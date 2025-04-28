#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <riscv_vector.h>

#define L2_16_4 \
"li t1, 8 \n\t"\
"vsetvli    t0, t1, e32,m1,ta,ma \n\t"\
"fmv.w.x    ft11, zero         \n\t"\
"vfmv.v.f   v12,  ft11         \n\t"\
"vfmv.v.f   v13,  ft11         \n\t"\
"vfmv.v.f   v14,  ft11         \n\t"\
"vfmv.v.f   v15,  ft11         \n\t"\
"vfmv.v.f   v16,  ft11         \n\t"\
"vfmv.v.f   v17,  ft11         \n\t"\
"vfmv.v.f   v18,  ft11         \n\t"\
"vfmv.v.f   v19,  ft11         \n\t"\
"mv         t0,   %[BK]        \n\t"\
"srli       t0,   %[BK], 3     \n\t"\
"blez       t0,   M16x4_TAIL    \n\t"\
"addi       t1,    %[PB], 1*4  \n\t"\
"addi       t2,    %[PB], 2*4  \n\t"\
"addi       t3,    %[PB], 3*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"vfmv.v.f       v5,    ft1  \n\t"\
"vfmv.v.f       v6,    ft2  \n\t"\
"vfmv.v.f       v7,    ft3  \n\t"\
"addi       t4,    %[PA], 1*8*4  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t4)  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v4,  v1  \n\t"\
"vfmacc.vv  v14,  v5,  v0  \n\t"\
"vfmacc.vv  v15,  v5,  v1  \n\t"\
"vfmacc.vv  v16,  v6,  v0  \n\t"\
"vfmacc.vv  v17,  v6,  v1  \n\t"\
"vfmacc.vv  v18,  v7,  v0  \n\t"\
"vfmacc.vv  v19,  v7,  v1  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v8,    ft4  \n\t"\
"vfmv.v.f       v9,    ft5  \n\t"\
"vfmv.v.f       v10,    ft6  \n\t"\
"vfmv.v.f       v11,    ft7  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t4,    t4,       16*4  \n\t"\
"vle32.v       v2,    (%[PA])  \n\t"\
"vle32.v       v3,    (t4)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t4,    t4,       16*4  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t4)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t4,    t4,       16*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"vfmv.v.f       v5,    ft1  \n\t"\
"vfmv.v.f       v6,    ft2  \n\t"\
"vfmv.v.f       v7,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v12,  v8,  v2  \n\t"\
"vfmacc.vv  v13,  v8,  v3  \n\t"\
"vfmacc.vv  v14,  v9,  v2  \n\t"\
"vfmacc.vv  v15,  v9,  v3  \n\t"\
"vfmacc.vv  v16,  v10,  v2  \n\t"\
"vfmacc.vv  v17,  v10,  v3  \n\t"\
"vfmacc.vv  v18,  v11,  v2  \n\t"\
"vfmacc.vv  v19,  v11,  v3  \n\t"\
"vle32.v       v2,    (%[PA])  \n\t"\
"vle32.v       v3,    (t4)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t4,    t4,       16*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v8,    ft4  \n\t"\
"vfmv.v.f       v9,    ft5  \n\t"\
"vfmv.v.f       v10,    ft6  \n\t"\
"vfmv.v.f       v11,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v4,  v1  \n\t"\
"vfmacc.vv  v14,  v5,  v0  \n\t"\
"vfmacc.vv  v15,  v5,  v1  \n\t"\
"vfmacc.vv  v16,  v6,  v0  \n\t"\
"vfmacc.vv  v17,  v6,  v1  \n\t"\
"vfmacc.vv  v18,  v7,  v0  \n\t"\
"vfmacc.vv  v19,  v7,  v1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t4)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t4,    t4,       16*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"vfmv.v.f       v5,    ft1  \n\t"\
"vfmv.v.f       v6,    ft2  \n\t"\
"vfmv.v.f       v7,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v12,  v8,  v2  \n\t"\
"vfmacc.vv  v13,  v8,  v3  \n\t"\
"vfmacc.vv  v14,  v9,  v2  \n\t"\
"vfmacc.vv  v15,  v9,  v3  \n\t"\
"vfmacc.vv  v16,  v10,  v2  \n\t"\
"vfmacc.vv  v17,  v10,  v3  \n\t"\
"vfmacc.vv  v18,  v11,  v2  \n\t"\
"vfmacc.vv  v19,  v11,  v3  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"blez       t0,   M16x4_MAINLOOP_TAIL    \n\t"\
".align 4                      \n\t"\
"M16x4_MAINLOOP:                \n\t"\
"vle32.v       v2,    (%[PA])  \n\t"\
"vle32.v       v3,    (t4)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t4,    t4,       16*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v8,    ft4  \n\t"\
"vfmv.v.f       v9,    ft5  \n\t"\
"vfmv.v.f       v10,    ft6  \n\t"\
"vfmv.v.f       v11,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v4,  v1  \n\t"\
"vfmacc.vv  v14,  v5,  v0  \n\t"\
"vfmacc.vv  v15,  v5,  v1  \n\t"\
"vfmacc.vv  v16,  v6,  v0  \n\t"\
"vfmacc.vv  v17,  v6,  v1  \n\t"\
"vfmacc.vv  v18,  v7,  v0  \n\t"\
"vfmacc.vv  v19,  v7,  v1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t4)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t4,    t4,       16*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"vfmv.v.f       v5,    ft1  \n\t"\
"vfmv.v.f       v6,    ft2  \n\t"\
"vfmv.v.f       v7,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v12,  v8,  v2  \n\t"\
"vfmacc.vv  v13,  v8,  v3  \n\t"\
"vfmacc.vv  v14,  v9,  v2  \n\t"\
"vfmacc.vv  v15,  v9,  v3  \n\t"\
"vfmacc.vv  v16,  v10,  v2  \n\t"\
"vfmacc.vv  v17,  v10,  v3  \n\t"\
"vfmacc.vv  v18,  v11,  v2  \n\t"\
"vfmacc.vv  v19,  v11,  v3  \n\t"\
"vle32.v       v2,    (%[PA])  \n\t"\
"vle32.v       v3,    (t4)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t4,    t4,       16*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v8,    ft4  \n\t"\
"vfmv.v.f       v9,    ft5  \n\t"\
"vfmv.v.f       v10,    ft6  \n\t"\
"vfmv.v.f       v11,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v4,  v1  \n\t"\
"vfmacc.vv  v14,  v5,  v0  \n\t"\
"vfmacc.vv  v15,  v5,  v1  \n\t"\
"vfmacc.vv  v16,  v6,  v0  \n\t"\
"vfmacc.vv  v17,  v6,  v1  \n\t"\
"vfmacc.vv  v18,  v7,  v0  \n\t"\
"vfmacc.vv  v19,  v7,  v1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t4)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t4,    t4,       16*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"vfmv.v.f       v5,    ft1  \n\t"\
"vfmv.v.f       v6,    ft2  \n\t"\
"vfmv.v.f       v7,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v12,  v8,  v2  \n\t"\
"vfmacc.vv  v13,  v8,  v3  \n\t"\
"vfmacc.vv  v14,  v9,  v2  \n\t"\
"vfmacc.vv  v15,  v9,  v3  \n\t"\
"vfmacc.vv  v16,  v10,  v2  \n\t"\
"vfmacc.vv  v17,  v10,  v3  \n\t"\
"vfmacc.vv  v18,  v11,  v2  \n\t"\
"vfmacc.vv  v19,  v11,  v3  \n\t"\
"vle32.v       v2,    (%[PA])  \n\t"\
"vle32.v       v3,    (t4)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t4,    t4,       16*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v8,    ft4  \n\t"\
"vfmv.v.f       v9,    ft5  \n\t"\
"vfmv.v.f       v10,    ft6  \n\t"\
"vfmv.v.f       v11,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v4,  v1  \n\t"\
"vfmacc.vv  v14,  v5,  v0  \n\t"\
"vfmacc.vv  v15,  v5,  v1  \n\t"\
"vfmacc.vv  v16,  v6,  v0  \n\t"\
"vfmacc.vv  v17,  v6,  v1  \n\t"\
"vfmacc.vv  v18,  v7,  v0  \n\t"\
"vfmacc.vv  v19,  v7,  v1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t4)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t4,    t4,       16*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"vfmv.v.f       v5,    ft1  \n\t"\
"vfmv.v.f       v6,    ft2  \n\t"\
"vfmv.v.f       v7,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v12,  v8,  v2  \n\t"\
"vfmacc.vv  v13,  v8,  v3  \n\t"\
"vfmacc.vv  v14,  v9,  v2  \n\t"\
"vfmacc.vv  v15,  v9,  v3  \n\t"\
"vfmacc.vv  v16,  v10,  v2  \n\t"\
"vfmacc.vv  v17,  v10,  v3  \n\t"\
"vfmacc.vv  v18,  v11,  v2  \n\t"\
"vfmacc.vv  v19,  v11,  v3  \n\t"\
"vle32.v       v2,    (%[PA])  \n\t"\
"vle32.v       v3,    (t4)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t4,    t4,       16*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v8,    ft4  \n\t"\
"vfmv.v.f       v9,    ft5  \n\t"\
"vfmv.v.f       v10,    ft6  \n\t"\
"vfmv.v.f       v11,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v4,  v1  \n\t"\
"vfmacc.vv  v14,  v5,  v0  \n\t"\
"vfmacc.vv  v15,  v5,  v1  \n\t"\
"vfmacc.vv  v16,  v6,  v0  \n\t"\
"vfmacc.vv  v17,  v6,  v1  \n\t"\
"vfmacc.vv  v18,  v7,  v0  \n\t"\
"vfmacc.vv  v19,  v7,  v1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t4)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t4,    t4,       16*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"vfmv.v.f       v5,    ft1  \n\t"\
"vfmv.v.f       v6,    ft2  \n\t"\
"vfmv.v.f       v7,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v12,  v8,  v2  \n\t"\
"vfmacc.vv  v13,  v8,  v3  \n\t"\
"vfmacc.vv  v14,  v9,  v2  \n\t"\
"vfmacc.vv  v15,  v9,  v3  \n\t"\
"vfmacc.vv  v16,  v10,  v2  \n\t"\
"vfmacc.vv  v17,  v10,  v3  \n\t"\
"vfmacc.vv  v18,  v11,  v2  \n\t"\
"vfmacc.vv  v19,  v11,  v3  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M16x4_MAINLOOP \n\t"\
"M16x4_MAINLOOP_TAIL:           \n\t"\
"vle32.v       v2,    (%[PA])  \n\t"\
"vle32.v       v3,    (t4)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t4,    t4,       16*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v8,    ft4  \n\t"\
"vfmv.v.f       v9,    ft5  \n\t"\
"vfmv.v.f       v10,    ft6  \n\t"\
"vfmv.v.f       v11,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v4,  v1  \n\t"\
"vfmacc.vv  v14,  v5,  v0  \n\t"\
"vfmacc.vv  v15,  v5,  v1  \n\t"\
"vfmacc.vv  v16,  v6,  v0  \n\t"\
"vfmacc.vv  v17,  v6,  v1  \n\t"\
"vfmacc.vv  v18,  v7,  v0  \n\t"\
"vfmacc.vv  v19,  v7,  v1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t4)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t4,    t4,       16*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"vfmv.v.f       v5,    ft1  \n\t"\
"vfmv.v.f       v6,    ft2  \n\t"\
"vfmv.v.f       v7,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v12,  v8,  v2  \n\t"\
"vfmacc.vv  v13,  v8,  v3  \n\t"\
"vfmacc.vv  v14,  v9,  v2  \n\t"\
"vfmacc.vv  v15,  v9,  v3  \n\t"\
"vfmacc.vv  v16,  v10,  v2  \n\t"\
"vfmacc.vv  v17,  v10,  v3  \n\t"\
"vfmacc.vv  v18,  v11,  v2  \n\t"\
"vfmacc.vv  v19,  v11,  v3  \n\t"\
"vle32.v       v2,    (%[PA])  \n\t"\
"vle32.v       v3,    (t4)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t4,    t4,       16*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v8,    ft4  \n\t"\
"vfmv.v.f       v9,    ft5  \n\t"\
"vfmv.v.f       v10,    ft6  \n\t"\
"vfmv.v.f       v11,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v4,  v1  \n\t"\
"vfmacc.vv  v14,  v5,  v0  \n\t"\
"vfmacc.vv  v15,  v5,  v1  \n\t"\
"vfmacc.vv  v16,  v6,  v0  \n\t"\
"vfmacc.vv  v17,  v6,  v1  \n\t"\
"vfmacc.vv  v18,  v7,  v0  \n\t"\
"vfmacc.vv  v19,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v2  \n\t"\
"vfmacc.vv  v13,  v8,  v3  \n\t"\
"vfmacc.vv  v14,  v9,  v2  \n\t"\
"vfmacc.vv  v15,  v9,  v3  \n\t"\
"vfmacc.vv  v16,  v10,  v2  \n\t"\
"vfmacc.vv  v17,  v10,  v3  \n\t"\
"vfmacc.vv  v18,  v11,  v2  \n\t"\
"vfmacc.vv  v19,  v11,  v3  \n\t"\
"M16x4_TAIL:                    \n\t"\
"andi       t0,   %[BK], 7     \n\t"\
"blez       t0,   M16x4_SAVERESULT   \n\t"\
"addi       t4,    %[PA], 1*8*4  \n\t"\
"addi       t1,    %[PB], 1*4  \n\t"\
"addi       t2,    %[PB], 2*4  \n\t"\
"addi       t3,    %[PB], 3*4  \n\t"\
".align 4                      \n\t"\
"M16x4_TAILLOOP:                \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"vfmv.v.f       v5,    ft1  \n\t"\
"vfmv.v.f       v6,    ft2  \n\t"\
"vfmv.v.f       v7,    ft3  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t4)  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v4,  v1  \n\t"\
"vfmacc.vv  v14,  v5,  v0  \n\t"\
"vfmacc.vv  v15,  v5,  v1  \n\t"\
"vfmacc.vv  v16,  v6,  v0  \n\t"\
"vfmacc.vv  v17,  v6,  v1  \n\t"\
"vfmacc.vv  v18,  v7,  v0  \n\t"\
"vfmacc.vv  v19,  v7,  v1  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t4,    t4,       16*4  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M16x4_TAILLOOP \n\t"\
"M16x4_SAVERESULT:              \n\t"\
"vfmv.v.f   v0,   %[ALPHA]     \n\t"\
"vle32.v       v4,    (%[C0])  \n\t"\
"vle32.v       v5,    (%[C1])  \n\t"\
"vle32.v       v6,    (%[C2])  \n\t"\
"vle32.v       v7,    (%[C3])  \n\t"\
"vfmacc.vv  v4,   v0, v12  \n\t"\
"vfmacc.vv  v5,   v0, v14  \n\t"\
"vfmacc.vv  v6,   v0, v16  \n\t"\
"vfmacc.vv  v7,   v0, v18  \n\t"\
"vse32.v      v4,   (%[C0])   \n\t"\
"vse32.v      v5,   (%[C1])   \n\t"\
"vse32.v      v6,   (%[C2])   \n\t"\
"vse32.v      v7,   (%[C3])   \n\t"\
"add        %[C0], %[C0], 8*4   \n\t"\
"add        %[C1], %[C1], 8*4   \n\t"\
"add        %[C2], %[C2], 8*4   \n\t"\
"add        %[C3], %[C3], 8*4   \n\t"\
"vle32.v       v4,    (%[C0])  \n\t"\
"vle32.v       v5,    (%[C1])  \n\t"\
"vle32.v       v6,    (%[C2])  \n\t"\
"vle32.v       v7,    (%[C3])  \n\t"\
"vfmacc.vv  v4,   v0, v13  \n\t"\
"vfmacc.vv  v5,   v0, v15  \n\t"\
"vfmacc.vv  v6,   v0, v17  \n\t"\
"vfmacc.vv  v7,   v0, v19  \n\t"\
"vse32.v      v4,   (%[C0])   \n\t"\
"vse32.v      v5,   (%[C1])   \n\t"\
"vse32.v      v6,   (%[C2])   \n\t"\
"vse32.v      v7,   (%[C3])   \n\t"\
"add        %[C0], %[C0], 8*4   \n\t"\
"add        %[C1], %[C1], 8*4   \n\t"\
"add        %[C2], %[C2], 8*4   \n\t"\
"add        %[C3], %[C3], 8*4   \n\t"\
"M16x4_END:                     \n\t"\
:[C0]"+r"(C0),[C1]"+r"(C1),[C2]"+r"(C2),[C3]"+r"(C3),[PA]"+r"(ptrba),[PB]"+r"(ptrbb)\
:[ALPHA]"f"(alpha), [BK]"r"(bk)\
:"t0", "t4", "t1", "t2", "t3", "ft11", "ft0", "ft1", "ft2", "ft3", "ft4", "ft5", "ft6", "ft7", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15", "v16", "v17", "v18", "v19"

