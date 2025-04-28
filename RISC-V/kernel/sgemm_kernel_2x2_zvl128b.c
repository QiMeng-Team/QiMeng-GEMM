#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <riscv_vector.h>


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
   float *C0,*C1;
   float *ptrba,*ptrbb;

   for (j=0; j<bn/2; j+=1){
	   C0 = C;
	   C1 = C0+ldc;

	   ptrba = ba;
      for(i=0; i<bm/2; i+=1) {
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
      for(i=0; i<bm/2; i+=1) {
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