#include <stdio.h>
#include <stdlib.h>

// CUDA runtime
#include <cuda_runtime.h>
#include "cuda_kernel.cuh"

#define CEIL_DIV(M, N) (((M) + (N)-1) / (N))

void kernel_64_64(int M, int N, int K, float alpha, float *A, float *B,
                 float beta, float *C) {
    static const int BM = 64;
    static const int BN = 64;
    static const int BK = 16;
    static const int WM = 16;
    static const int WN = 32;
    static const int WMITER = 16;
    static const int WNITER = 32;
    static const int TM = 4;
    static const int TN = 4;

    dim3 threadsPerBlock((BM*BN)/(WM*WN)*32);
    dim3 blocksPerGrid(CEIL_DIV(N, BN), CEIL_DIV(M, BM));
    gemm<BM, BN, BK, WM, WN, WMITER, WNITER, TM, TN>
        <<<blocksPerGrid, threadsPerBlock>>>(M, N, K, alpha, A, B, beta, C);      
}