#define L2_8_4 \
"li t1, 8 \n\t"\
"vsetvli    t0, t1, e32,m1,ta,ma \n\t"\
"fmv.w.x    ft11, zero         \n\t"\
"vfmv.v.f   v10,  ft11         \n\t"\
"vfmv.v.f   v11,  ft11         \n\t"\
"vfmv.v.f   v12,  ft11         \n\t"\
"vfmv.v.f   v13,  ft11         \n\t"\
"mv         t0,   %[BK]        \n\t"\
"srli       t0,   %[BK], 3     \n\t"\
"blez       t0,   M8x4_TAIL    \n\t"\
"addi       t1,    %[PB], 1*4  \n\t"\
"addi       t2,    %[PB], 2*4  \n\t"\
"addi       t3,    %[PB], 3*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"blez       t0,   M8x4_MAINLOOP_TAIL    \n\t"\
".align 4                      \n\t"\
"M8x4_MAINLOOP:                \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M8x4_MAINLOOP \n\t"\
"M8x4_MAINLOOP_TAIL:           \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"M8x4_TAIL:                    \n\t"\
"andi       t0,   %[BK], 7     \n\t"\
"blez       t0,   M8x4_SAVERESULT   \n\t"\
"addi       t1,    %[PB], 1*4  \n\t"\
"addi       t2,    %[PB], 2*4  \n\t"\
"addi       t3,    %[PB], 3*4  \n\t"\
".align 4                      \n\t"\
"M8x4_TAILLOOP:                \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M8x4_TAILLOOP \n\t"\
"M8x4_SAVERESULT:              \n\t"\
"vfmv.v.f   v0,   %[ALPHA]     \n\t"\
"vle32.v       v2,    (%[C0])  \n\t"\
"vle32.v       v3,    (%[C1])  \n\t"\
"vle32.v       v4,    (%[C2])  \n\t"\
"vle32.v       v5,    (%[C3])  \n\t"\
"vfmacc.vv  v2,   v0, v10  \n\t"\
"vfmacc.vv  v3,   v0, v11  \n\t"\
"vfmacc.vv  v4,   v0, v12  \n\t"\
"vfmacc.vv  v5,   v0, v13  \n\t"\
"vse32.v      v2,   (%[C0])   \n\t"\
"vse32.v      v3,   (%[C1])   \n\t"\
"vse32.v      v4,   (%[C2])   \n\t"\
"vse32.v      v5,   (%[C3])   \n\t"\
"add        %[C0], %[C0], 8*4   \n\t"\
"add        %[C1], %[C1], 8*4   \n\t"\
"add        %[C2], %[C2], 8*4   \n\t"\
"add        %[C3], %[C3], 8*4   \n\t"\
"M8x4_END:                     \n\t"\
:[C0]"+r"(C0),[C1]"+r"(C1),[C2]"+r"(C2),[C3]"+r"(C3),[PA]"+r"(ptrba),[PB]"+r"(ptrbb)\
:[ALPHA]"f"(alpha), [BK]"r"(bk)\
:"t0", "t1", "t2", "t3", "ft11", "ft0", "ft1", "ft2", "ft3", "ft4", "ft5", "ft6", "ft7", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8", "v9", "v10", "v11", "v12", "v13"

