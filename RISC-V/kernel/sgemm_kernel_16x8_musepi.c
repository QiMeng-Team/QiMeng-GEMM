#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <riscv_vector.h>

int gemm_kernel(long bm,long bn,long bk,float alpha,float* ba,float* bb,float* C,long ldc
		)
{
   long i,j,k;
   float *C0,*C1,*C2,*C3,*C4,*C5,*C6,*C7;
   float *ptrba,*ptrbb;
   
   float loadb0,loadb1,loadb2,loadb3,loadb4,loadb5,loadb6,loadb7;
   float load0,load1,load2,load3,load4,load5,load6,load7;
   float load8,load9,load10,load11,load12,load13,load14,load15;

   float res0,res1,res2,res3;
   float res4,res5,res6,res7;
   float res8,res9,res10,res11;
   float res12,res13,res14,res15;
   float res16,res17,res18,res19;
   float res20,res21,res22,res23;
   float res24,res25,res26,res27;
   float res28,res29,res30,res31;

   for (j=0; j<bn/8; j+=1){
   	   C0 = C;
	   C1 = C0+ldc;
	   C2 = C1+ldc;
	   C3 = C2+ldc;
	   
   	   C4 = C+4*ldc;
	   C5 = C1+4*ldc;
	   C6 = C2+4*ldc;
	   C7 = C3+4*ldc;

	   ptrba = ba;
	   for(i=0; i<bm/16; i+=1){
		   ptrbb = bb;
		   //t0 for k
		   //ft0-ft7 for B
		   //v0-v1 for A
		   //v16-v31 for temp C

	   	   asm volatile(
				"vsetvli    t0, zero, e32,m1,ta,ma \n\t"
				"fmv.w.x    ft11, zero         \n\t"
				"mv         t0,   %[BK]        \n\t"
				
				"flw        ft0,  0(%[PB])     \n\t"
				"vfmv.v.f   v16,  ft11         \n\t"
				"vfmv.v.f   v17,  ft11         \n\t"
				"flw        ft1,  4(%[PB])     \n\t"
				"vfmv.v.f   v18,  ft11         \n\t"
				"vfmv.v.f   v19,  ft11         \n\t"

				"flw        ft2,  8(%[PB])    \n\t"
				"vfmv.v.f   v20,  ft11         \n\t"
				"vfmv.v.f   v21,  ft11         \n\t"
				"flw        ft3,  12(%[PB])    \n\t"
				"vfmv.v.f   v22,  ft11         \n\t"
				"vfmv.v.f   v23,  ft11         \n\t"
                "add        %[PB], %[PB], 16   \n\t"

				"vfmv.v.f   v24,  ft11         \n\t"
				"vfmv.v.f   v25,  ft11         \n\t"
				"vle32.v    v0,   (%[PA])      \n\t"
				"add        %[PA], %[PA], 8*4  \n\t"
				"vfmv.v.f   v26,  ft11         \n\t"
				"vfmv.v.f   v27,  ft11         \n\t"
				
				"vfmv.v.f   v28,  ft11         \n\t"
				"vfmv.v.f   v29,  ft11         \n\t"
				"vle32.v    v1,   (%[PA])      \n\t"
				"add        %[PA], %[PA], 8*4  \n\t"
				"vfmv.v.f   v30,  ft11         \n\t"
				"vfmv.v.f   v31,  ft11         \n\t"
				
				"blez       t0,   M16x8_END     \n\t"

				".align 4                      \n\t"
				"M16x8_MAIN:                   \n\t"
                "srli       t1, t0, 1          \n\t"
                "blez       t1, M16x8_MAINTAIL \n\t"

                "M16x8_MAINLOOP:"
				"vl2r.v      v2,   (%[PA])     \n\t"
				"add        %[PA], %[PA], 8*8  \n\t"

				"vfmacc.vf  v16,  ft0,    v0    \n\t"
				"vfmacc.vf  v17,  ft0,    v1    \n\t"
				"flw        ft4,  0(%[PB])      \n\t"

				"vfmacc.vf  v18,  ft1,    v0    \n\t"
				"vfmacc.vf  v19,  ft1,    v1    \n\t"
				"flw        ft5,  4(%[PB])     \n\t"

				"vfmacc.vf  v20,  ft2,    v0    \n\t"
				"vfmacc.vf  v21,  ft2,    v1    \n\t"				
				"flw        ft6,  8(%[PB])     \n\t"
				
				"vfmacc.vf  v22,  ft3,    v0    \n\t"
				"vfmacc.vf  v23,  ft3,    v1    \n\t"
				"flw        ft7,  12(%[PB])     \n\t"

				"vfmacc.vf  v24,  ft4,    v0    \n\t"
				"vfmacc.vf  v25,  ft4,    v1    \n\t"
				"flw        ft0,  16(%[PB])     \n\t"

				"vfmacc.vf  v26,  ft5,    v0    \n\t"
				"vfmacc.vf  v27,  ft5,    v1    \n\t"
				"flw        ft1,  20(%[PB])     \n\t"

				"vfmacc.vf  v28,  ft6,    v0    \n\t"
				"vfmacc.vf  v29,  ft6,    v1    \n\t"
				"flw        ft2,  24(%[PB])     \n\t"

				"vfmacc.vf  v30,  ft7,    v0    \n\t"
				"vfmacc.vf  v31,  ft7,    v1    \n\t"
				"flw        ft3,  28(%[PB])     \n\t"

				"vl2r.v      v0,   (%[PA])     \n\t"
				"add        %[PA], %[PA], 8*8  \n\t"

				"vfmacc.vf  v16,  ft0,    v2    \n\t"
				"vfmacc.vf  v17,  ft0,    v3    \n\t"
				"flw        ft4,  32(%[PB])      \n\t"

				"vfmacc.vf  v18,  ft1,    v2    \n\t"
				"vfmacc.vf  v19,  ft1,    v3    \n\t"
				"flw        ft5,  36(%[PB])     \n\t"

				"vfmacc.vf  v20,  ft2,    v2    \n\t"
				"vfmacc.vf  v21,  ft2,    v3    \n\t"				
				"flw        ft6,  40(%[PB])     \n\t"
				
				"vfmacc.vf  v22,  ft3,    v2    \n\t"
				"vfmacc.vf  v23,  ft3,    v3    \n\t"
				"flw        ft7,  44(%[PB])     \n\t"

				"vfmacc.vf  v24,  ft4,    v2    \n\t"
				"vfmacc.vf  v25,  ft4,    v3    \n\t"
				"flw        ft0,  48(%[PB])     \n\t"

				"vfmacc.vf  v26,  ft5,    v2    \n\t"
				"vfmacc.vf  v27,  ft5,    v3    \n\t"
				"flw        ft1,  52(%[PB])     \n\t"

				"vfmacc.vf  v28,  ft6,    v2    \n\t"
				"vfmacc.vf  v29,  ft6,    v3    \n\t"
				"flw        ft2,  56(%[PB])     \n\t"

				"vfmacc.vf  v30,  ft7,    v2    \n\t"
				"vfmacc.vf  v31,  ft7,    v3    \n\t"
				"flw        ft3,  60(%[PB])     \n\t"
                "add        %[PB], %[PB], 64    \n\t"

				"addi       t1,   t1, -1        \n\t"
				"bgtz       t1,   M16x8_MAINLOOP \n\t"

                "andi       t1, t0, 1           \n\t"
                "blez       t1, M16x8_ALPHA      \n\t"

                "M16x8_MAINTAIL:"
				"vfmacc.vf  v16,  ft0,    v0    \n\t"
				"vfmacc.vf  v17,  ft0,    v1    \n\t"
				"flw        ft4,  0(%[PB])      \n\t"

				"vfmacc.vf  v18,  ft1,    v0    \n\t"
				"vfmacc.vf  v19,  ft1,    v1    \n\t"
				"flw        ft5,  4(%[PB])     \n\t"

				"vfmacc.vf  v20,  ft2,    v0    \n\t"
				"vfmacc.vf  v21,  ft2,    v1    \n\t"				
				"flw        ft6,  8(%[PB])     \n\t"
				
				"vfmacc.vf  v22,  ft3,    v0    \n\t"
				"vfmacc.vf  v23,  ft3,    v1    \n\t"
				"flw        ft7,  12(%[PB])     \n\t"

				"vfmacc.vf  v24,  ft4,    v0    \n\t"
				"vfmacc.vf  v25,  ft4,    v1    \n\t"
				"flw        ft0,  16(%[PB])     \n\t"

				"vfmacc.vf  v26,  ft5,    v0    \n\t"
				"vfmacc.vf  v27,  ft5,    v1    \n\t"
				"flw        ft1,  20(%[PB])     \n\t"

				"vfmacc.vf  v28,  ft6,    v0    \n\t"
				"vfmacc.vf  v29,  ft6,    v1    \n\t"
				"flw        ft2,  24(%[PB])     \n\t"

				"vfmacc.vf  v30,  ft7,    v0    \n\t"
				"vfmacc.vf  v31,  ft7,    v1    \n\t"
				"flw        ft3,  28(%[PB])     \n\t"
                "add        %[PB], %[PB], 64    \n\t"

				"vle32.v    v0,   (%[PA])      \n\t"
				"add        %[PA], %[PA], 64   \n\t"
				
				//Save result
				//load C
#if 1
				"M16x8_ALPHA:                   \n\t"
                "vsetvli    t0, zero, e32, m2,ta,ma  \n\t"
				"vle32.v    v0,   (%[C0])      \n\t"
				"vle32.v    v2,   (%[C1])      \n\t"
				
				//Multiply Alpha
				"vfmacc.vf  v0,   %[ALPHA], v16 \n\t"
				"vle32.v    v4,   (%[C2])       \n\t"

				"vfmacc.vf  v2,   %[ALPHA], v18 \n\t"
				"vle32.v    v6,   (%[C3])       \n\t"
				"vse32.v    v0,   (%[C0])       \n\t"

				"vfmacc.vf  v4,   %[ALPHA], v20 \n\t"
                "add        %[C0], %[C0], 64    \n\t"
				"vle32.v    v8,   (%[C4])       \n\t"
				"vse32.v    v2,   (%[C1])       \n\t"

				"vfmacc.vf  v6,   %[ALPHA], v22 \n\t"
                "add        %[C1], %[C1], 64    \n\t"
				"vle32.v    v10,  (%[C5])       \n\t"
				"vse32.v    v4,   (%[C2])       \n\t"

				"vfmacc.vf  v8,   %[ALPHA], v24 \n\t"
                "add        %[C2], %[C2], 64    \n\t"
				"vle32.v    v12,  (%[C6])       \n\t"
				"vse32.v    v6,   (%[C3])       \n\t"

				"vfmacc.vf  v10,  %[ALPHA], v26 \n\t"
                "add        %[C3], %[C3], 64    \n\t"
				"vle32.v    v14,   (%[C7])      \n\t"
				"vse32.v    v8,   (%[C4])       \n\t"
				
				"vfmacc.vf  v12,  %[ALPHA], v28 \n\t"
                "add        %[C4], %[C4], 64    \n\t"
				"vse32.v    v10,   (%[C5])      \n\t"
				"vfmacc.vf  v14,  %[ALPHA], v30 \n\t"
                "add        %[C5], %[C5], 64    \n\t"
				"vse32.v    v12,   (%[C6])      \n\t"
				"vse32.v    v14,   (%[C7])      \n\t"
                "add        %[C6], %[C6], 64    \n\t"
                "add        %[C7], %[C7], 64    \n\t"

				"M16x8_END:                     \n\t"

				"add        %[PA], %[PA], -64   \n\t"
				"add        %[PB], %[PB], -64   \n\t"
				
				:[C0]"+r"(C0),[C1]"+r"(C1),[C2]"+r"(C2),[C3]"+r"(C3),
				 [C4]"+r"(C4),[C5]"+r"(C5),[C6]"+r"(C6),[C7]"+r"(C7),
				 [PA]"+r"(ptrba), [PB]"+r"(ptrbb)
				:[ALPHA]"f"(alpha), [BK]"r"(bk)
				:"cc", "t0", "t1", "t4","t5","t6","t3",
				 "ft11", "ft0", "ft1", "ft2","ft3","ft4", "ft5", "ft6","ft7",
				 "v0", "v1", "v2", "v3",
				 "v4", "v5", "v6", "v7",
				 "v16", "v17", "v18", "v19", "v20", "v21", "v22", "v23",
				 "v24", "v25", "v26", "v27", "v28", "v29", "v30", "v31");
#else
				"M8x8_ALPHA:                    \n\t"
				"vsetvli    t4,   zero, e32, m8,ta,ma \n\t"
				"vle32.v    v0,   (%[C0])       \n\t"
				"vfmacc.vf  v0,   %[ALPHA], v16 \n\t"
				"vle32.v    v8,   (%[C4])       \n\t"
				"vfmacc.vf  v8,   %[ALPHA], v24 \n\t"
				"vse32.v    v0,   (%[C0])       \n\t"
				"vse32.v    v8,   (%[C4])       \n\t"
                "add        %[C0], %[C0], 16*4  \n\t"
                "add        %[C4], %[C4], 16*4  \n\t"
				"M8x8_END:                      \n\t"
				"add        %[PA], %[PA], -32   \n\t"
				"add        %[PB], %[PB], -16   \n\t"

				:[C0]"+r"(C0),[C4]"+r"(C4),
				 [PA]"+r"(ptrba), [PB]"+r"(ptrbb)
				:[ALPHA]"f"(alpha), [BK]"r"(bk)
				:"cc", "t0", "t1", "t4","t5","t6","t3",
				 "ft11", "ft0", "ft1", "ft2","ft3","ft4", "ft5", "ft6","ft7",
				 "v0", "v1", "v2", "v3",
				 "v4", "v5", "v6", "v7",
				 "v16", "v17", "v18", "v19", "v20", "v21", "v22", "v23",
				 "v24", "v25", "v26", "v27", "v28", "v29", "v30", "v31");

#endif
	   }

	   if(bm&8){
		   ptrbb = bb;
		   //t0 for k
		   //ft0-ft7 for B
		   //v0-v1 for A
		   //v16-v31 for temp C

	   	   asm volatile(
				"vsetvli    t0, zero, e32,m1,ta,ma   \n\t"
				"fmv.w.x    ft11, zero         \n\t"
				"mv         t0,   %[BK]        \n\t"
				
				"vfmv.v.f   v16,  ft11         \n\t"
				"vfmv.v.f   v18,  ft11         \n\t"
				"vfmv.v.f   v20,  ft11         \n\t"
				"vfmv.v.f   v22,  ft11         \n\t"

				"vfmv.v.f   v24,  ft11         \n\t"
				"vfmv.v.f   v26,  ft11         \n\t"
				"vfmv.v.f   v28,  ft11         \n\t"
				"vfmv.v.f   v30,  ft11         \n\t"
				
				"blez       t0,   M8x8_END     \n\t"
				".align 4                      \n\t"
				"M8x8_MAINLOOP:                \n\t"
				"flw        ft0,  0(%[PB])     \n\t"
				"flw        ft1,  4(%[PB])     \n\t"

				"vle32.v    v0,   (%[PA])      \n\t"
				"add        %[PA], %[PA], 8*4  \n\t"
				
				"vfmacc.vf  v16,  ft0,    v0   \n\t"
				"flw        ft2,  8(%[PB])     \n\t"

				"vfmacc.vf  v18,  ft1,    v0    \n\t"
				"flw        ft3,  12(%[PB])     \n\t"

				"vfmacc.vf  v20,  ft2,    v0    \n\t"
				"flw        ft0,  16(%[PB])     \n\t"
				
				"vfmacc.vf  v22,  ft3,    v0   \n\t"
				"flw        ft1,  20(%[PB])    \n\t"

				"vfmacc.vf  v24,  ft0,    v0   \n\t"
				"flw        ft2,  24(%[PB])    \n\t"

				"vfmacc.vf  v26,  ft1,    v0    \n\t"
				"flw        ft3,  28(%[PB])     \n\t"

				"vfmacc.vf  v28,  ft2,    v0    \n\t"
				"vfmacc.vf  v30,  ft3,    v0    \n\t"
                "add        %[PB], %[PB], 32    \n\t"

				"addi       t0,   t0, -1       \n\t"
				"bgtz       t0,   M8x8_MAINLOOP \n\t"
				
				//Save result
				//load C
				"vle32.v    v0,   (%[C0])      \n\t"
				"vle32.v    v1,   (%[C1])      \n\t"
				"vle32.v    v2,   (%[C2])      \n\t"
				"vle32.v    v3,   (%[C3])      \n\t"
				
				//Multiply Alpha
				"vfmacc.vf  v0,   %[ALPHA], v16 \n\t"
				"vfmacc.vf  v1,   %[ALPHA], v18 \n\t"
				"vfmacc.vf  v2,   %[ALPHA], v20 \n\t"
				"vfmacc.vf  v3,   %[ALPHA], v22 \n\t"

				"vse32.v    v0,   (%[C0])      \n\t"
				"add        %[C0], %[C0], 8*4  \n\t"
				"vse32.v    v1,   (%[C1])      \n\t"
				"add        %[C1], %[C1], 8*4  \n\t"
				
				"vse32.v    v2,   (%[C2])      \n\t"
				"add        %[C2], %[C2], 8*4  \n\t"
				"vse32.v    v3,   (%[C3])      \n\t"
				"add        %[C3], %[C3], 8*4  \n\t"

				"vle32.v    v4,   (%[C4])      \n\t"
				"vle32.v    v5,   (%[C5])      \n\t"
				"vle32.v    v6,   (%[C6])      \n\t"
				"vle32.v    v7,   (%[C7])      \n\t"

				"vfmacc.vf  v4,   %[ALPHA], v24 \n\t"
				"vfmacc.vf  v5,   %[ALPHA], v26 \n\t"
				"vfmacc.vf  v6,   %[ALPHA], v28 \n\t"
				"vfmacc.vf  v7,   %[ALPHA], v30 \n\t"


				"vse32.v    v4,   (%[C4])      \n\t"
				"add        %[C4], %[C4], 8*4  \n\t"
				"vse32.v    v5,   (%[C5])      \n\t"
				"add        %[C5], %[C5], 8*4  \n\t"

				"vse32.v    v6,   (%[C6])      \n\t"
				"add        %[C6], %[C6], 8*4  \n\t"
				"vse32.v    v7,   (%[C7])      \n\t"
				"add        %[C7], %[C7], 8*4  \n\t"

				"M8x8_END:                     \n\t"
				
				:[C0]"+r"(C0),[C1]"+r"(C1),[C2]"+r"(C2),[C3]"+r"(C3),
				 [C4]"+r"(C4),[C5]"+r"(C5),[C6]"+r"(C6),[C7]"+r"(C7),
				 [PA]"+r"(ptrba), [PB]"+r"(ptrbb)
				:[ALPHA]"f"(alpha), [BK]"r"(bk)
				:"cc", "t0", 
				 "ft11", "ft0", "ft1", "ft2","ft3",
				 "v0", "v1", "v2", "v3",
				 "v4", "v5", "v6", "v7",
				 "v16", "v18", "v20", "v22", 
				 "v24", "v26", "v28",  "v30");
	   }
	   if(bm&4){
		   ptrbb = bb;
	   	   asm volatile(
                "li         t0, 4              \n\t"
				"vsetvli    t0, t0, e32,m1,ta,ma     \n\t"
				"fmv.w.x    ft11, zero         \n\t"
				"mv         t0,   %[BK]        \n\t"
				
				"vfmv.v.f   v16,  ft11         \n\t"
				"vfmv.v.f   v18,  ft11         \n\t"
				"vfmv.v.f   v20,  ft11         \n\t"
				"vfmv.v.f   v22,  ft11         \n\t"

				"vfmv.v.f   v24,  ft11         \n\t"
				"vfmv.v.f   v26,  ft11         \n\t"
				"vfmv.v.f   v28,  ft11         \n\t"
				"vfmv.v.f   v30,  ft11         \n\t"
				
				"blez       t0,   M4x7_END     \n\t"
				".align 4                      \n\t"
				"M4x7_MAINLOOP:                \n\t"
				"flw        ft0,  0(%[PB])     \n\t"
				"flw        ft1,  4(%[PB])     \n\t"

				"vle32.v    v0,   (%[PA])      \n\t"
				"add        %[PA], %[PA], 4*4  \n\t"
				
				"vfmacc.vf  v16,  ft0,    v0   \n\t"
				"flw        ft2,  8(%[PB])     \n\t"

				"vfmacc.vf  v18,  ft1,    v0    \n\t"
				"flw        ft3,  12(%[PB])     \n\t"

				"vfmacc.vf  v20,  ft2,    v0    \n\t"
				"flw        ft0,  16(%[PB])     \n\t"
				
				"vfmacc.vf  v22,  ft3,    v0   \n\t"
				"flw        ft1,  20(%[PB])    \n\t"

				"vfmacc.vf  v24,  ft0,    v0   \n\t"
				"flw        ft2,  24(%[PB])    \n\t"

				"vfmacc.vf  v26,  ft1,    v0    \n\t"
				"flw        ft3,  28(%[PB])     \n\t"

				"vfmacc.vf  v28,  ft2,    v0    \n\t"
				"vfmacc.vf  v30,  ft3,    v0    \n\t"
                "add        %[PB], %[PB], 32    \n\t"

				"addi       t0,   t0, -1       \n\t"
				"bgtz       t0,   M4x7_MAINLOOP \n\t"
				
				//Save result
				//load C
				"vle32.v    v0,   (%[C0])      \n\t"
				"vle32.v    v1,   (%[C1])      \n\t"
				"vle32.v    v2,   (%[C2])      \n\t"
				"vle32.v    v3,   (%[C3])      \n\t"
				
				//Multiply Alpha
				"vfmacc.vf  v0,   %[ALPHA], v16 \n\t"
				"vfmacc.vf  v1,   %[ALPHA], v18 \n\t"
				"vfmacc.vf  v2,   %[ALPHA], v20 \n\t"
				"vfmacc.vf  v3,   %[ALPHA], v22 \n\t"

				"vse32.v    v0,   (%[C0])      \n\t"
				"add        %[C0], %[C0], 4*4  \n\t"
				"vse32.v    v1,   (%[C1])      \n\t"
				"add        %[C1], %[C1], 4*4  \n\t"
				
				"vse32.v    v2,   (%[C2])      \n\t"
				"add        %[C2], %[C2], 4*4  \n\t"
				"vse32.v    v3,   (%[C3])      \n\t"
				"add        %[C3], %[C3], 4*4  \n\t"

				"vle32.v    v4,   (%[C4])      \n\t"
				"vle32.v    v5,   (%[C5])      \n\t"
				"vle32.v    v6,   (%[C6])      \n\t"
				"vle32.v    v7,   (%[C7])      \n\t"

				"vfmacc.vf  v4,   %[ALPHA], v24 \n\t"
				"vfmacc.vf  v5,   %[ALPHA], v26 \n\t"
				"vfmacc.vf  v6,   %[ALPHA], v28 \n\t"
				"vfmacc.vf  v7,   %[ALPHA], v30 \n\t"


				"vse32.v    v4,   (%[C4])      \n\t"
				"add        %[C4], %[C4], 4*4  \n\t"
				"vse32.v    v5,   (%[C5])      \n\t"
				"add        %[C5], %[C5], 4*4  \n\t"

				"vse32.v    v6,   (%[C6])      \n\t"
				"add        %[C6], %[C6], 4*4  \n\t"
				"vse32.v    v7,   (%[C7])      \n\t"
				"add        %[C7], %[C7], 4*4  \n\t"

				"M4x7_END:                     \n\t"
				
				:[C0]"+r"(C0),[C1]"+r"(C1),[C2]"+r"(C2),[C3]"+r"(C3),
				 [C4]"+r"(C4),[C5]"+r"(C5),[C6]"+r"(C6),[C7]"+r"(C7),
				 [PA]"+r"(ptrba), [PB]"+r"(ptrbb)
				:[ALPHA]"f"(alpha), [BK]"r"(bk)
				:"cc", "t0", 
				 "ft11", "ft0", "ft1", "ft2","ft3",
				 "v0", "v1", "v2", "v3",
				 "v4", "v5", "v6", "v7",
				 "v16", "v18", "v20", "v22", 
				 "v24", "v26", "v28",  "v30");
       }
#if 1
	   if(bm&2){
		   ptrbb = bb;
		   res0 = 0;
		   res1 = 0;
		   res2 = 0;
		   res3 = 0;
		   res4 = 0;
		   res5 = 0;
		   res6 = 0;
		   res7 = 0;
		   res8 = 0;
		   res9 = 0;
		   res10 = 0;
		   res11 = 0;
		   res12 = 0;
		   res13 = 0;
		   res14 = 0;
		   res15 = 0;
		   
		   for(k=0; k<bk; k+=1){
			   loadb0 = ptrbb[0];
			   loadb1 = ptrbb[1];
			   loadb2 = ptrbb[2];
			   loadb3 = ptrbb[3];
			   
			   loadb4 = ptrbb[4];
			   loadb5 = ptrbb[5];
			   loadb6 = ptrbb[6];
			   loadb7 = ptrbb[7];

			   load0 = ptrba[0];
			   load1 = ptrba[1];
				   
			   res0 = res0 + load0 * loadb0;
			   res1 = res1 + load1 * loadb0;
			   
			   res2 = res2 + load0 * loadb1;
			   res3 = res3 + load1 * loadb1;

			   res4 = res4 + load0 * loadb2;
			   res5 = res5 + load1 * loadb2;
			   
			   res6 = res6 + load0 * loadb3;
			   res7 = res7 + load1 * loadb3;

   			   res8 = res8 + load0 * loadb4;
			   res9 = res9 + load1 * loadb4;
			   
			   res10 = res10 + load0 * loadb5;
			   res11 = res11 + load1 * loadb5;

			   res12 = res12 + load0 * loadb6;
			   res13 = res13 + load1 * loadb6;
			   
			   res14 = res14 + load0 * loadb7;
			   res15 = res15 + load1 * loadb7;

			   ptrba += 2;
			   ptrbb += 8;
		   }
		   
      		   res0 = res0 * alpha;
		   res1 = res1 * alpha;
		   res2 = res2 * alpha;
		   res3 = res3 * alpha;
		   res4 = res4 * alpha;
		   res5 = res5 * alpha;
		   res6 = res6 * alpha;
		   res7 = res7 * alpha;

       		   res8 = res8 * alpha;
		   res9 = res9 * alpha;
		   res10 = res10 * alpha;
		   res11 = res11 * alpha;
		   res12 = res12 * alpha;
		   res13 = res13 * alpha;
		   res14 = res14 * alpha;
		   res15 = res15 * alpha;

		   C0[0] += res0;
		   C0[1] += res1;
		   
		   C1[0] += res2;
		   C1[1] += res3;
		   
		   C2[0] += res4;
		   C2[1] += res5;
		   
		   C3[0] += res6;
		   C3[1] += res7;

   		   C4[0] += res8;
		   C4[1] += res9;
		   
		   C5[0] += res10;
		   C5[1] += res11;
		   
		   C6[0] += res12;
		   C6[1] += res13;
		   
		   C7[0] += res14;
		   C7[1] += res15;

		   C0 += 2;
		   C1 += 2;
		   C2 += 2;
		   C3 += 2;

   		   C4 += 2;
		   C5 += 2;
		   C6 += 2;
		   C7 += 2;
	   }
	   if(bm&1){
   		   ptrbb = bb;
		   res0 = 0;
		   res2 = 0;
		   res4 = 0;
		   res6 = 0;
		   res8 = 0;
		   res10 = 0;
		   res12 = 0;
		   res14 = 0;
		   
		   for(k=0; k<bk; k+=1){
			   loadb0 = ptrbb[0];
			   loadb1 = ptrbb[1];
			   loadb2 = ptrbb[2];
			   loadb3 = ptrbb[3];
			   
			   loadb4 = ptrbb[4];
			   loadb5 = ptrbb[5];
			   loadb6 = ptrbb[6];
			   loadb7 = ptrbb[7];

			   load0 = ptrba[0];
				   
			   res0 = res0 + load0 * loadb0;
			   res2 = res2 + load0 * loadb1;
			   res4 = res4 + load0 * loadb2;
			   res6 = res6 + load0 * loadb3;

   			   res8 = res8 + load0 * loadb4;
			   res10 = res10 + load0 * loadb5;
			   res12 = res12 + load0 * loadb6;
			   res14 = res14 + load0 * loadb7;

			   ptrba += 1;
			   ptrbb += 8;
		   }
		   
      		   res0 = res0 * alpha;
		   res2 = res2 * alpha;
		   res4 = res4 * alpha;
		   res6 = res6 * alpha;

       		   res8 = res8 * alpha;
		   res10 = res10 * alpha;
		   res12 = res12 * alpha;
		   res14 = res14 * alpha;


		   C0[0] += res0;
		   C1[0] += res2;
		   C2[0] += res4;
		   C3[0] += res6;

   		   C4[0] += res8;
		   C5[0] += res10;
		   C6[0] += res12;
		   C7[0] += res14;

		   C0 += 1;
		   C1 += 1;
		   C2 += 1;
		   C3 += 1;

   		   C4 += 1;
		   C5 += 1;
		   C6 += 1;
		   C7 += 1;
	   }
#endif
   	   k = bk<<3;
	   bb = bb+k;
	   i = ldc<<3;
	   C = C+i;
   }
   
   if (bn&4){
	   C0 = C;
	   C1 = C0+ldc;
	   C2 = C1+ldc;
	   C3 = C2+ldc;

	   ptrba = ba;
	   for(i=0; i<bm/16; i+=1){
		   ptrbb = bb;
		   //t0 for k
		   //ft0-ft3 for B
		   //v0-v3 for A
		   //v16-v23 for temp C
   	   	   asm volatile(
				"vsetvli    t0, zero, e32,m1,ta,ma \n\t"
				"fmv.w.x    ft11, zero         \n\t"
				"mv         t0,   %[BK]        \n\t"
				
				"vfmv.v.f   v16,  ft11         \n\t"
				"vfmv.v.f   v17,  ft11         \n\t"
				"vfmv.v.f   v18,  ft11         \n\t"
				"vfmv.v.f   v19,  ft11         \n\t"

				"vfmv.v.f   v20,  ft11         \n\t"
				"vfmv.v.f   v21,  ft11         \n\t"
				"vfmv.v.f   v22,  ft11         \n\t"
				"vfmv.v.f   v23,  ft11         \n\t"

				"blez       t0,   M8x4_END     \n\t"
				".align 4                      \n\t"
				"M8x4_MAINLOOP:                \n\t"
				"flw        ft0,  0(%[PB])     \n\t"
				//"add        %[PB], %[PB], 4    \n\t"
				"flw        ft1,  4(%[PB])     \n\t"
				//"add        %[PB], %[PB], 4    \n\t"

				"vle32.v    v0,   (%[PA])      \n\t"
				"add        %[PA], %[PA], 8*4  \n\t"
				"vle32.v    v1,   (%[PA])      \n\t"
				"add        %[PA], %[PA], 8*4  \n\t"
				
				"vfmacc.vf  v16,  ft0,    v0    \n\t"
				"vfmacc.vf  v17,  ft0,    v1    \n\t"
				"flw        ft2,  8(%[PB])      \n\t"
				//"add        %[PB], %[PB], 4    \n\t"


				"vfmacc.vf  v18,  ft1,    v0    \n\t"
				"vfmacc.vf  v19,  ft1,    v1    \n\t"
				"flw        ft3,  12(%[PB])     \n\t"
				//"add        %[PB], %[PB], 4    \n\t"
				

				"vfmacc.vf  v20,  ft2,    v0    \n\t"
				"vfmacc.vf  v21,  ft2,    v1    \n\t"				
				"vfmacc.vf  v22,  ft3,    v0    \n\t"
				"vfmacc.vf  v23,  ft3,    v1    \n\t"
                "add        %[PB], %[PB], 16    \n\t"

				"addi       t0,   t0, -1       \n\t"
				"bgtz       t0,   M8x4_MAINLOOP \n\t"
				
				//Save result
				//load C
				"vle32.v    v0,   (%[C0])      \n\t"
				"addi       t4,   %[C0], 8*4   \n\t"
				"vle32.v    v1,   (%[C1])      \n\t"
				"addi       t5,   %[C1], 8*4   \n\t"
				"vle32.v    v2,   (%[C2])      \n\t"
				"addi       t6,   %[C2], 8*4   \n\t"
				"vle32.v    v3,   (%[C3])      \n\t"
				"addi       t3,   %[C3], 8*4   \n\t"
				
				//Multiply Alpha
				"vfmacc.vf  v0,   %[ALPHA], v16 \n\t"
				"vle32.v    v4,   (t4)          \n\t"
				"vfmacc.vf  v1,   %[ALPHA], v18 \n\t"
				"vle32.v    v5,   (t5)          \n\t"
				"vfmacc.vf  v2,   %[ALPHA], v20 \n\t"
				"vle32.v    v6,   (t6)          \n\t"
				"vfmacc.vf  v3,   %[ALPHA], v22 \n\t"
				"vle32.v    v7,   (t3)          \n\t"

				"vfmacc.vf  v4,   %[ALPHA], v17 \n\t"
				"vse32.v    v0,   (%[C0])      \n\t"
				"add        %[C0], %[C0], 16*4  \n\t"
				"vfmacc.vf  v5,   %[ALPHA], v19 \n\t"
				"vse32.v    v1,   (%[C1])      \n\t"
				"add        %[C1], %[C1], 16*4  \n\t"
				
				"vfmacc.vf  v6,   %[ALPHA], v21 \n\t"
				"vse32.v    v2,   (%[C2])      \n\t"
				"add        %[C2], %[C2], 16*4  \n\t"

				"vfmacc.vf  v7,   %[ALPHA], v23 \n\t"
				"vse32.v    v3,   (%[C3])      \n\t"
				"add        %[C3], %[C3], 16*4  \n\t"

				"vse32.v    v4,   (t4)         \n\t"
				"vse32.v    v5,   (t5)         \n\t"
				"vse32.v    v6,   (t6)         \n\t"
				"vse32.v    v7,   (t3)         \n\t"
				"M8x4_END:                     \n\t"
				
				:[C0]"+r"(C0),[C1]"+r"(C1),[C2]"+r"(C2),[C3]"+r"(C3),
				 [PA]"+r"(ptrba), [PB]"+r"(ptrbb)
				:[ALPHA]"f"(alpha), [BK]"r"(bk)
				:"cc", "t0", "t4","t5","t6","t3",
				 "ft11", "ft0", "ft1", "ft2","ft3",
				 "v0", "v1", "v2", "v3",
				 "v4", "v5", "v6", "v7",
				 "v16", "v17", "v18", "v19", "v20", "v21", "v22", "v23");

	   }
	   if(bm&8){
		   ptrbb = bb;
		   //t0 for k
		   //ft0-ft7 for B
		   //v0-v1 for A
		   //v16-v31 for temp C

	   	   asm volatile(
				"vsetvli    t0, zero, e32,m1,ta,ma   \n\t"
				"fmv.w.x    ft11, zero         \n\t"
				"mv         t0,   %[BK]        \n\t"
				
				"vfmv.v.f   v16,  ft11         \n\t"
				"vfmv.v.f   v18,  ft11         \n\t"
				"vfmv.v.f   v20,  ft11         \n\t"
				"vfmv.v.f   v22,  ft11         \n\t"

				"blez       t0,   M4x8_END     \n\t"
				".align 4                      \n\t"
				"M4x8_MAINLOOP:                \n\t"
				"flw        ft0,  0(%[PB])     \n\t"
				"flw        ft1,  4(%[PB])     \n\t"

				"vle32.v    v0,   (%[PA])      \n\t"
				"add        %[PA], %[PA], 8*4  \n\t"
				
				"vfmacc.vf  v16,  ft0,    v0   \n\t"
				"flw        ft2,  8(%[PB])     \n\t"

				"vfmacc.vf  v18,  ft1,    v0    \n\t"
				"flw        ft3,  12(%[PB])     \n\t"

				"vfmacc.vf  v20,  ft2,    v0    \n\t"
				
				"vfmacc.vf  v22,  ft3,    v0    \n\t"
                "add        %[PB], %[PB], 16   \n\t"

				"addi       t0,   t0, -1       \n\t"
				"bgtz       t0,   M4x8_MAINLOOP \n\t"
				
				//Save result
				//load C
				"vle32.v    v0,   (%[C0])      \n\t"
				"vle32.v    v1,   (%[C1])      \n\t"
				"vle32.v    v2,   (%[C2])      \n\t"
				"vle32.v    v3,   (%[C3])      \n\t"
				
				//Multiply Alpha
				"vfmacc.vf  v0,   %[ALPHA], v16 \n\t"
				"vfmacc.vf  v1,   %[ALPHA], v18 \n\t"
				"vfmacc.vf  v2,   %[ALPHA], v20 \n\t"
				"vfmacc.vf  v3,   %[ALPHA], v22 \n\t"

				"vse32.v    v0,   (%[C0])      \n\t"
				"add        %[C0], %[C0], 8*4  \n\t"
				"vse32.v    v1,   (%[C1])      \n\t"
				"add        %[C1], %[C1], 8*4  \n\t"
				
				"vse32.v    v2,   (%[C2])      \n\t"
				"add        %[C2], %[C2], 8*4  \n\t"
				"vse32.v    v3,   (%[C3])      \n\t"
				"add        %[C3], %[C3], 8*4  \n\t"

				"M4x8_END:                     \n\t"
				
				:[C0]"+r"(C0),[C1]"+r"(C1),[C2]"+r"(C2),[C3]"+r"(C3),
				 [C4]"+r"(C4),[C5]"+r"(C5),[C6]"+r"(C6),[C7]"+r"(C7),
				 [PA]"+r"(ptrba), [PB]"+r"(ptrbb)
				:[ALPHA]"f"(alpha), [BK]"r"(bk)
				:"cc", "t0", 
				 "ft11", "ft0", "ft1", "ft2","ft3",
				 "v0", "v1", "v2", "v3",
				 "v16", "v18", "v20", "v22");
	   }

	   if(bm&4){
		   ptrbb = bb;
      		res0 = 0;
		   res1 = 0;
		   res2 = 0;
		   res3 = 0;
		   res4 = 0;
		   res5 = 0;
		   res6 = 0;
		   res7 = 0;
		   res8 = 0;
		   res9 = 0;
		   res10 = 0;
		   res11 = 0;
		   res12 = 0;
		   res13 = 0;
		   res14 = 0;
		   res15 = 0;
		   
		   for(k=0; k<bk; k+=1){
			   loadb0 = ptrbb[0];
			   loadb1 = ptrbb[1];

			   load0 = ptrba[0];
			   load1 = ptrba[1];
			   load2 = ptrba[2];
			   load3 = ptrba[3];
				   
			   res0 = res0 + load0 * loadb0;
			   res1 = res1 + load1 * loadb0;
			   res2 = res2 + load2 * loadb0;
			   res3 = res3 + load3 * loadb0;

			   res4 = res4 + load0 * loadb1;
			   res5 = res5 + load1 * loadb1;
			   res6 = res6 + load2 * loadb1;
			   res7 = res7 + load3 * loadb1;

			   loadb2 = ptrbb[2];
			   loadb3 = ptrbb[3];
			   
   			   res8 = res8 + load0 * loadb2;
			   res9 = res9 + load1 * loadb2;
			   res10 = res10 + load2 * loadb2;
			   res11 = res11 + load3 * loadb2;

			   res12 = res12 + load0 * loadb3;
			   res13 = res13 + load1 * loadb3;
			   res14 = res14 + load2 * loadb3;
			   res15 = res15 + load3 * loadb3;

			   ptrba += 4;
			   ptrbb += 4;
		   }
		   
      		   res0 = res0 * alpha;
		   res1 = res1 * alpha;
		   res2 = res2 * alpha;
		   res3 = res3 * alpha;
		   res4 = res4 * alpha;
		   res5 = res5 * alpha;
		   res6 = res6 * alpha;
		   res7 = res7 * alpha;

       		   res8 = res8 * alpha;
		   res9 = res9 * alpha;
		   res10 = res10 * alpha;
		   res11 = res11 * alpha;
		   res12 = res12 * alpha;
		   res13 = res13 * alpha;
		   res14 = res14 * alpha;
		   res15 = res15 * alpha;

		   C0[0] += res0;
		   C0[1] += res1;
		   C0[2] += res2;
		   C0[3] += res3;
		   
		   C1[0] += res4;
		   C1[1] += res5;
		   C1[2] += res6;
		   C1[3] += res7;

   		   C2[0] += res8;
		   C2[1] += res9;
		   C2[2] += res10;
		   C2[3] += res11;
		   
		   C3[0] += res12;
		   C3[1] += res13;
		   C3[2] += res14;
		   C3[3] += res15;

		   C0 += 4;
		   C1 += 4;
		   C2 += 4;
		   C3 += 4;
	   }
   	   if(bm&2){
		   ptrbb = bb;
		   
       		   res0 = 0;
		   res1 = 0;
		   
		   res4 = 0;
		   res5 = 0;
		   
		   res8 = 0;
		   res9 = 0;
		   
		   res12 = 0;
		   res13 = 0;
		   
		   for(k=0; k<bk; k+=1){
			   loadb0 = ptrbb[0];
			   loadb1 = ptrbb[1];

			   load0 = ptrba[0];
			   load1 = ptrba[1];
				   
			   res0 = res0 + load0 * loadb0;
			   res1 = res1 + load1 * loadb0;

			   res4 = res4 + load0 * loadb1;
			   res5 = res5 + load1 * loadb1;

			   loadb2 = ptrbb[2];
			   loadb3 = ptrbb[3];
			   
   			   res8 = res8 + load0 * loadb2;
			   res9 = res9 + load1 * loadb2;

			   res12 = res12 + load0 * loadb3;
			   res13 = res13 + load1 * loadb3;

			   ptrba += 2;
			   ptrbb += 4;
		   }
		   
      		   res0 = res0 * alpha;
		   res1 = res1 * alpha;

		   res4 = res4 * alpha;
		   res5 = res5 * alpha;

       		   res8 = res8 * alpha;
		   res9 = res9 * alpha;

		   res12 = res12 * alpha;
		   res13 = res13 * alpha;

		   C0[0] += res0;
		   C0[1] += res1;

		   C1[0] += res4;
		   C1[1] += res5;

   		   C2[0] += res8;
		   C2[1] += res9;
		   
		   C3[0] += res12;
		   C3[1] += res13;

		   C0 += 2;
		   C1 += 2;
		   C2 += 2;
		   C3 += 2;
	   }
	   if(bm&1){
		   ptrbb = bb;
		   		   
       		   res0 = 0;
		   
		   res4 = 0;
		   
		   res8 = 0;
		   
		   res12 = 0;
		   
		   for(k=0; k<bk; k+=1){
			   loadb0 = ptrbb[0];
			   loadb1 = ptrbb[1];

			   load0 = ptrba[0];
				   
			   res0 = res0 + load0 * loadb0;

			   res4 = res4 + load0 * loadb1;

			   loadb2 = ptrbb[2];
			   loadb3 = ptrbb[3];
			   
   			   res8 = res8 + load0 * loadb2;

			   res12 = res12 + load0 * loadb3;

			   ptrba += 1;
			   ptrbb += 4;
		   }
		   
      		   res0 = res0 * alpha;

		   res4 = res4 * alpha;

       		   res8 = res8 * alpha;

		   res12 = res12 * alpha;

		   C0[0] += res0;
		   C1[0] += res4;
   		   C2[0] += res8;
		   C3[0] += res12;

		   C0 += 1;
		   C1 += 1;
		   C2 += 1;
		   C3 += 1;
	   }
	   
	   k = bk<<2;
	   bb = bb+k;
	   i = ldc<<2;
	   C = C+i;
   }
   
   if(bn&2){
	   C0 = C;
	   C1 = C0+ldc;

	   ptrba = ba;
	   for(i=0; i<bm/16; i+=1){
		   ptrbb = bb;
   		   res0 = 0;
		   res1 = 0;
		   res2 = 0;
		   res3 = 0;
		   res4 = 0;
		   res5 = 0;
		   res6 = 0;
		   res7 = 0;
		   res8 = 0;
		   res9 = 0;
		   res10 = 0;
		   res11 = 0;
		   res12 = 0;
		   res13 = 0;
		   res14 = 0;
		   res15 = 0;
		   res16 = 0;
		   res17 = 0;
		   res18 = 0;
		   res19 = 0;
		   res20 = 0;
		   res21 = 0;
		   res22 = 0;
		   res24 = 0;
		   res23 = 0;
		   res25 = 0;
		   res26 = 0;
		   res27 = 0;
		   res28 = 0;
		   res29 = 0;
		   res30 = 0;
		   res31 = 0;
		   
		   for(k=0; k<bk; k+=1){
			   loadb0 = ptrbb[0];
			   loadb1 = ptrbb[1];

			   load0 = ptrba[0];
			   load1 = ptrba[1];
			   load2 = ptrba[2];
			   load3 = ptrba[3];
			   load4 = ptrba[4];
			   load5 = ptrba[5];
			   load6 = ptrba[6];
			   load7 = ptrba[7];
			   load8 = ptrba[8];
			   load9 = ptrba[9];
			   load10 = ptrba[10];
			   load11 = ptrba[11];
			   load12 = ptrba[12];
			   load13 = ptrba[13];
			   load14 = ptrba[14];
			   load15 = ptrba[15];
				   
			   res0 = res0 + load0 * loadb0;
			   res1 = res1 + load1 * loadb0;
			   res2 = res2 + load2 * loadb0;
			   res3 = res3 + load3 * loadb0;

			   res4 = res4 + load4 * loadb0;
			   res5 = res5 + load5 * loadb0;
			   res6 = res6 + load6 * loadb0;
			   res7 = res7 + load7 * loadb0;

			   res8 = res8 + load8 * loadb0;
			   res9 = res9 + load9 * loadb0;
			   res10 = res10 + load10 * loadb0;
			   res11 = res11 + load11 * loadb0;

			   res12 = res12 + load12 * loadb0;
			   res13 = res13 + load13 * loadb0;
			   res14 = res14 + load14 * loadb0;
			   res15 = res15 + load15 * loadb0;

   			   res16 = res16 + load0 * loadb1;
			   res17 = res17 + load1 * loadb1;
			   res18 = res18 + load2 * loadb1;
			   res19 = res19 + load3 * loadb1;

			   res20 = res20 + load4 * loadb1;
			   res21 = res21 + load5 * loadb1;
			   res22 = res22 + load6 * loadb1;
			   res23 = res23 + load7 * loadb1;

			   res24 = res24 + load8 * loadb1;
			   res25 = res25 + load9 * loadb1;
			   res26 = res26 + load10 * loadb1;
			   res27 = res27 + load11 * loadb1;

			   res28 = res28 + load12 * loadb1;
			   res29 = res29 + load13 * loadb1;
			   res30 = res30 + load14 * loadb1;
			   res31 = res31 + load15 * loadb1;

			   ptrba += 16;
			   ptrbb += 2;
		   }
		   
      	   res0 = res0 * alpha;
		   res1 = res1 * alpha;
		   res2 = res2 * alpha;
		   res3 = res3 * alpha;
		   res4 = res4 * alpha;
		   res5 = res5 * alpha;
		   res6 = res6 * alpha;
		   res7 = res7 * alpha;

       	   res8 = res8 * alpha;
		   res9 = res9 * alpha;
		   res10 = res10 * alpha;
		   res11 = res11 * alpha;
		   res12 = res12 * alpha;
		   res13 = res13 * alpha;
		   res14 = res14 * alpha;
		   res15 = res15 * alpha;

		   res16 = res16 * alpha;
		   res17 = res17 * alpha;
		   res18 = res18 * alpha;
		   res19 = res19 * alpha;
		   res20 = res20 * alpha;
		   res21 = res21 * alpha;
		   res22 = res22 * alpha;
		   res23 = res23 * alpha;
		   res24 = res24 * alpha;
		   res25 = res25 * alpha;
		   res26 = res26 * alpha;
		   res27 = res27 * alpha;
		   res28 = res28 * alpha;
		   res29 = res29 * alpha;
		   res30 = res30 * alpha;
		   res31 = res31 * alpha;

		   C0[0] += res0;
		   C0[1] += res1;
		   C0[2] += res2;
		   C0[3] += res3;
		   C0[4] += res4;
		   C0[5] += res5;
		   C0[6] += res6;
		   C0[7] += res7;
		   C0[8] += res8;
		   C0[9] += res9;
		   C0[10] += res10;
		   C0[11] += res11;
		   C0[12] += res12;
		   C0[13] += res13;
		   C0[14] += res14;
		   C0[15] += res15;

   		   C1[0] += res16;
		   C1[1] += res17;
		   C1[2] += res18;
		   C1[3] += res19;
		   C1[4] += res20;
		   C1[5] += res21;
		   C1[6] += res22;
		   C1[7] += res23;
		   C1[8] += res24;
		   C1[9] += res25;
		   C1[10] += res26;
		   C1[11] += res27;
		   C1[12] += res28;
		   C1[13] += res29;
		   C1[14] += res30;
		   C1[15] += res31;

		   C0 += 16;
		   C1 += 16;
	   }

	   if(bm&8){
		   ptrbb = bb;
   		   res0 = 0;
		   res1 = 0;
		   res2 = 0;
		   res3 = 0;
		   res4 = 0;
		   res5 = 0;
		   res6 = 0;
		   res7 = 0;
		   res8 = 0;
		   res9 = 0;
		   res10 = 0;
		   res11 = 0;
		   res12 = 0;
		   res13 = 0;
		   res14 = 0;
		   res15 = 0;
		   
		   for(k=0; k<bk; k+=1){
			   loadb0 = ptrbb[0];
			   loadb1 = ptrbb[1];

			   load0 = ptrba[0];
			   load1 = ptrba[1];
			   load2 = ptrba[2];
			   load3 = ptrba[3];
			   load4 = ptrba[4];
			   load5 = ptrba[5];
			   load6 = ptrba[6];
			   load7 = ptrba[7];
				   
			   res0 = res0 + load0 * loadb0;
			   res1 = res1 + load1 * loadb0;
			   res2 = res2 + load2 * loadb0;
			   res3 = res3 + load3 * loadb0;

			   res4 = res4 + load4 * loadb0;
			   res5 = res5 + load5 * loadb0;
			   res6 = res6 + load6 * loadb0;
			   res7 = res7 + load7 * loadb0;

   			   res8 = res8 + load0 * loadb1;
			   res9 = res9 + load1 * loadb1;
			   res10 = res10 + load2 * loadb1;
			   res11 = res11 + load3 * loadb1;

			   res12 = res12 + load4 * loadb1;
			   res13 = res13 + load5 * loadb1;
			   res14 = res14 + load6 * loadb1;
			   res15 = res15 + load7 * loadb1;

			   ptrba += 8;
			   ptrbb += 2;
		   }
		   
      		   res0 = res0 * alpha;
		   res1 = res1 * alpha;
		   res2 = res2 * alpha;
		   res3 = res3 * alpha;
		   res4 = res4 * alpha;
		   res5 = res5 * alpha;
		   res6 = res6 * alpha;
		   res7 = res7 * alpha;

       		   res8 = res8 * alpha;
		   res9 = res9 * alpha;
		   res10 = res10 * alpha;
		   res11 = res11 * alpha;
		   res12 = res12 * alpha;
		   res13 = res13 * alpha;
		   res14 = res14 * alpha;
		   res15 = res15 * alpha;

		   C0[0] += res0;
		   C0[1] += res1;
		   C0[2] += res2;
		   C0[3] += res3;
		   C0[4] += res4;
		   C0[5] += res5;
		   C0[6] += res6;
		   C0[7] += res7;

   		   C1[0] += res8;
		   C1[1] += res9;
		   C1[2] += res10;
		   C1[3] += res11;
		   C1[4] += res12;
		   C1[5] += res13;
		   C1[6] += res14;
		   C1[7] += res15;

		   C0 += 8;
		   C1 += 8;
	   }
	   if(bm&4){
		   ptrbb = bb;
   		   res0 = 0;
		   res1 = 0;
		   res2 = 0;
		   res3 = 0;
		   
		   res8 = 0;
		   res9 = 0;
		   res10 = 0;
		   res11 = 0;
		   
		   for(k=0; k<bk; k+=1){
			   loadb0 = ptrbb[0];
			   loadb1 = ptrbb[1];

			   load0 = ptrba[0];
			   load1 = ptrba[1];
			   load2 = ptrba[2];
			   load3 = ptrba[3];
				   
			   res0 = res0 + load0 * loadb0;
			   res1 = res1 + load1 * loadb0;
			   res2 = res2 + load2 * loadb0;
			   res3 = res3 + load3 * loadb0;

   			   res8 = res8 + load0 * loadb1;
			   res9 = res9 + load1 * loadb1;
			   res10 = res10 + load2 * loadb1;
			   res11 = res11 + load3 * loadb1;

			   ptrba += 4;
			   ptrbb += 2;
		   }
		   
      		   res0 = res0 * alpha;
		   res1 = res1 * alpha;
		   res2 = res2 * alpha;
		   res3 = res3 * alpha;

       		   res8 = res8 * alpha;
		   res9 = res9 * alpha;
		   res10 = res10 * alpha;
		   res11 = res11 * alpha;

		   C0[0] += res0;
		   C0[1] += res1;
		   C0[2] += res2;
		   C0[3] += res3;

   		   C1[0] += res8;
		   C1[1] += res9;
		   C1[2] += res10;
		   C1[3] += res11;

		   C0 += 4;
		   C1 += 4;
	   }
   	   if(bm&2){
		   ptrbb = bb;
      		   res0 = 0;
		   res1 = 0;
		   
		   res8 = 0;
		   res9 = 0;
		   
		   for(k=0; k<bk; k+=1){
			   loadb0 = ptrbb[0];
			   loadb1 = ptrbb[1];

			   load0 = ptrba[0];
			   load1 = ptrba[1];
				   
			   res0 = res0 + load0 * loadb0;
			   res1 = res1 + load1 * loadb0;

   			   res8 = res8 + load0 * loadb1;
			   res9 = res9 + load1 * loadb1;

			   ptrba += 2;
			   ptrbb += 2;
		   }
		   
      		   res0 = res0 * alpha;
		   res1 = res1 * alpha;

       		   res8 = res8 * alpha;
		   res9 = res9 * alpha;

		   C0[0] += res0;
		   C0[1] += res1;

   		   C1[0] += res8;
		   C1[1] += res9;
		   
		   C0 += 2;
		   C1 += 2;
	   }
	   if(bm&1){
		   ptrbb = bb;
       		   res0 = 0;
		   res8 = 0;
		   for(k=0; k<bk; k+=1){
			   loadb0 = ptrbb[0];
			   loadb1 = ptrbb[1];
			   load0 = ptrba[0];
				   
			   res0 = res0 + load0 * loadb0;
   			   res8 = res8 + load0 * loadb1;
			   ptrba += 1;
			   ptrbb += 2;
		   }
		   
      		   res0 = res0 * alpha;
       		   res8 = res8 * alpha;

		   C0[0] += res0;
   		   C1[0] += res8;
		   
		   C0 += 1;
		   C1 += 1;
	   }
	   k = bk<<1;
	   bb = bb+k;
	   i = ldc<<1;
	   C = C+i;
   }

   if (bn&1){
	   C0 = C;
	   ptrba = ba;
	   for(i=0; i<bm/16; i+=1){
		   ptrbb = bb;
		   res0 = 0;
		   res1 = 0;
		   res2 = 0;
		   res3 = 0;
		   res4 = 0;
		   res5 = 0;
		   res6 = 0;
		   res7 = 0;
		   res8 = 0;
		   res9 = 0;
		   res10 = 0;
		   res11 = 0;
		   res12 = 0;
		   res13 = 0;
		   res14 = 0;
		   res15 = 0;

		   for(k=0; k<bk; k+=1){
			   loadb0 = ptrbb[0];
			   res0 = res0 + ptrba[0] * loadb0;
			   res1 = res1 + ptrba[1] * loadb0;
			   res2 = res2 + ptrba[2] * loadb0;
			   res3 = res3 + ptrba[3] * loadb0;

			   res4 = res4 + ptrba[4] * loadb0;
			   res5 = res5 + ptrba[5] * loadb0;
			   res6 = res6 + ptrba[6] * loadb0;
			   res7 = res7 + ptrba[7] * loadb0;
			   res8 = res8 + ptrba[8] * loadb0;
			   res9 = res9 + ptrba[9] * loadb0;
			   res10 = res10 + ptrba[10] * loadb0;
			   res11 = res11 + ptrba[11] * loadb0;
			   res12 = res12 + ptrba[12] * loadb0;
			   res13 = res13 + ptrba[13] * loadb0;
			   res14 = res14 + ptrba[14] * loadb0;
			   res15 = res15 + ptrba[15] * loadb0;
			   
			   ptrba += 16;
			   ptrbb += 1;
		   }
   		   res0 = res0 * alpha;
		   res1 = res1 * alpha;
		   res2 = res2 * alpha;
		   res3 = res3 * alpha;
		   res4 = res4 * alpha;
		   res5 = res5 * alpha;
		   res6 = res6 * alpha;
		   res7 = res7 * alpha;
		   res8 = res8 * alpha;
		   res9 = res9 * alpha;
		   res10 = res10 * alpha;
		   res11 = res11 * alpha;
		   res12 = res12 * alpha;
		   res13 = res13 * alpha;
		   res14 = res14 * alpha;
		   res15 = res15 * alpha;

		   C0[0] += res0;
		   C0[1] += res1;
		   C0[2] += res2;
		   C0[3] += res3;
		   C0[4] += res4;
		   C0[5] += res5;
		   C0[6] += res6;
		   C0[7] += res7;
		   C0[8] += res8;
		   C0[9] += res9;
		   C0[10] += res10;
		   C0[11] += res11;
		   C0[12] += res12;
		   C0[13] += res13;
		   C0[14] += res14;
		   C0[15] += res15;
		   
		   C0 += 16;
	   }
	   if(bm&8){
		   ptrbb = bb;
		   res0 = 0;
		   res1 = 0;
		   res2 = 0;
		   res3 = 0;
		   res4 = 0;
		   res5 = 0;
		   res6 = 0;
		   res7 = 0;

		   for(k=0; k<bk; k+=1){
			   loadb0 = ptrbb[0];
			   res0 = res0 + ptrba[0] * loadb0;
			   res1 = res1 + ptrba[1] * loadb0;
			   res2 = res2 + ptrba[2] * loadb0;
			   res3 = res3 + ptrba[3] * loadb0;

			   res4 = res4 + ptrba[4] * loadb0;
			   res5 = res5 + ptrba[5] * loadb0;
			   res6 = res6 + ptrba[6] * loadb0;
			   res7 = res7 + ptrba[7] * loadb0;
			   
			   ptrba += 8;
			   ptrbb += 1;
		   }
   		   res0 = res0 * alpha;
		   res1 = res1 * alpha;
		   res2 = res2 * alpha;
		   res3 = res3 * alpha;
		   res4 = res4 * alpha;
		   res5 = res5 * alpha;
		   res6 = res6 * alpha;
		   res7 = res7 * alpha;

		   C0[0] += res0;
		   C0[1] += res1;
		   C0[2] += res2;
		   C0[3] += res3;
		   C0[4] += res4;
		   C0[5] += res5;
		   C0[6] += res6;
		   C0[7] += res7;
		   
		   C0 += 8;
	   }
	   if(bm&4){
		   ptrbb = bb;
   		   res0 = 0;
		   res1 = 0;
		   res2 = 0;
		   res3 = 0;
		   for(k=0; k<bk; k+=1){
			   loadb0 = ptrbb[0];
			   res0 = res0 + ptrba[0] * loadb0;
			   res1 = res1 + ptrba[1] * loadb0;
			   res2 = res2 + ptrba[2] * loadb0;
			   res3 = res3 + ptrba[3] * loadb0;

			   ptrba += 4;
			   ptrbb += 1;
		   }
      		   res0 = res0 * alpha;
		   res1 = res1 * alpha;
		   res2 = res2 * alpha;
		   res3 = res3 * alpha;

		   C0[0] += res0;
		   C0[1] += res1;
		   C0[2] += res2;
		   C0[3] += res3;
		   
		   C0 += 4;
	   }
   	   if(bm&2){
		   ptrbb = bb;
   		   res0 = 0;
		   res1 = 0;
		   for(k=0; k<bk; k+=1){
			   loadb0 = ptrbb[0];
			   res0 = res0 + ptrba[0] * loadb0;
			   res1 = res1 + ptrba[1] * loadb0;

			   ptrba += 2;
			   ptrbb += 1;
		   }
      		   res0 = res0 * alpha;
		   res1 = res1 * alpha;

		   C0[0] += res0;
		   C0[1] += res1;
		   
		   C0 += 2;
	   }
	   if(bm&1){
   		   ptrbb = bb;
   		   res0 = 0;
		   for(k=0; k<bk; k+=1){
			   loadb0 = ptrbb[0];
			   res0 = res0 + ptrba[0] * loadb0;
			   ptrba += 1;
			   ptrbb += 1;
		   }
      		   res0 = res0 * alpha;
		   C0[0] += res0;
		   C0 += 1;
	   }

	   k = bk;
	   bb = bb+k;
	   C = C+ldc;
   }
   return 0;
}
