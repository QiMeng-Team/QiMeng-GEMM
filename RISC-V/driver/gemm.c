#include "gemm.h"

// Matrix multiplication framework with OpenBLAS-like signature
void my_cblas_sgemm(const CBLAS_LAYOUT Layout, const CBLAS_TRANSPOSE TransA,
                 const CBLAS_TRANSPOSE TransB, const int M, const int N,
                 const int K, const float alpha, const float *A,
                 const int lda, const float *B, const int ldb,
                 const float beta, float *C, const int ldc) {

    // OpenBLAS uses column-major order by default; handle row-major conversion
    int n_from = 0, n_to = N, m_from = 0, m_to = M, k = K, l2size = 256; // Assuming cache size placeholder
    int min_l, min_i, min_j;
    int ls, is, js;
    int jjs, min_jj;
    int l1stride;
    int gemm_p;
    float *sa = (float*)malloc(GEMM_P * GEMM_Q * sizeof(float));
    float *sb = (float*)malloc(GEMM_Q * GEMM_R * sizeof(float));
    /*
    void *buffer = (void*)malloc(32 << 20);
    float *sa = (float *)((long)buffer +0);
    float *sb = (float *)(((long)sa + ((GEMM_P * GEMM_Q * COMPSIZE * 4 + 16383) & ~16383)) + 0);
    */

    // Scaling the result matrix C by beta
    /*
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            C[i + j * ldc] *= beta;
        }
    }
    */
    
    BETA_OPERATION(m_from, m_to, n_from, n_to, beta, C, ldc);
 
    for (js = n_from; js < n_to; js += GEMM_R) {
    min_j = n_to - js;
    if (min_j > GEMM_R)
        min_j = GEMM_R;

    for (ls = 0; ls < k; ls += min_l) {
        min_l = k - ls;
        if (min_l >= GEMM_Q * 2) {
            min_l = GEMM_Q;
        } else {
            if (min_l > GEMM_Q) {
                min_l = ((min_l / 2 + GEMM_UNROLL_M - 1) / GEMM_UNROLL_M) * GEMM_UNROLL_M;
            }
            gemm_p = ((l2size / min_l + GEMM_UNROLL_M - 1) / GEMM_UNROLL_M) * GEMM_UNROLL_M;
            while (gemm_p * min_l > l2size)
                gemm_p -= GEMM_UNROLL_M;
        }
        int pad_min_l = min_l;

        // Handle full width matrix operations
        min_i = m_to - m_from;
        l1stride = 1;
        if (min_i >= GEMM_P * 2) {
            min_i = GEMM_P;
        } else {
            if (min_i > GEMM_P) {
                min_i = ((min_i / 2 + GEMM_UNROLL_M - 1) / GEMM_UNROLL_M) * GEMM_UNROLL_M;
            } else {
                l1stride = 0;
            }
        }

        // Copy data A to L2 cache and perform KERNEL_OPERATION
        ICOPY_OPERATION(min_l, min_i, A, lda, ls, m_from, sa);
        for (jjs = js; jjs < js + min_j; jjs += min_jj) {
            min_jj = min_j + js - jjs;
            if (min_jj >= 3 * GEMM_UNROLL_N)
                min_jj = 3 * GEMM_UNROLL_N;
            else if (min_jj > GEMM_UNROLL_N)
                min_jj = GEMM_UNROLL_N;

            OCOPY_OPERATION(min_l, min_jj, B, ldb, ls, jjs, sb + pad_min_l * (jjs - js) * COMPSIZE * l1stride);
            KERNEL_OPERATION(min_i, min_jj, min_l, alpha, sa, sb + pad_min_l * (jjs - js) * COMPSIZE * l1stride, C, ldc, m_from, jjs);
        }

        // Process the remaining submatrices
        for (is = m_from + min_i; is < m_to; is += min_i) {
            min_i = m_to - is;
            if (min_i >= GEMM_P * 2) {
                min_i = GEMM_P;
            } else if (min_i > GEMM_P) {
                min_i = ((min_i / 2 + GEMM_UNROLL_M - 1) / GEMM_UNROLL_M) * GEMM_UNROLL_M;
            }

            ICOPY_OPERATION(min_l, min_i, A, lda, ls, is, sa);
            KERNEL_OPERATION(min_i, min_j, min_l, alpha, sa, sb, C, ldc, is, js);
        }
    }
}

    free(sa);
    free(sb);
    // free(buffer);
}