#define L2_4_4 \
"li t1, 4 \n\t"\
"vsetvli    t0, t1, e32,m1,ta,ma \n\t"\
"fmv.w.x    ft11, zero         \n\t"\
"vfmv.v.f   v10,  ft11         \n\t"\
"vfmv.v.f   v11,  ft11         \n\t"\
"vfmv.v.f   v12,  ft11         \n\t"\
"vfmv.v.f   v13,  ft11         \n\t"\
"mv         t0,   %[BK]        \n\t"\
"srli       t0,   %[BK], 3     \n\t"\
"blez       t0,   M4x4_TAIL    \n\t"\
"addi       t1,    %[PB], 1*4  \n\t"\
"addi       t2,    %[PB], 2*4  \n\t"\
"addi       t3,    %[PB], 3*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"blez       t0,   M4x4_MAINLOOP_TAIL    \n\t"\
".align 4                      \n\t"\
"M4x4_MAINLOOP:                \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M4x4_MAINLOOP \n\t"\
"M4x4_MAINLOOP_TAIL:           \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"M4x4_TAIL:                    \n\t"\
"andi       t0,   %[BK], 7     \n\t"\
"blez       t0,   M4x4_SAVERESULT   \n\t"\
"addi       t1,    %[PB], 1*4  \n\t"\
"addi       t2,    %[PB], 2*4  \n\t"\
"addi       t3,    %[PB], 3*4  \n\t"\
".align 4                      \n\t"\
"M4x4_TAILLOOP:                \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M4x4_TAILLOOP \n\t"\
"M4x4_SAVERESULT:              \n\t"\
"vfmv.v.f   v0,   %[ALPHA]     \n\t"\
"vle32.v       v2,    (%[C0])  \n\t"\
"vle32.v       v3,    (%[C1])  \n\t"\
"vle32.v       v4,    (%[C2])  \n\t"\
"vle32.v       v5,    (%[C3])  \n\t"\
"vfmacc.vv  v2,   v0, v10  \n\t"\
"vfmacc.vv  v3,   v0, v11  \n\t"\
"vfmacc.vv  v4,   v0, v12  \n\t"\
"vfmacc.vv  v5,   v0, v13  \n\t"\
"vse32.v      v2,   (%[C0])   \n\t"\
"vse32.v      v3,   (%[C1])   \n\t"\
"vse32.v      v4,   (%[C2])   \n\t"\
"vse32.v      v5,   (%[C3])   \n\t"\
"add        %[C0], %[C0], 4*4   \n\t"\
"add        %[C1], %[C1], 4*4   \n\t"\
"add        %[C2], %[C2], 4*4   \n\t"\
"add        %[C3], %[C3], 4*4   \n\t"\
"M4x4_END:                     \n\t"\
:[C0]"+r"(C0),[C1]"+r"(C1),[C2]"+r"(C2),[C3]"+r"(C3),[PA]"+r"(ptrba),[PB]"+r"(ptrbb)\
:[ALPHA]"f"(alpha), [BK]"r"(bk)\
:"t0", "t1", "t2", "t3", "ft11", "ft0", "ft1", "ft2", "ft3", "ft4", "ft5", "ft6", "ft7", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8", "v9", "v10", "v11", "v12", "v13"

