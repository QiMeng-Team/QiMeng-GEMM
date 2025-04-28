#ifndef GEMM_OPERATIONS_H
#define GEMM_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cblas.h>  // OpenBLAS or CBLAS for consistency

#define GEMM_UNROLL_M 16
#define GEMM_UNROLL_N 8

#ifndef GEMM_P
	#define GEMM_P 8
#endif
#ifndef GEMM_Q
	#define GEMM_Q 16
#endif
#ifndef GEMM_R
	#define GEMM_R 32
#endif

#define COMPSIZE 1 // Placeholder for compatibility

// Function declarations
extern int gemm_ncopy(int min_l, int min_i, const float* a, int lda, float* sa);
extern int gemm_tcopy(int min_l, int min_jj, const float* b, int ldb, float* sb);
extern int gemm_kernel(int min_i, int min_jj, int min_l, const float alpha, float* sa, float* sb, float* c, int ldc);
extern int gemm_beta(int m, int n, int dummy1, float beta,
	  float *dummy2, int dummy3, float *dummy4, int dummy5,
	  float *c, int ldc);
      
#define ICOPY_OPERATION(M, N, A, LDA, X, Y, BUFFER) gemm_tcopy(M, N, (float *)(A) + ((Y) + (X) * (LDA)) * COMPSIZE, LDA, BUFFER);
#define OCOPY_OPERATION(M, N, A, LDA, X, Y, BUFFER) gemm_ncopy(M, N, (float *)(A) + ((X) + (Y) * (LDA)) * COMPSIZE, LDA, BUFFER);
#define KERNEL_OPERATION(M, N, K, ALPHA, SA, SB, C, LDC, X, Y) \
	gemm_kernel(M, N, K, ALPHA, SA, SB, (float *)(C) + ((X) + (Y) * LDC) * COMPSIZE, LDC)
#define BETA_OPERATION(M_FROM, M_TO, N_FROM, N_TO, BETA, C, LDC) \
	gemm_beta((M_TO) - (M_FROM), (N_TO - N_FROM), 0, \
		  BETA, NULL, 0, NULL, 0, \
		  (float *)(C) + ((M_FROM) + (N_FROM) * (LDC)) * COMPSIZE, LDC)

// Matrix multiplication framework with OpenBLAS-like signature
void my_cblas_sgemm(const CBLAS_LAYOUT Layout, const CBLAS_TRANSPOSE TransA,
                 const CBLAS_TRANSPOSE TransB, const int M, const int N,
                 const int K, const float alpha, const float *A,
                 const int lda, const float *B, const int ldb,
                 const float beta, float *C, const int ldc);

#endif // GEMM_OPERATIONS_H
