/* openblas.c */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "driver/gemm.h"

#define min(x,y) (((x) < (y)) ? (x) : (y))

int main(int argc, char** argv)
{
    printf("%s",argv[0]);
    if (argc != 5) {
        printf("usage: ./main [M] [K] [N] [iter]\n");
        exit(0);
    }
    int M = atoi(argv[1]);
    int K = atoi(argv[2]);
    int N = atoi(argv[3]);
    float *A, *B, *C;
    int m, n, k, i, j;
    float alpha, beta;

    m = M, k = K, n = N;

    alpha = 1.0; beta = 0.0;

    A = (float *)malloc(m * k * sizeof(float));
    B = (float *)malloc(k * n * sizeof(float));
    C = (float *)malloc(m * n * sizeof(float));

    for (i = 0; i < (m * k); i++) {
        A[i] = (float)(i / 13);
    }

    for (i = 0; i < (k*n); i++) {
        B[i] = (float)(i % 13);
    }

    for (i = 0; i < (m * n); i++) {
        C[i] = 0.0;
    }
    double msecPerMatrixMul[2] = {0, 0};
    double gigaFlops[2] = {0, 0};
    double flopsPerMatrixMul = 2.0 * M * N * K;
    clock_t start, stop;
    float msecTotal = 0;
    int nIter = atoi(argv[4]);
    start = clock();
    for (int run = 0 ; run < nIter; run++) {
        // 此处使用了cblas单精度实数矩阵乘的接口
        my_cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, m, n, k, alpha, A, m, B, k, beta, C, m);    
    }
    stop = clock();
    printf ("\nComputations completed.\n\n");
    msecTotal = ((double)(stop - start) * 1000.0) / CLOCKS_PER_SEC;
    msecPerMatrixMul[0] = msecTotal / nIter;
    gigaFlops[0] = (flopsPerMatrixMul * 1.0e-9f) / (msecPerMatrixMul[0] / 1000.0f);
    printf("my OpenBLAS gemm Performance= %.2f GFlop/s, Time= %.3f msec, Size= %.0f Ops,\n",
        gigaFlops[0],
        msecPerMatrixMul[0],
        flopsPerMatrixMul);

    free(A);
    free(B);
    free(C);
    return 0;
}