#define L2_2_4 \
"li t1, 2 \n\t"\
"vsetvli    t0, t1, e32,m1,ta,ma \n\t"\
"fmv.w.x    ft11, zero         \n\t"\
"vfmv.v.f   v10,  ft11         \n\t"\
"vfmv.v.f   v11,  ft11         \n\t"\
"vfmv.v.f   v12,  ft11         \n\t"\
"vfmv.v.f   v13,  ft11         \n\t"\
"mv         t0,   %[BK]        \n\t"\
"srli       t0,   %[BK], 3     \n\t"\
"blez       t0,   M2x4_TAIL    \n\t"\
"addi       t1,    %[PB], 1*4  \n\t"\
"addi       t2,    %[PB], 2*4  \n\t"\
"addi       t3,    %[PB], 3*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"blez       t0,   M2x4_MAINLOOP_TAIL    \n\t"\
".align 4                      \n\t"\
"M2x4_MAINLOOP:                \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M2x4_MAINLOOP \n\t"\
"M2x4_MAINLOOP_TAIL:           \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"M2x4_TAIL:                    \n\t"\
"andi       t0,   %[BK], 7     \n\t"\
"blez       t0,   M2x4_SAVERESULT   \n\t"\
"addi       t1,    %[PB], 1*4  \n\t"\
"addi       t2,    %[PB], 2*4  \n\t"\
"addi       t3,    %[PB], 3*4  \n\t"\
".align 4                      \n\t"\
"M2x4_TAILLOOP:                \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M2x4_TAILLOOP \n\t"\
"M2x4_SAVERESULT:              \n\t"\
"vfmv.v.f   v0,   %[ALPHA]     \n\t"\
"vle32.v       v2,    (%[C0])  \n\t"\
"vle32.v       v3,    (%[C1])  \n\t"\
"vle32.v       v4,    (%[C2])  \n\t"\
"vle32.v       v5,    (%[C3])  \n\t"\
"vfmacc.vv  v2,   v0, v10  \n\t"\
"vfmacc.vv  v3,   v0, v11  \n\t"\
"vfmacc.vv  v4,   v0, v12  \n\t"\
"vfmacc.vv  v5,   v0, v13  \n\t"\
"vse32.v      v2,   (%[C0])   \n\t"\
"vse32.v      v3,   (%[C1])   \n\t"\
"vse32.v      v4,   (%[C2])   \n\t"\
"vse32.v      v5,   (%[C3])   \n\t"\
"add        %[C0], %[C0], 2*4   \n\t"\
"add        %[C1], %[C1], 2*4   \n\t"\
"add        %[C2], %[C2], 2*4   \n\t"\
"add        %[C3], %[C3], 2*4   \n\t"\
"M2x4_END:                     \n\t"\
:[C0]"+r"(C0),[C1]"+r"(C1),[C2]"+r"(C2),[C3]"+r"(C3),[PA]"+r"(ptrba),[PB]"+r"(ptrbb)\
:[ALPHA]"f"(alpha), [BK]"r"(bk)\
:"t0", "t1", "t2", "t3", "ft11", "ft0", "ft1", "ft2", "ft3", "ft4", "ft5", "ft6", "ft7", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8", "v9", "v10", "v11", "v12", "v13"

#define L2_1_4 \
"li t1, 1 \n\t"\
"vsetvli    t0, t1, e32,m1,ta,ma \n\t"\
"fmv.w.x    ft11, zero         \n\t"\
"vfmv.v.f   v10,  ft11         \n\t"\
"vfmv.v.f   v11,  ft11         \n\t"\
"vfmv.v.f   v12,  ft11         \n\t"\
"vfmv.v.f   v13,  ft11         \n\t"\
"mv         t0,   %[BK]        \n\t"\
"srli       t0,   %[BK], 3     \n\t"\
"blez       t0,   M1x4_TAIL    \n\t"\
"addi       t1,    %[PB], 1*4  \n\t"\
"addi       t2,    %[PB], 2*4  \n\t"\
"addi       t3,    %[PB], 3*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"blez       t0,   M1x4_MAINLOOP_TAIL    \n\t"\
".align 4                      \n\t"\
"M1x4_MAINLOOP:                \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M1x4_MAINLOOP \n\t"\
"M1x4_MAINLOOP_TAIL:           \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft4,    (%[PB])  \n\t"\
"flw       ft5,    (t1)  \n\t"\
"flw       ft6,    (t2)  \n\t"\
"flw       ft7,    (t3)  \n\t"\
"vfmv.v.f       v6,    ft4  \n\t"\
"vfmv.v.f       v7,    ft5  \n\t"\
"vfmv.v.f       v8,    ft6  \n\t"\
"vfmv.v.f       v9,    ft7  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"vfmacc.vv  v10,  v6,  v1  \n\t"\
"vfmacc.vv  v11,  v7,  v1  \n\t"\
"vfmacc.vv  v12,  v8,  v1  \n\t"\
"vfmacc.vv  v13,  v9,  v1  \n\t"\
"M1x4_TAIL:                    \n\t"\
"andi       t0,   %[BK], 7     \n\t"\
"blez       t0,   M1x4_SAVERESULT   \n\t"\
"addi       t1,    %[PB], 1*4  \n\t"\
"addi       t2,    %[PB], 2*4  \n\t"\
"addi       t3,    %[PB], 3*4  \n\t"\
".align 4                      \n\t"\
"M1x4_TAILLOOP:                \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"flw       ft2,    (t2)  \n\t"\
"flw       ft3,    (t3)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vfmacc.vv  v10,  v2,  v0  \n\t"\
"vfmacc.vv  v11,  v3,  v0  \n\t"\
"vfmacc.vv  v12,  v4,  v0  \n\t"\
"vfmacc.vv  v13,  v5,  v0  \n\t"\
"addi       %[PB],    %[PB], 4*4  \n\t"\
"addi       t1,    t1, 4*4  \n\t"\
"addi       t2,    t2, 4*4  \n\t"\
"addi       t3,    t3, 4*4  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M1x4_TAILLOOP \n\t"\
"M1x4_SAVERESULT:              \n\t"\
"vfmv.v.f   v0,   %[ALPHA]     \n\t"\
"vle32.v       v2,    (%[C0])  \n\t"\
"vle32.v       v3,    (%[C1])  \n\t"\
"vle32.v       v4,    (%[C2])  \n\t"\
"vle32.v       v5,    (%[C3])  \n\t"\
"vfmacc.vv  v2,   v0, v10  \n\t"\
"vfmacc.vv  v3,   v0, v11  \n\t"\
"vfmacc.vv  v4,   v0, v12  \n\t"\
"vfmacc.vv  v5,   v0, v13  \n\t"\
"vse32.v      v2,   (%[C0])   \n\t"\
"vse32.v      v3,   (%[C1])   \n\t"\
"vse32.v      v4,   (%[C2])   \n\t"\
"vse32.v      v5,   (%[C3])   \n\t"\
"add        %[C0], %[C0], 1*4   \n\t"\
"add        %[C1], %[C1], 1*4   \n\t"\
"add        %[C2], %[C2], 1*4   \n\t"\
"add        %[C3], %[C3], 1*4   \n\t"\
"M1x4_END:                     \n\t"\
:[C0]"+r"(C0),[C1]"+r"(C1),[C2]"+r"(C2),[C3]"+r"(C3),[PA]"+r"(ptrba),[PB]"+r"(ptrbb)\
:[ALPHA]"f"(alpha), [BK]"r"(bk)\
:"t0", "t1", "t2", "t3", "ft11", "ft0", "ft1", "ft2", "ft3", "ft4", "ft5", "ft6", "ft7", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8", "v9", "v10", "v11", "v12", "v13"

