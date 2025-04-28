/*********************************************************************/
/* Copyright 2009, 2010 The University of Texas at Austin.           */
/* All rights reserved.                                              */
/*                                                                   */
/* Redistribution and use in source and binary forms, with or        */
/* without modification, are permitted provided that the following   */
/* conditions are met:                                               */
/*                                                                   */
/*   1. Redistributions of source code must retain the above         */
/*      copyright notice, this list of conditions and the following  */
/*      disclaimer.                                                  */
/*                                                                   */
/*   2. Redistributions in binary form must reproduce the above      */
/*      copyright notice, this list of conditions and the following  */
/*      disclaimer in the documentation and/or other materials       */
/*      provided with the distribution.                              */
/*                                                                   */
/*    THIS  SOFTWARE IS PROVIDED  BY THE  UNIVERSITY OF  TEXAS AT    */
/*    AUSTIN  ``AS IS''  AND ANY  EXPRESS OR  IMPLIED WARRANTIES,    */
/*    INCLUDING, BUT  NOT LIMITED  TO, THE IMPLIED  WARRANTIES OF    */
/*    MERCHANTABILITY  AND FITNESS FOR  A PARTICULAR  PURPOSE ARE    */
/*    DISCLAIMED.  IN  NO EVENT SHALL THE UNIVERSITY  OF TEXAS AT    */
/*    AUSTIN OR CONTRIBUTORS BE  LIABLE FOR ANY DIRECT, INDIRECT,    */
/*    INCIDENTAL,  SPECIAL, EXEMPLARY,  OR  CONSEQUENTIAL DAMAGES    */
/*    (INCLUDING, BUT  NOT LIMITED TO,  PROCUREMENT OF SUBSTITUTE    */
/*    GOODS  OR  SERVICES; LOSS  OF  USE,  DATA,  OR PROFITS;  OR    */
/*    BUSINESS INTERRUPTION) HOWEVER CAUSED  AND ON ANY THEORY OF    */
/*    LIABILITY, WHETHER  IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*    (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY WAY OUT    */
/*    OF  THE  USE OF  THIS  SOFTWARE,  EVEN  IF ADVISED  OF  THE    */
/*    POSSIBILITY OF SUCH DAMAGE.                                    */
/*                                                                   */
/* The views and conclusions contained in the software and           */
/* documentation are those of the authors and should not be          */
/* interpreted as representing official policies, either expressed   */
/* or implied, of The University of Texas at Austin.                 */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <riscv_vector.h>

int gemm_beta(long m, long n, long dummy1, float beta,
	  float *dummy2, long dummy3, float *dummy4, long dummy5,
	  float *c, long ldc){


 // long i, j;
  long chunk, remain;
  float *c_offset1, *c_offset;
  c_offset = c;
  chunk = m >> 5;
  remain = m & 31;
  //ldc = ldc << 2;

 // printf("c:0x%llx.\n", c_offset);
 if(beta == 0) {
    asm volatile(
    "vsetvli        t0, zero, e32, m8 \n\t"
    "vfmv.v.f       v8, %[beta]       \n\t"
    "blez           %[n], END         \n\t"

    "MAIN:"
    "mv             t1, %[c_offset]   \n\t"
    "blez           %[chunk], TAIL    \n\t"
    "mv             t2, %[chunk]      \n\t"
    "vsetvli        t0, zero, e32, m8 \n\t"

    "MAIN_LOOP:"
    "vse32.v          v8, (t1)          \n\t"
    "addi           t1, t1, 128       \n\t"
    "addi           t2, t2, -1        \n\t"
    "bgtz           t2, MAIN_LOOP     \n\t"


    "TAIL:"
    "blez           %[remain], LOOP_END \n\t"
    "vsetvli        t0, %[remain], e32, m8 \n\t"
    "vse32.v          v8, (t1)\n\t"
    "LOOP_END:"
    "slli t0, %[ldc], 2        \n\t"
    "add %[c_offset], %[c_offset], t0     \n\t"
    "addi           %[n], %[n], -1\n\t"
    "bgtz           %[n], MAIN\n\t"
    "END:           \n\t"
    :[c_offset]"+r"(c_offset)
    :[chunk]"r"(chunk),[beta]"f"(beta), [n]"r"(n), [ldc]"r"(ldc), [remain]"r"(remain)
    :"memory", "t0", "t1", "t2", "v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15");
} else {
    asm volatile(
    "vsetvli        t0, zero, e32, m8 \n\t"
    "vfmv.v.f       v0, %[beta]       \n\t"
    "blez           %[n], END1        \n\t"

    "MAIN1:                           \n\t"
    "mv             t1, %[c_offset]   \n\t"
    "blez           %[chunk], TAIL1   \n\t"
    "mv             t2, %[chunk]      \n\t"
    "vsetvli        t0, zero, e32, m8 \n\t"

    "MAIN_LOOP1:"
    "vle32.v          v8, (t1)          \n\t"
    "vfmul.vv       v8, v8, v0        \n\t"
    "vse32.v          v8, (t1)          \n\t"
    "addi           t1, t1, 128       \n\t"
    "addi           t2, t2, -1        \n\t"
    "bgtz           t2, MAIN_LOOP1    \n\t"


    "TAIL1:"
    "blez           %[remain], LOOP_END1    \n\t"
    "vsetvli        t0, %[remain], e32, m8  \n\t"
    "vle32.v          v8, (t1)                \n\t"
    "vfmul.vv       v8, v8, v0              \n\t"
    "vse32.v          v8, (t1)                \n\t"

    "LOOP_END1:"
    "slli t0, %[ldc], 2        \n\t"
    "add %[c_offset], %[c_offset], t0     \n\t"
    "addi           %[n], %[n], -1\n\t"
    "bgtz           %[n], MAIN1\n\t"
    "END1:          \n\t"
    :[c_offset]"+r"(c_offset)
    :[chunk]"r"(chunk),[beta]"f"(beta), [n]"r"(n), [ldc]"r"(ldc), [remain]"r"(remain)
    :"memory", "t0", "t1", "t2", "v0", "v1", "v2", "v3", "v4", "v5", "v6",
     "v7", "v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15");
}

  return 0;
};
