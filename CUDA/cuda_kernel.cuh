// optimize sgemm

#include <stdio.h>
#include <stdlib.h>

// CUDA runtime
#include <cuda_runtime.h>
#include <cublas_v2.h>

// transfer float4
#define FLOAT4(pointer) (reinterpret_cast<float4*>(&(pointer))[0])

#define OFFSET(row, col, ld) ((row) * (ld) + (col))

template <const int BM, const int BN, const int BK, const int WM, const int WN,
          const int WMITER, const int WNITER, const int TM, const int TN>
__global__ void gemm(int M, int N, int K, float alpha, float *A, float *B, float beta, float *C) {
    // Shared memory for sub-matrices of A and B
    __shared__ float As[2][BK][BM];
    __shared__ float Bs[2][BK][BN];

    // Thread index
    int tid = threadIdx.x;
    int wid = tid / 32; // Warp index in the block
    int lane = tid % 32; // Thread index in the warp
    int thread_num = BM * BN / WM / WN * 32;

    // Calculate the height of the block for A and B
    const int hightA = thread_num / (BK / 4);
    const int hightB = thread_num / (BN / 4);

    // Calculate the load indices for shared memory
    int load_a_smem_m = threadIdx.x / (BK / 4);
    int load_a_smem_k = threadIdx.x % (BK / 4) * 4;
    int load_b_smem_k = threadIdx.x / (BN / 4);
    int load_b_smem_n = threadIdx.x % (BN / 4) * 4;

    // Warp and thread indices within the block
    int Wrow = wid / (BN / WN);
    int Wcol = wid % (BN / WN);
    int Trow = lane / (WNITER / TN);
    int Tcol = lane % (WNITER / TN);

    // Temporary results
    float results[WM / WMITER * TM][WN / WNITER * TN] = {0.0f};
    float regM[TM] = {0.0f};
    float regN[TN] = {0.0f};

    int A_offset = blockIdx.y * BM * K;
    int B_offset = blockIdx.x * BN;
    int C_offset = blockIdx.y * BM * N + blockIdx.x * BN;

    // Initial load of A and B into shared memory (phase 0)
    for (int loadOffset = 0; loadOffset < BM; loadOffset += hightA) {
        float4 tmp = FLOAT4(A[OFFSET(load_a_smem_m + loadOffset, load_a_smem_k, K) + A_offset]);
        As[0][load_a_smem_k][load_a_smem_m + loadOffset] = tmp.x;
        As[0][load_a_smem_k + 1][load_a_smem_m + loadOffset] = tmp.y;
        As[0][load_a_smem_k + 2][load_a_smem_m + loadOffset] = tmp.z;
        As[0][load_a_smem_k + 3][load_a_smem_m + loadOffset] = tmp.w;
    }
    for (int loadOffset = 0; loadOffset < BK; loadOffset += hightB) {
        FLOAT4(Bs[0][load_b_smem_k + loadOffset][load_b_smem_n]) =
            FLOAT4(B[OFFSET(load_b_smem_k + loadOffset, load_b_smem_n, N) + B_offset]);
    }

    for (int bkIdx = 1; bkIdx < (K + BK - 1) / BK; bkIdx++) {
        __syncthreads();
        int comp_flag = (bkIdx - 1) & 1;
        int mem_flag = bkIdx & 1;

        // Compute the product of As and Bs
        for (int k = 0; k < BK; ++k) {
            for (int wm = 0; wm < WM / WMITER; ++wm) {
                for (int wn = 0; wn < WN / WNITER; ++wn) {
                    // Move numbers to the register
                    for (int i = 0; i < TM; ++i) {
                        regM[i] = As[comp_flag][k][Wrow * WM + wm * WMITER + Trow * TM + i];
                    }
                    for (int j = 0; j < TN; ++j) {
                        regN[j] = Bs[comp_flag][k][Wcol * WN + wn * WNITER + Tcol * TN + j];
                    }
                    // Compute results
                    for (int i = 0; i < TM; ++i) {
                        for (int j = 0; j < TN; ++j) {
                            results[wm * TM + i][wn * TN + j] += regM[i] * regN[j];
                        }
                    }
                }
            }
        }

        // Load A into shared memory with transposition (phase n)
        for (int loadOffset = 0; loadOffset < BM; loadOffset += hightA) {
            float4 tmp = FLOAT4(A[OFFSET(load_a_smem_m + loadOffset, load_a_smem_k + bkIdx * BK, K) + A_offset]);
            As[mem_flag][load_a_smem_k][load_a_smem_m + loadOffset] = tmp.x;
            As[mem_flag][load_a_smem_k + 1][load_a_smem_m + loadOffset] = tmp.y;
            As[mem_flag][load_a_smem_k + 2][load_a_smem_m + loadOffset] = tmp.z;
            As[mem_flag][load_a_smem_k + 3][load_a_smem_m + loadOffset] = tmp.w;
        }
        // Load B into shared memory (phase n)
        for (int loadOffset = 0; loadOffset < BK; loadOffset += hightB) {
            FLOAT4(Bs[mem_flag][load_b_smem_k + loadOffset][load_b_smem_n]) =
                FLOAT4(B[OFFSET(load_b_smem_k + loadOffset + bkIdx * BK, load_b_smem_n, N) + B_offset]);
        }
    }

    // Final computation phase
    __syncthreads();
    int comp_flag = ((K + BK - 1) / BK - 1) & 1;
    for (int k = 0; k < BK; ++k) {
        for (int wm = 0; wm < WM / WMITER; ++wm) {
            for (int wn = 0; wn < WN / WNITER; ++wn) {
                // Move numbers to the register
                for (int i = 0; i < TM; ++i) {
                    regM[i] = As[comp_flag][k][Wrow * WM + wm * WMITER + Trow * TM + i];
                }
                for (int j = 0; j < TN; ++j) {
                    regN[j] = Bs[comp_flag][k][Wcol * WN + wn * WNITER + Tcol * TN + j];
                }
                // Compute results
                for (int i = 0; i < TM; ++i) {
                    for (int j = 0; j < TN; ++j) {
                        results[wm * TM + i][wn * TN + j] += regM[i] * regN[j];
                    }
                }
            }
        }
    }

    // Store the results back to global memory
    for (int wm = 0; wm < WM / WMITER; ++wm)
        for (int wn = 0; wn < WN / WNITER; ++wn)
            for (int m = 0; m < TM; ++m)
                for (int n = 0; n < TN; ++n) {
                    int load_c_gmem = OFFSET(Wrow * WM + wm * WMITER + Trow * TM + m, Wcol * WN + wn * WNITER + Tcol * TN + n, N) + C_offset;
                    C[load_c_gmem] = alpha * results[m + wm * TM][n + wn * TN] + beta * C[load_c_gmem];
                }
}