#define L2_16_2 \
"li t1, 8 \n\t"\
"vsetvli    t0, t1, e32,m1,ta,ma \n\t"\
"fmv.w.x    ft11, zero         \n\t"\
"vfmv.v.f   v8,  ft11         \n\t"\
"vfmv.v.f   v9,  ft11         \n\t"\
"vfmv.v.f   v10,  ft11         \n\t"\
"vfmv.v.f   v11,  ft11         \n\t"\
"mv         t0,   %[BK]        \n\t"\
"srli       t0,   %[BK], 3     \n\t"\
"blez       t0,   M16x2_TAIL    \n\t"\
"addi       t1,    %[PB], 1*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"vfmv.v.f       v5,    ft1  \n\t"\
"addi       t2,    %[PA], 1*8*4  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t2)  \n\t"\
"vfmacc.vv  v8,  v4,  v0  \n\t"\
"vfmacc.vv  v9,  v4,  v1  \n\t"\
"vfmacc.vv  v10,  v5,  v0  \n\t"\
"vfmacc.vv  v11,  v5,  v1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v6,    ft2  \n\t"\
"vfmv.v.f       v7,    ft3  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t2,    t2,       16*4  \n\t"\
"vle32.v       v2,    (%[PA])  \n\t"\
"vle32.v       v3,    (t2)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t2,    t2,       16*4  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t2)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t2,    t2,       16*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"vfmv.v.f       v5,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v8,  v6,  v2  \n\t"\
"vfmacc.vv  v9,  v6,  v3  \n\t"\
"vfmacc.vv  v10,  v7,  v2  \n\t"\
"vfmacc.vv  v11,  v7,  v3  \n\t"\
"vle32.v       v2,    (%[PA])  \n\t"\
"vle32.v       v3,    (t2)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t2,    t2,       16*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v6,    ft2  \n\t"\
"vfmv.v.f       v7,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v8,  v4,  v0  \n\t"\
"vfmacc.vv  v9,  v4,  v1  \n\t"\
"vfmacc.vv  v10,  v5,  v0  \n\t"\
"vfmacc.vv  v11,  v5,  v1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t2)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t2,    t2,       16*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"vfmv.v.f       v5,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v8,  v6,  v2  \n\t"\
"vfmacc.vv  v9,  v6,  v3  \n\t"\
"vfmacc.vv  v10,  v7,  v2  \n\t"\
"vfmacc.vv  v11,  v7,  v3  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"blez       t0,   M16x2_MAINLOOP_TAIL    \n\t"\
".align 4                      \n\t"\
"M16x2_MAINLOOP:                \n\t"\
"vle32.v       v2,    (%[PA])  \n\t"\
"vle32.v       v3,    (t2)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t2,    t2,       16*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v6,    ft2  \n\t"\
"vfmv.v.f       v7,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v8,  v4,  v0  \n\t"\
"vfmacc.vv  v9,  v4,  v1  \n\t"\
"vfmacc.vv  v10,  v5,  v0  \n\t"\
"vfmacc.vv  v11,  v5,  v1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t2)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t2,    t2,       16*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"vfmv.v.f       v5,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v8,  v6,  v2  \n\t"\
"vfmacc.vv  v9,  v6,  v3  \n\t"\
"vfmacc.vv  v10,  v7,  v2  \n\t"\
"vfmacc.vv  v11,  v7,  v3  \n\t"\
"vle32.v       v2,    (%[PA])  \n\t"\
"vle32.v       v3,    (t2)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t2,    t2,       16*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v6,    ft2  \n\t"\
"vfmv.v.f       v7,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v8,  v4,  v0  \n\t"\
"vfmacc.vv  v9,  v4,  v1  \n\t"\
"vfmacc.vv  v10,  v5,  v0  \n\t"\
"vfmacc.vv  v11,  v5,  v1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t2)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t2,    t2,       16*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"vfmv.v.f       v5,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v8,  v6,  v2  \n\t"\
"vfmacc.vv  v9,  v6,  v3  \n\t"\
"vfmacc.vv  v10,  v7,  v2  \n\t"\
"vfmacc.vv  v11,  v7,  v3  \n\t"\
"vle32.v       v2,    (%[PA])  \n\t"\
"vle32.v       v3,    (t2)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t2,    t2,       16*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v6,    ft2  \n\t"\
"vfmv.v.f       v7,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v8,  v4,  v0  \n\t"\
"vfmacc.vv  v9,  v4,  v1  \n\t"\
"vfmacc.vv  v10,  v5,  v0  \n\t"\
"vfmacc.vv  v11,  v5,  v1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t2)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t2,    t2,       16*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"vfmv.v.f       v5,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v8,  v6,  v2  \n\t"\
"vfmacc.vv  v9,  v6,  v3  \n\t"\
"vfmacc.vv  v10,  v7,  v2  \n\t"\
"vfmacc.vv  v11,  v7,  v3  \n\t"\
"vle32.v       v2,    (%[PA])  \n\t"\
"vle32.v       v3,    (t2)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t2,    t2,       16*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v6,    ft2  \n\t"\
"vfmv.v.f       v7,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v8,  v4,  v0  \n\t"\
"vfmacc.vv  v9,  v4,  v1  \n\t"\
"vfmacc.vv  v10,  v5,  v0  \n\t"\
"vfmacc.vv  v11,  v5,  v1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t2)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t2,    t2,       16*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"vfmv.v.f       v5,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v8,  v6,  v2  \n\t"\
"vfmacc.vv  v9,  v6,  v3  \n\t"\
"vfmacc.vv  v10,  v7,  v2  \n\t"\
"vfmacc.vv  v11,  v7,  v3  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M16x2_MAINLOOP \n\t"\
"M16x2_MAINLOOP_TAIL:           \n\t"\
"vle32.v       v2,    (%[PA])  \n\t"\
"vle32.v       v3,    (t2)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t2,    t2,       16*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v6,    ft2  \n\t"\
"vfmv.v.f       v7,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v8,  v4,  v0  \n\t"\
"vfmacc.vv  v9,  v4,  v1  \n\t"\
"vfmacc.vv  v10,  v5,  v0  \n\t"\
"vfmacc.vv  v11,  v5,  v1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t2)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t2,    t2,       16*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"vfmv.v.f       v5,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v8,  v6,  v2  \n\t"\
"vfmacc.vv  v9,  v6,  v3  \n\t"\
"vfmacc.vv  v10,  v7,  v2  \n\t"\
"vfmacc.vv  v11,  v7,  v3  \n\t"\
"vle32.v       v2,    (%[PA])  \n\t"\
"vle32.v       v3,    (t2)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t2,    t2,       16*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v6,    ft2  \n\t"\
"vfmv.v.f       v7,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v8,  v4,  v0  \n\t"\
"vfmacc.vv  v9,  v4,  v1  \n\t"\
"vfmacc.vv  v10,  v5,  v0  \n\t"\
"vfmacc.vv  v11,  v5,  v1  \n\t"\
"vfmacc.vv  v8,  v6,  v2  \n\t"\
"vfmacc.vv  v9,  v6,  v3  \n\t"\
"vfmacc.vv  v10,  v7,  v2  \n\t"\
"vfmacc.vv  v11,  v7,  v3  \n\t"\
"M16x2_TAIL:                    \n\t"\
"andi       t0,   %[BK], 7     \n\t"\
"blez       t0,   M16x2_SAVERESULT   \n\t"\
"addi       t2,    %[PA], 1*8*4  \n\t"\
"addi       t1,    %[PB], 1*4  \n\t"\
".align 4                      \n\t"\
"M16x2_TAILLOOP:                \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"vfmv.v.f       v5,    ft1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t2)  \n\t"\
"vfmacc.vv  v8,  v4,  v0  \n\t"\
"vfmacc.vv  v9,  v4,  v1  \n\t"\
"vfmacc.vv  v10,  v5,  v0  \n\t"\
"vfmacc.vv  v11,  v5,  v1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t2,    t2,       16*4  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M16x2_TAILLOOP \n\t"\
"M16x2_SAVERESULT:              \n\t"\
"vfmv.v.f   v0,   %[ALPHA]     \n\t"\
"vle32.v       v4,    (%[C0])  \n\t"\
"vle32.v       v5,    (%[C1])  \n\t"\
"vfmacc.vv  v4,   v0, v8  \n\t"\
"vfmacc.vv  v5,   v0, v10  \n\t"\
"vse32.v      v4,   (%[C0])   \n\t"\
"vse32.v      v5,   (%[C1])   \n\t"\
"add        %[C0], %[C0], 8*4   \n\t"\
"add        %[C1], %[C1], 8*4   \n\t"\
"vle32.v       v4,    (%[C0])  \n\t"\
"vle32.v       v5,    (%[C1])  \n\t"\
"vfmacc.vv  v4,   v0, v9  \n\t"\
"vfmacc.vv  v5,   v0, v11  \n\t"\
"vse32.v      v4,   (%[C0])   \n\t"\
"vse32.v      v5,   (%[C1])   \n\t"\
"add        %[C0], %[C0], 8*4   \n\t"\
"add        %[C1], %[C1], 8*4   \n\t"\
"M16x2_END:                     \n\t"\
:[C0]"+r"(C0),[C1]"+r"(C1),[PA]"+r"(ptrba),[PB]"+r"(ptrbb)\
:[ALPHA]"f"(alpha), [BK]"r"(bk)\
:"t0", "t2", "t1", "ft11", "ft0", "ft1", "ft2", "ft3", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8", "v9", "v10", "v11"

