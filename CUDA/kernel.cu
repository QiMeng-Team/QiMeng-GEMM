#include <stdio.h>
#include <stdlib.h>

// CUDA runtime
#include <cuda_runtime.h>

void kernel_128_128(int M, int N, int K, float alpha, float *A, float *B, float beta, float *C);
void kernel_64_128(int M, int N, int K, float alpha, float *A, float *B, float beta, float *C);
void kernel_64_64(int M, int N, int K, float alpha, float *A, float *B, float beta, float *C);
void kernel_32_64(int M, int N, int K, float alpha, float *A, float *B, float beta, float *C);

void cuda_gemm(int M, int N, int K, float alpha, float *A, float *B, float beta, float *C) {
    if (N >4096 || M > 4096) {
        kernel_128_128(M, N, K, alpha, A, B, beta, C);
    }
    else if (N >= 2048 || M>=2048) {
        kernel_64_128(M, N, K, alpha, A, B, beta, C);
    }
    else if (N==1024 && M==1024) {
        kernel_32_64(M, N, K, alpha, A, B, beta, C);
    }
    else {
        kernel_64_64(M, N, K, alpha, A, B, beta, C);
    }
}