#define L2_8_2 \
"li t1, 8 \n\t"\
"vsetvli    t0, t1, e32,m1,ta,ma \n\t"\
"fmv.w.x    ft11, zero         \n\t"\
"vfmv.v.f   v6,  ft11         \n\t"\
"vfmv.v.f   v7,  ft11         \n\t"\
"mv         t0,   %[BK]        \n\t"\
"srli       t0,   %[BK], 3     \n\t"\
"blez       t0,   M8x2_TAIL    \n\t"\
"addi       t1,    %[PB], 1*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"blez       t0,   M8x2_MAINLOOP_TAIL    \n\t"\
".align 4                      \n\t"\
"M8x2_MAINLOOP:                \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M8x2_MAINLOOP \n\t"\
"M8x2_MAINLOOP_TAIL:           \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"M8x2_TAIL:                    \n\t"\
"andi       t0,   %[BK], 7     \n\t"\
"blez       t0,   M8x2_SAVERESULT   \n\t"\
"addi       t1,    %[PB], 1*4  \n\t"\
".align 4                      \n\t"\
"M8x2_TAILLOOP:                \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M8x2_TAILLOOP \n\t"\
"M8x2_SAVERESULT:              \n\t"\
"vfmv.v.f   v0,   %[ALPHA]     \n\t"\
"vle32.v       v2,    (%[C0])  \n\t"\
"vle32.v       v3,    (%[C1])  \n\t"\
"vfmacc.vv  v2,   v0, v6  \n\t"\
"vfmacc.vv  v3,   v0, v7  \n\t"\
"vse32.v      v2,   (%[C0])   \n\t"\
"vse32.v      v3,   (%[C1])   \n\t"\
"add        %[C0], %[C0], 8*4   \n\t"\
"add        %[C1], %[C1], 8*4   \n\t"\
"M8x2_END:                     \n\t"\
:[C0]"+r"(C0),[C1]"+r"(C1),[PA]"+r"(ptrba),[PB]"+r"(ptrbb)\
:[ALPHA]"f"(alpha), [BK]"r"(bk)\
:"t0", "t1", "ft11", "ft0", "ft1", "ft2", "ft3", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7"

#define L2_4_2 \
"li t1, 4 \n\t"\
"vsetvli    t0, t1, e32,m1,ta,ma \n\t"\
"fmv.w.x    ft11, zero         \n\t"\
"vfmv.v.f   v6,  ft11         \n\t"\
"vfmv.v.f   v7,  ft11         \n\t"\
"mv         t0,   %[BK]        \n\t"\
"srli       t0,   %[BK], 3     \n\t"\
"blez       t0,   M4x2_TAIL    \n\t"\
"addi       t1,    %[PB], 1*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"blez       t0,   M4x2_MAINLOOP_TAIL    \n\t"\
".align 4                      \n\t"\
"M4x2_MAINLOOP:                \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M4x2_MAINLOOP \n\t"\
"M4x2_MAINLOOP_TAIL:           \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"M4x2_TAIL:                    \n\t"\
"andi       t0,   %[BK], 7     \n\t"\
"blez       t0,   M4x2_SAVERESULT   \n\t"\
"addi       t1,    %[PB], 1*4  \n\t"\
".align 4                      \n\t"\
"M4x2_TAILLOOP:                \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M4x2_TAILLOOP \n\t"\
"M4x2_SAVERESULT:              \n\t"\
"vfmv.v.f   v0,   %[ALPHA]     \n\t"\
"vle32.v       v2,    (%[C0])  \n\t"\
"vle32.v       v3,    (%[C1])  \n\t"\
"vfmacc.vv  v2,   v0, v6  \n\t"\
"vfmacc.vv  v3,   v0, v7  \n\t"\
"vse32.v      v2,   (%[C0])   \n\t"\
"vse32.v      v3,   (%[C1])   \n\t"\
"add        %[C0], %[C0], 4*4   \n\t"\
"add        %[C1], %[C1], 4*4   \n\t"\
"M4x2_END:                     \n\t"\
:[C0]"+r"(C0),[C1]"+r"(C1),[PA]"+r"(ptrba),[PB]"+r"(ptrbb)\
:[ALPHA]"f"(alpha), [BK]"r"(bk)\
:"t0", "t1", "ft11", "ft0", "ft1", "ft2", "ft3", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7"

#define L2_2_2 \
"li t1, 2 \n\t"\
"vsetvli    t0, t1, e32,m1,ta,ma \n\t"\
"fmv.w.x    ft11, zero         \n\t"\
"vfmv.v.f   v6,  ft11         \n\t"\
"vfmv.v.f   v7,  ft11         \n\t"\
"mv         t0,   %[BK]        \n\t"\
"srli       t0,   %[BK], 3     \n\t"\
"blez       t0,   M2x2_TAIL    \n\t"\
"addi       t1,    %[PB], 1*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"blez       t0,   M2x2_MAINLOOP_TAIL    \n\t"\
".align 4                      \n\t"\
"M2x2_MAINLOOP:                \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M2x2_MAINLOOP \n\t"\
"M2x2_MAINLOOP_TAIL:           \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"M2x2_TAIL:                    \n\t"\
"andi       t0,   %[BK], 7     \n\t"\
"blez       t0,   M2x2_SAVERESULT   \n\t"\
"addi       t1,    %[PB], 1*4  \n\t"\
".align 4                      \n\t"\
"M2x2_TAILLOOP:                \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M2x2_TAILLOOP \n\t"\
"M2x2_SAVERESULT:              \n\t"\
"vfmv.v.f   v0,   %[ALPHA]     \n\t"\
"vle32.v       v2,    (%[C0])  \n\t"\
"vle32.v       v3,    (%[C1])  \n\t"\
"vfmacc.vv  v2,   v0, v6  \n\t"\
"vfmacc.vv  v3,   v0, v7  \n\t"\
"vse32.v      v2,   (%[C0])   \n\t"\
"vse32.v      v3,   (%[C1])   \n\t"\
"add        %[C0], %[C0], 2*4   \n\t"\
"add        %[C1], %[C1], 2*4   \n\t"\
"M2x2_END:                     \n\t"\
:[C0]"+r"(C0),[C1]"+r"(C1),[PA]"+r"(ptrba),[PB]"+r"(ptrbb)\
:[ALPHA]"f"(alpha), [BK]"r"(bk)\
:"t0", "t1", "ft11", "ft0", "ft1", "ft2", "ft3", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7"

#define L2_1_2 \
"li t1, 1 \n\t"\
"vsetvli    t0, t1, e32,m1,ta,ma \n\t"\
"fmv.w.x    ft11, zero         \n\t"\
"vfmv.v.f   v6,  ft11         \n\t"\
"vfmv.v.f   v7,  ft11         \n\t"\
"mv         t0,   %[BK]        \n\t"\
"srli       t0,   %[BK], 3     \n\t"\
"blez       t0,   M1x2_TAIL    \n\t"\
"addi       t1,    %[PB], 1*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"blez       t0,   M1x2_MAINLOOP_TAIL    \n\t"\
".align 4                      \n\t"\
"M1x2_MAINLOOP:                \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M1x2_MAINLOOP \n\t"\
"M1x2_MAINLOOP_TAIL:           \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft2,    (%[PB])  \n\t"\
"flw       ft3,    (t1)  \n\t"\
"vfmv.v.f       v4,    ft2  \n\t"\
"vfmv.v.f       v5,    ft3  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"vfmacc.vv  v6,  v4,  v1  \n\t"\
"vfmacc.vv  v7,  v5,  v1  \n\t"\
"M1x2_TAIL:                    \n\t"\
"andi       t0,   %[BK], 7     \n\t"\
"blez       t0,   M1x2_SAVERESULT   \n\t"\
"addi       t1,    %[PB], 1*4  \n\t"\
".align 4                      \n\t"\
"M1x2_TAILLOOP:                \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"flw       ft1,    (t1)  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vfmacc.vv  v6,  v2,  v0  \n\t"\
"vfmacc.vv  v7,  v3,  v0  \n\t"\
"addi       %[PB],    %[PB], 2*4  \n\t"\
"addi       t1,    t1, 2*4  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M1x2_TAILLOOP \n\t"\
"M1x2_SAVERESULT:              \n\t"\
"vfmv.v.f   v0,   %[ALPHA]     \n\t"\
"vle32.v       v2,    (%[C0])  \n\t"\
"vle32.v       v3,    (%[C1])  \n\t"\
"vfmacc.vv  v2,   v0, v6  \n\t"\
"vfmacc.vv  v3,   v0, v7  \n\t"\
"vse32.v      v2,   (%[C0])   \n\t"\
"vse32.v      v3,   (%[C1])   \n\t"\
"add        %[C0], %[C0], 1*4   \n\t"\
"add        %[C1], %[C1], 1*4   \n\t"\
"M1x2_END:                     \n\t"\
:[C0]"+r"(C0),[C1]"+r"(C1),[PA]"+r"(ptrba),[PB]"+r"(ptrbb)\
:[ALPHA]"f"(alpha), [BK]"r"(bk)\
:"t0", "t1", "ft11", "ft0", "ft1", "ft2", "ft3", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7"

#define L2_16_1 \
"li t1, 8 \n\t"\
"vsetvli    t0, t1, e32,m1,ta,ma \n\t"\
"fmv.w.x    ft11, zero         \n\t"\
"vfmv.v.f   v6,  ft11         \n\t"\
"vfmv.v.f   v7,  ft11         \n\t"\
"mv         t0,   %[BK]        \n\t"\
"srli       t0,   %[BK], 3     \n\t"\
"blez       t0,   M16x1_TAIL    \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"addi       t1,    %[PA], 1*8*4  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t1)  \n\t"\
"vfmacc.vv  v6,  v4,  v0  \n\t"\
"vfmacc.vv  v7,  v4,  v1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v5,    ft1  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t1,    t1,       16*4  \n\t"\
"vle32.v       v2,    (%[PA])  \n\t"\
"vle32.v       v3,    (t1)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t1,    t1,       16*4  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t1)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t1,    t1,       16*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v6,  v5,  v2  \n\t"\
"vfmacc.vv  v7,  v5,  v3  \n\t"\
"vle32.v       v2,    (%[PA])  \n\t"\
"vle32.v       v3,    (t1)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t1,    t1,       16*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v5,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v6,  v4,  v0  \n\t"\
"vfmacc.vv  v7,  v4,  v1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t1)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t1,    t1,       16*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v6,  v5,  v2  \n\t"\
"vfmacc.vv  v7,  v5,  v3  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"blez       t0,   M16x1_MAINLOOP_TAIL    \n\t"\
".align 4                      \n\t"\
"M16x1_MAINLOOP:                \n\t"\
"vle32.v       v2,    (%[PA])  \n\t"\
"vle32.v       v3,    (t1)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t1,    t1,       16*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v5,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v6,  v4,  v0  \n\t"\
"vfmacc.vv  v7,  v4,  v1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t1)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t1,    t1,       16*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v6,  v5,  v2  \n\t"\
"vfmacc.vv  v7,  v5,  v3  \n\t"\
"vle32.v       v2,    (%[PA])  \n\t"\
"vle32.v       v3,    (t1)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t1,    t1,       16*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v5,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v6,  v4,  v0  \n\t"\
"vfmacc.vv  v7,  v4,  v1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t1)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t1,    t1,       16*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v6,  v5,  v2  \n\t"\
"vfmacc.vv  v7,  v5,  v3  \n\t"\
"vle32.v       v2,    (%[PA])  \n\t"\
"vle32.v       v3,    (t1)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t1,    t1,       16*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v5,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v6,  v4,  v0  \n\t"\
"vfmacc.vv  v7,  v4,  v1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t1)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t1,    t1,       16*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v6,  v5,  v2  \n\t"\
"vfmacc.vv  v7,  v5,  v3  \n\t"\
"vle32.v       v2,    (%[PA])  \n\t"\
"vle32.v       v3,    (t1)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t1,    t1,       16*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v5,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v6,  v4,  v0  \n\t"\
"vfmacc.vv  v7,  v4,  v1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t1)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t1,    t1,       16*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v6,  v5,  v2  \n\t"\
"vfmacc.vv  v7,  v5,  v3  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M16x1_MAINLOOP \n\t"\
"M16x1_MAINLOOP_TAIL:           \n\t"\
"vle32.v       v2,    (%[PA])  \n\t"\
"vle32.v       v3,    (t1)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t1,    t1,       16*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v5,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v6,  v4,  v0  \n\t"\
"vfmacc.vv  v7,  v4,  v1  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t1)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t1,    t1,       16*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v6,  v5,  v2  \n\t"\
"vfmacc.vv  v7,  v5,  v3  \n\t"\
"vle32.v       v2,    (%[PA])  \n\t"\
"vle32.v       v3,    (t1)  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t1,    t1,       16*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v5,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v6,  v4,  v0  \n\t"\
"vfmacc.vv  v7,  v4,  v1  \n\t"\
"vfmacc.vv  v6,  v5,  v2  \n\t"\
"vfmacc.vv  v7,  v5,  v3  \n\t"\
"M16x1_TAIL:                    \n\t"\
"andi       t0,   %[BK], 7     \n\t"\
"blez       t0,   M16x1_SAVERESULT   \n\t"\
"addi       t1,    %[PA], 1*8*4  \n\t"\
".align 4                      \n\t"\
"M16x1_TAILLOOP:                \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v4,    ft0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vle32.v       v1,    (t1)  \n\t"\
"vfmacc.vv  v6,  v4,  v0  \n\t"\
"vfmacc.vv  v7,  v4,  v1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"addi       %[PA],    %[PA], 16*4  \n\t"\
"addi       t1,    t1,       16*4  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M16x1_TAILLOOP \n\t"\
"M16x1_SAVERESULT:              \n\t"\
"vfmv.v.f   v0,   %[ALPHA]     \n\t"\
"vle32.v       v4,    (%[C0])  \n\t"\
"vfmacc.vv  v4,   v0, v6  \n\t"\
"vse32.v      v4,   (%[C0])   \n\t"\
"add        %[C0], %[C0], 8*4   \n\t"\
"vle32.v       v4,    (%[C0])  \n\t"\
"vfmacc.vv  v4,   v0, v7  \n\t"\
"vse32.v      v4,   (%[C0])   \n\t"\
"add        %[C0], %[C0], 8*4   \n\t"\
"M16x1_END:                     \n\t"\
:[C0]"+r"(C0),[PA]"+r"(ptrba),[PB]"+r"(ptrbb)\
:[ALPHA]"f"(alpha), [BK]"r"(bk)\
:"t0", "t1", "ft11", "ft0", "ft1", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7"

#define L2_8_1 \
"li t1, 8 \n\t"\
"vsetvli    t0, t1, e32,m1,ta,ma \n\t"\
"fmv.w.x    ft11, zero         \n\t"\
"vfmv.v.f   v4,  ft11         \n\t"\
"mv         t0,   %[BK]        \n\t"\
"srli       t0,   %[BK], 3     \n\t"\
"blez       t0,   M8x1_TAIL    \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"blez       t0,   M8x1_MAINLOOP_TAIL    \n\t"\
".align 4                      \n\t"\
"M8x1_MAINLOOP:                \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M8x1_MAINLOOP \n\t"\
"M8x1_MAINLOOP_TAIL:           \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"M8x1_TAIL:                    \n\t"\
"andi       t0,   %[BK], 7     \n\t"\
"blez       t0,   M8x1_SAVERESULT   \n\t"\
".align 4                      \n\t"\
"M8x1_TAILLOOP:                \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"addi       %[PA],    %[PA], 8*4  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M8x1_TAILLOOP \n\t"\
"M8x1_SAVERESULT:              \n\t"\
"vfmv.v.f   v0,   %[ALPHA]     \n\t"\
"vle32.v       v2,    (%[C0])  \n\t"\
"vfmacc.vv  v2,   v0, v4  \n\t"\
"vse32.v      v2,   (%[C0])   \n\t"\
"add        %[C0], %[C0], 8*4   \n\t"\
"M8x1_END:                     \n\t"\
:[C0]"+r"(C0),[PA]"+r"(ptrba),[PB]"+r"(ptrbb)\
:[ALPHA]"f"(alpha), [BK]"r"(bk)\
:"t0", "ft11", "ft0", "ft1", "v0", "v1", "v2", "v3", "v4"

#define L2_4_1 \
"li t1, 4 \n\t"\
"vsetvli    t0, t1, e32,m1,ta,ma \n\t"\
"fmv.w.x    ft11, zero         \n\t"\
"vfmv.v.f   v4,  ft11         \n\t"\
"mv         t0,   %[BK]        \n\t"\
"srli       t0,   %[BK], 3     \n\t"\
"blez       t0,   M4x1_TAIL    \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"blez       t0,   M4x1_MAINLOOP_TAIL    \n\t"\
".align 4                      \n\t"\
"M4x1_MAINLOOP:                \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M4x1_MAINLOOP \n\t"\
"M4x1_MAINLOOP_TAIL:           \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"M4x1_TAIL:                    \n\t"\
"andi       t0,   %[BK], 7     \n\t"\
"blez       t0,   M4x1_SAVERESULT   \n\t"\
".align 4                      \n\t"\
"M4x1_TAILLOOP:                \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"addi       %[PA],    %[PA], 4*4  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M4x1_TAILLOOP \n\t"\
"M4x1_SAVERESULT:              \n\t"\
"vfmv.v.f   v0,   %[ALPHA]     \n\t"\
"vle32.v       v2,    (%[C0])  \n\t"\
"vfmacc.vv  v2,   v0, v4  \n\t"\
"vse32.v      v2,   (%[C0])   \n\t"\
"add        %[C0], %[C0], 4*4   \n\t"\
"M4x1_END:                     \n\t"\
:[C0]"+r"(C0),[PA]"+r"(ptrba),[PB]"+r"(ptrbb)\
:[ALPHA]"f"(alpha), [BK]"r"(bk)\
:"t0", "ft11", "ft0", "ft1", "v0", "v1", "v2", "v3", "v4"

#define L2_2_1 \
"li t1, 2 \n\t"\
"vsetvli    t0, t1, e32,m1,ta,ma \n\t"\
"fmv.w.x    ft11, zero         \n\t"\
"vfmv.v.f   v4,  ft11         \n\t"\
"mv         t0,   %[BK]        \n\t"\
"srli       t0,   %[BK], 3     \n\t"\
"blez       t0,   M2x1_TAIL    \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"blez       t0,   M2x1_MAINLOOP_TAIL    \n\t"\
".align 4                      \n\t"\
"M2x1_MAINLOOP:                \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M2x1_MAINLOOP \n\t"\
"M2x1_MAINLOOP_TAIL:           \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"M2x1_TAIL:                    \n\t"\
"andi       t0,   %[BK], 7     \n\t"\
"blez       t0,   M2x1_SAVERESULT   \n\t"\
".align 4                      \n\t"\
"M2x1_TAILLOOP:                \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"addi       %[PA],    %[PA], 2*4  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M2x1_TAILLOOP \n\t"\
"M2x1_SAVERESULT:              \n\t"\
"vfmv.v.f   v0,   %[ALPHA]     \n\t"\
"vle32.v       v2,    (%[C0])  \n\t"\
"vfmacc.vv  v2,   v0, v4  \n\t"\
"vse32.v      v2,   (%[C0])   \n\t"\
"add        %[C0], %[C0], 2*4   \n\t"\
"M2x1_END:                     \n\t"\
:[C0]"+r"(C0),[PA]"+r"(ptrba),[PB]"+r"(ptrbb)\
:[ALPHA]"f"(alpha), [BK]"r"(bk)\
:"t0", "ft11", "ft0", "ft1", "v0", "v1", "v2", "v3", "v4"

#define L2_1_1 \
"li t1, 1 \n\t"\
"vsetvli    t0, t1, e32,m1,ta,ma \n\t"\
"fmv.w.x    ft11, zero         \n\t"\
"vfmv.v.f   v4,  ft11         \n\t"\
"mv         t0,   %[BK]        \n\t"\
"srli       t0,   %[BK], 3     \n\t"\
"blez       t0,   M1x1_TAIL    \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"blez       t0,   M1x1_MAINLOOP_TAIL    \n\t"\
".align 4                      \n\t"\
"M1x1_MAINLOOP:                \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M1x1_MAINLOOP \n\t"\
"M1x1_MAINLOOP_TAIL:           \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"vle32.v       v1,    (%[PA])  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"flw       ft1,    (%[PB])  \n\t"\
"vfmv.v.f       v3,    ft1  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"vfmacc.vv  v4,  v3,  v1  \n\t"\
"M1x1_TAIL:                    \n\t"\
"andi       t0,   %[BK], 7     \n\t"\
"blez       t0,   M1x1_SAVERESULT   \n\t"\
".align 4                      \n\t"\
"M1x1_TAILLOOP:                \n\t"\
"flw       ft0,    (%[PB])  \n\t"\
"vfmv.v.f       v2,    ft0  \n\t"\
"vle32.v       v0,    (%[PA])  \n\t"\
"vfmacc.vv  v4,  v2,  v0  \n\t"\
"addi       %[PB],    %[PB], 1*4  \n\t"\
"addi       %[PA],    %[PA], 1*4  \n\t"\
"addi       t0,   t0, -1       \n\t"\
"bgtz       t0,   M1x1_TAILLOOP \n\t"\
"M1x1_SAVERESULT:              \n\t"\
"vfmv.v.f   v0,   %[ALPHA]     \n\t"\
"vle32.v       v2,    (%[C0])  \n\t"\
"vfmacc.vv  v2,   v0, v4  \n\t"\
"vse32.v      v2,   (%[C0])   \n\t"\
"add        %[C0], %[C0], 1*4   \n\t"\
"M1x1_END:                     \n\t"\
:[C0]"+r"(C0),[PA]"+r"(ptrba),[PB]"+r"(ptrbb)\
:[ALPHA]"f"(alpha), [BK]"r"(bk)\
:"t0", "ft11", "ft0", "ft1", "v0", "v1", "v2", "v3", "v4"

int gemm_kernel(long bm,long bn,long bk,float alpha,float* ba,float* bb,float* C,long ldc)
{
   long i,j,k;
   float *C0,*C1,*C2,*C3;
   float *ptrba,*ptrbb;

   for (j=0; j<bn/4; j+=1){
	   C0 = C;
	   C1 = C0+ldc;
	   C2 = C1+ldc;
	   C3 = C2+ldc;

	   ptrba = ba;
      for(i=0; i<bm/16; i+=1) {
         ptrbb = bb;
         asm volatile(L2_16_4);
      }
      if(bm&8) {
         ptrbb = bb;
         asm volatile(L2_8_4);
      }
      if(bm&4) {
         ptrbb = bb;
         asm volatile(L2_4_4);
      }
      if(bm&2) {
         ptrbb = bb;
         asm volatile(L2_2_4);
      }
      if(bm&1) {
         ptrbb = bb;
         asm volatile(L2_1_4);
      }
      k = bk*4;
	   bb = bb+k;
	   i = ldc*4;
	   C = C+i;
   }
   if(bn&2) {
      C0 = C;
	   C1 = C0+ldc;

	   ptrba = ba;
      for(i=0; i<bm/16; i+=1) {
         ptrbb = bb;
         asm volatile(L2_16_2);
      }
      if(bm&8) {
         ptrbb = bb;
         asm volatile(L2_8_2);
      }
      if(bm&4) {
         ptrbb = bb;
         asm volatile(L2_4_2);
      }
      if(bm&2) {
         ptrbb = bb;
         asm volatile(L2_2_2);
      }
      if(bm&1) {
         ptrbb = bb;
         asm volatile(L2_1_2);
      }
      k = bk*2;
	   bb = bb+k;
	   i = ldc*2;
	   C = C+i;
   }
   if(bn&1) {
      C0 = C;
	   ptrba = ba;
      for(i=0; i<bm/16; i+=1) {
         ptrbb = bb;
         asm volatile(L2_16_1);
      }
      if(bm&8) {
         ptrbb = bb;
         asm volatile(L2_8_1);
      }
      if(bm&4) {
         ptrbb = bb;
         asm volatile(L2_4_1);
      }
      if(bm&2) {
         ptrbb = bb;
         asm volatile(L2_2_1);
      }
      if(bm&1) {
         ptrbb = bb;
         asm volatile(L2_1_1);
      }
      k = bk;
	   bb = bb+k;
	   C = C+ldc;
   }
   return 0 ;
}