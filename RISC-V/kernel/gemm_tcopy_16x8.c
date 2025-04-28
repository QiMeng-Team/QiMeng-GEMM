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

int gemm_tcopy(long m, long n, float *a, long lda, float *b){

  long i, j;

  float *aoffset;
  float *aoffset1, *aoffset2, *aoffset3, *aoffset4;
  float *aoffset5, *aoffset6, *aoffset7, *aoffset8;

  float *boffset,  *boffset1, *boffset2, *boffset3, *boffset4, *boffset5;

  float ctemp01, ctemp02, ctemp03, ctemp04;
  float ctemp05, ctemp06, ctemp07, ctemp08;
  float ctemp09, ctemp10, ctemp11, ctemp12;
  float ctemp13, ctemp14, ctemp15, ctemp16;
  float ctemp17, ctemp18, ctemp19, ctemp20;
  float ctemp21, ctemp22, ctemp23, ctemp24;
  float ctemp25, ctemp26, ctemp27, ctemp28;
  float ctemp29, ctemp30, ctemp31, ctemp32;
  float ctemp33, ctemp34, ctemp35, ctemp36;
  float ctemp37, ctemp38, ctemp39, ctemp40;
  float ctemp41, ctemp42, ctemp43, ctemp44;
  float ctemp45, ctemp46, ctemp47, ctemp48;
  float ctemp49, ctemp50, ctemp51, ctemp52;
  float ctemp53, ctemp54, ctemp55, ctemp56;
  float ctemp57, ctemp58, ctemp59, ctemp60;
  float ctemp61, ctemp62, ctemp63, ctemp64;
  float ctemp65, ctemp66, ctemp67, ctemp68;
  float ctemp69, ctemp70, ctemp71, ctemp72;
  float ctemp73, ctemp74, ctemp75, ctemp76;
  float ctemp77, ctemp78, ctemp79, ctemp80;
  float ctemp81, ctemp82, ctemp83, ctemp84;
  float ctemp85, ctemp86, ctemp87, ctemp88;
  float ctemp89, ctemp90, ctemp91, ctemp92;
  float ctemp93, ctemp94, ctemp95, ctemp96;
  float ctemp97, ctemp98, ctemp99, ctemp100;
  float ctemp101, ctemp102, ctemp103, ctemp104;
  float ctemp105, ctemp106, ctemp107, ctemp108;
  float ctemp109, ctemp110, ctemp111, ctemp112;
  float ctemp113, ctemp114, ctemp115, ctemp116;
  float ctemp117, ctemp118, ctemp119, ctemp120;
  float ctemp121, ctemp122, ctemp123, ctemp124;
  float ctemp125, ctemp126, ctemp127, ctemp128;


  aoffset   = a;
  boffset   = b;

#if 0
  fprintf(stderr, "M = %d N = %d\n", m, n);
#endif

  boffset2  = b + m  * (n & ~7);
  boffset3  = b + m  * (n & ~3);
  boffset4  = b + m  * (n & ~1);
  boffset5  = b + m  * (n & ~15);

  j = (m >> 3);
  if (j > 0){
    do{
      aoffset1  = aoffset;
      aoffset2  = aoffset1 + lda;
      aoffset3  = aoffset2 + lda;
      aoffset4  = aoffset3 + lda;
      aoffset5  = aoffset4 + lda;
      aoffset6  = aoffset5 + lda;
      aoffset7  = aoffset6 + lda;
      aoffset8  = aoffset7 + lda;
      aoffset += 8 * lda;

      boffset1  = boffset;
      boffset  += 128;

      i = (n >> 4);
      if (i > 0){
	    do{
	  ctemp01 = *(aoffset1 + 0);
	  ctemp02 = *(aoffset1 + 1);
	  ctemp03 = *(aoffset1 + 2);
	  ctemp04 = *(aoffset1 + 3);
	  ctemp05 = *(aoffset1 + 4);
	  ctemp06 = *(aoffset1 + 5);
	  ctemp07 = *(aoffset1 + 6);
	  ctemp08 = *(aoffset1 + 7);
	  ctemp09 = *(aoffset1 + 8);
	  ctemp10 = *(aoffset1 + 9);
	  ctemp11 = *(aoffset1 + 10);
	  ctemp12 = *(aoffset1 + 11);
	  ctemp13 = *(aoffset1 + 12);
	  ctemp14 = *(aoffset1 + 13);
	  ctemp15 = *(aoffset1 + 14);
	  ctemp16 = *(aoffset1 + 15);
	  aoffset1 += 16;

	  ctemp17 = *(aoffset2 + 0);
	  ctemp18 = *(aoffset2 + 1);
	  ctemp19 = *(aoffset2 + 2);
	  ctemp20 = *(aoffset2 + 3);
	  ctemp21 = *(aoffset2 + 4);
	  ctemp22 = *(aoffset2 + 5);
	  ctemp23 = *(aoffset2 + 6);
	  ctemp24 = *(aoffset2 + 7);
	  ctemp25 = *(aoffset2 + 8);
	  ctemp26 = *(aoffset2 + 9);
	  ctemp27 = *(aoffset2 + 10);
	  ctemp28 = *(aoffset2 + 11);
	  ctemp29 = *(aoffset2 + 12);
	  ctemp30 = *(aoffset2 + 13);
	  ctemp31 = *(aoffset2 + 14);
	  ctemp32 = *(aoffset2 + 15);
	  aoffset2 += 16;

	  ctemp33 = *(aoffset3 + 0);
	  ctemp34 = *(aoffset3 + 1);
	  ctemp35 = *(aoffset3 + 2);
	  ctemp36 = *(aoffset3 + 3);
	  ctemp37 = *(aoffset3 + 4);
	  ctemp38 = *(aoffset3 + 5);
	  ctemp39 = *(aoffset3 + 6);
	  ctemp40 = *(aoffset3 + 7);
	  ctemp41 = *(aoffset3 + 8);
	  ctemp42 = *(aoffset3 + 9);
	  ctemp43 = *(aoffset3 + 10);
	  ctemp44 = *(aoffset3 + 11);
	  ctemp45 = *(aoffset3 + 12);
	  ctemp46 = *(aoffset3 + 13);
	  ctemp47 = *(aoffset3 + 14);
	  ctemp48 = *(aoffset3 + 15);
	  aoffset3 += 16;

	  ctemp49 = *(aoffset4 + 0);
	  ctemp50 = *(aoffset4 + 1);
	  ctemp51 = *(aoffset4 + 2);
	  ctemp52 = *(aoffset4 + 3);
	  ctemp53 = *(aoffset4 + 4);
	  ctemp54 = *(aoffset4 + 5);
	  ctemp55 = *(aoffset4 + 6);
	  ctemp56 = *(aoffset4 + 7);
	  ctemp57 = *(aoffset4 + 8);
	  ctemp58 = *(aoffset4 + 9);
	  ctemp59 = *(aoffset4 + 10);
	  ctemp60 = *(aoffset4 + 11);
	  ctemp61 = *(aoffset4 + 12);
	  ctemp62 = *(aoffset4 + 13);
	  ctemp63 = *(aoffset4 + 14);
	  ctemp64 = *(aoffset4 + 15);
	  aoffset4 += 16;

	  ctemp65 = *(aoffset5 + 0);
	  ctemp66 = *(aoffset5 + 1);
	  ctemp67 = *(aoffset5 + 2);
	  ctemp68 = *(aoffset5 + 3);
	  ctemp69 = *(aoffset5 + 4);
	  ctemp70 = *(aoffset5 + 5);
	  ctemp71 = *(aoffset5 + 6);
	  ctemp72 = *(aoffset5 + 7);
	  ctemp73 = *(aoffset5 + 8);
	  ctemp74 = *(aoffset5 + 9);
	  ctemp75 = *(aoffset5 + 10);
	  ctemp76 = *(aoffset5 + 11);
	  ctemp77 = *(aoffset5 + 12);
	  ctemp78 = *(aoffset5 + 13);
	  ctemp79 = *(aoffset5 + 14);
	  ctemp80 = *(aoffset5 + 15);
	  aoffset5 += 16;

	  ctemp81 = *(aoffset6 + 0);
	  ctemp82 = *(aoffset6 + 1);
	  ctemp83 = *(aoffset6 + 2);
	  ctemp84 = *(aoffset6 + 3);
	  ctemp85 = *(aoffset6 + 4);
	  ctemp86 = *(aoffset6 + 5);
	  ctemp87 = *(aoffset6 + 6);
	  ctemp88 = *(aoffset6 + 7);
	  ctemp89 = *(aoffset6 + 8);
	  ctemp90 = *(aoffset6 + 9);
	  ctemp91 = *(aoffset6 + 10);
	  ctemp92 = *(aoffset6 + 11);
	  ctemp93 = *(aoffset6 + 12);
	  ctemp94 = *(aoffset6 + 13);
	  ctemp95 = *(aoffset6 + 14);
	  ctemp96 = *(aoffset6 + 15);
	  aoffset6 += 16;

	  ctemp97  = *(aoffset7 + 0);
	  ctemp98  = *(aoffset7 + 1);
	  ctemp99  = *(aoffset7 + 2);
	  ctemp100 = *(aoffset7 + 3);
	  ctemp101 = *(aoffset7 + 4);
	  ctemp102 = *(aoffset7 + 5);
	  ctemp103 = *(aoffset7 + 6);
	  ctemp104 = *(aoffset7 + 7);
	  ctemp105 = *(aoffset7 + 8);
	  ctemp106 = *(aoffset7 + 9);
	  ctemp107 = *(aoffset7 + 10);
	  ctemp108 = *(aoffset7 + 11);
	  ctemp109 = *(aoffset7 + 12);
	  ctemp110 = *(aoffset7 + 13);
	  ctemp111 = *(aoffset7 + 14);
	  ctemp112 = *(aoffset7 + 15);
	  aoffset7 += 16;

	  ctemp113 = *(aoffset8 + 0);
	  ctemp114 = *(aoffset8 + 1);
	  ctemp115 = *(aoffset8 + 2);
	  ctemp116 = *(aoffset8 + 3);
	  ctemp117 = *(aoffset8 + 4);
	  ctemp118 = *(aoffset8 + 5);
	  ctemp119 = *(aoffset8 + 6);
	  ctemp120 = *(aoffset8 + 7);
	  ctemp121 = *(aoffset8 + 8);
	  ctemp122 = *(aoffset8 + 9);
	  ctemp123 = *(aoffset8 + 10);
	  ctemp124 = *(aoffset8 + 11);
	  ctemp125 = *(aoffset8 + 12);
	  ctemp126 = *(aoffset8 + 13);
	  ctemp127 = *(aoffset8 + 14);
	  ctemp128 = *(aoffset8 + 15);
	  aoffset8 += 16;

	  *(boffset1 +  0) = ctemp01;
	  *(boffset1 +  1) = ctemp02;
	  *(boffset1 +  2) = ctemp03;
	  *(boffset1 +  3) = ctemp04;
	  *(boffset1 +  4) = ctemp05;
	  *(boffset1 +  5) = ctemp06;
	  *(boffset1 +  6) = ctemp07;
	  *(boffset1 +  7) = ctemp08;
	  *(boffset1 +  8) = ctemp09;
	  *(boffset1 +  9) = ctemp10;
	  *(boffset1 + 10) = ctemp11;
	  *(boffset1 + 11) = ctemp12;
	  *(boffset1 + 12) = ctemp13;
	  *(boffset1 + 13) = ctemp14;
	  *(boffset1 + 14) = ctemp15;
	  *(boffset1 + 15) = ctemp16;

	  *(boffset1 + 16) = ctemp17;
	  *(boffset1 + 17) = ctemp18;
	  *(boffset1 + 18) = ctemp19;
	  *(boffset1 + 19) = ctemp20;
	  *(boffset1 + 20) = ctemp21;
	  *(boffset1 + 21) = ctemp22;
	  *(boffset1 + 22) = ctemp23;
	  *(boffset1 + 23) = ctemp24;
	  *(boffset1 + 24) = ctemp25;
	  *(boffset1 + 25) = ctemp26;
	  *(boffset1 + 26) = ctemp27;
	  *(boffset1 + 27) = ctemp28;
	  *(boffset1 + 28) = ctemp29;
	  *(boffset1 + 29) = ctemp30;
	  *(boffset1 + 30) = ctemp31;
	  *(boffset1 + 31) = ctemp32;

	  *(boffset1 + 32) = ctemp33;
	  *(boffset1 + 33) = ctemp34;
	  *(boffset1 + 34) = ctemp35;
	  *(boffset1 + 35) = ctemp36;
	  *(boffset1 + 36) = ctemp37;
	  *(boffset1 + 37) = ctemp38;
	  *(boffset1 + 38) = ctemp39;
	  *(boffset1 + 39) = ctemp40;
	  *(boffset1 + 40) = ctemp41;
	  *(boffset1 + 41) = ctemp42;
	  *(boffset1 + 42) = ctemp43;
	  *(boffset1 + 43) = ctemp44;
	  *(boffset1 + 44) = ctemp45;
	  *(boffset1 + 45) = ctemp46;
	  *(boffset1 + 46) = ctemp47;
	  *(boffset1 + 47) = ctemp48;

	  *(boffset1 + 48) = ctemp49;
	  *(boffset1 + 49) = ctemp50;
	  *(boffset1 + 50) = ctemp51;
	  *(boffset1 + 51) = ctemp52;
	  *(boffset1 + 52) = ctemp53;
	  *(boffset1 + 53) = ctemp54;
	  *(boffset1 + 54) = ctemp55;
	  *(boffset1 + 55) = ctemp56;
	  *(boffset1 + 56) = ctemp57;
	  *(boffset1 + 57) = ctemp58;
	  *(boffset1 + 58) = ctemp59;
	  *(boffset1 + 59) = ctemp60;
	  *(boffset1 + 60) = ctemp61;
	  *(boffset1 + 61) = ctemp62;
	  *(boffset1 + 62) = ctemp63;
	  *(boffset1 + 63) = ctemp64;

	  *(boffset1 + 64) = ctemp65;
	  *(boffset1 + 65) = ctemp66;
	  *(boffset1 + 66) = ctemp67;
	  *(boffset1 + 67) = ctemp68;
	  *(boffset1 + 68) = ctemp69;
	  *(boffset1 + 69) = ctemp70;
	  *(boffset1 + 70) = ctemp71;
	  *(boffset1 + 71) = ctemp72;
	  *(boffset1 + 72) = ctemp73;
	  *(boffset1 + 73) = ctemp74;
	  *(boffset1 + 74) = ctemp75;
	  *(boffset1 + 75) = ctemp76;
	  *(boffset1 + 76) = ctemp77;
	  *(boffset1 + 77) = ctemp78;
	  *(boffset1 + 78) = ctemp79;
	  *(boffset1 + 79) = ctemp80;

	  *(boffset1 + 80) = ctemp81;
	  *(boffset1 + 81) = ctemp82;
	  *(boffset1 + 82) = ctemp83;
	  *(boffset1 + 83) = ctemp84;
	  *(boffset1 + 84) = ctemp85;
	  *(boffset1 + 85) = ctemp86;
	  *(boffset1 + 86) = ctemp87;
	  *(boffset1 + 87) = ctemp88;
	  *(boffset1 + 88) = ctemp89;
	  *(boffset1 + 89) = ctemp90;
	  *(boffset1 + 90) = ctemp91;
	  *(boffset1 + 91) = ctemp92;
	  *(boffset1 + 92) = ctemp93;
	  *(boffset1 + 93) = ctemp94;
	  *(boffset1 + 94) = ctemp95;
	  *(boffset1 + 95) = ctemp96;

	  *(boffset1 + 96)  = ctemp97;
	  *(boffset1 + 97)  = ctemp98;
	  *(boffset1 + 98)  = ctemp99;
	  *(boffset1 + 99)  = ctemp100;
	  *(boffset1 + 100) = ctemp101;
	  *(boffset1 + 101) = ctemp102;
	  *(boffset1 + 102) = ctemp103;
	  *(boffset1 + 103) = ctemp104;
	  *(boffset1 + 104) = ctemp105;
	  *(boffset1 + 105) = ctemp106;
	  *(boffset1 + 106) = ctemp107;
	  *(boffset1 + 107) = ctemp108;
	  *(boffset1 + 108) = ctemp109;
	  *(boffset1 + 109) = ctemp110;
	  *(boffset1 + 110) = ctemp111;
	  *(boffset1 + 111) = ctemp112;

	  *(boffset1 + 112) = ctemp113;
	  *(boffset1 + 113) = ctemp114;
	  *(boffset1 + 114) = ctemp115;
	  *(boffset1 + 115) = ctemp116;
	  *(boffset1 + 116) = ctemp117;
	  *(boffset1 + 117) = ctemp118;
	  *(boffset1 + 118) = ctemp119;
	  *(boffset1 + 119) = ctemp120;
	  *(boffset1 + 120) = ctemp121;
	  *(boffset1 + 121) = ctemp122;
	  *(boffset1 + 122) = ctemp123;
	  *(boffset1 + 123) = ctemp124;
	  *(boffset1 + 124) = ctemp125;
	  *(boffset1 + 125) = ctemp126;
	  *(boffset1 + 126) = ctemp127;
	  *(boffset1 + 127) = ctemp128;

	  boffset1 += m * 16;
	  i --;
	}while(i > 0);
      }

      if(n & 8){
      ctemp01 = *(aoffset1 + 0);
	  ctemp02 = *(aoffset1 + 1);
	  ctemp03 = *(aoffset1 + 2);
	  ctemp04 = *(aoffset1 + 3);
	  ctemp05 = *(aoffset1 + 4);
	  ctemp06 = *(aoffset1 + 5);
	  ctemp07 = *(aoffset1 + 6);
	  ctemp08 = *(aoffset1 + 7);
	  aoffset1 += 8;

	  ctemp09 = *(aoffset2 + 0);
	  ctemp10 = *(aoffset2 + 1);
	  ctemp11 = *(aoffset2 + 2);
	  ctemp12 = *(aoffset2 + 3);
	  ctemp13 = *(aoffset2 + 4);
	  ctemp14 = *(aoffset2 + 5);
	  ctemp15 = *(aoffset2 + 6);
	  ctemp16 = *(aoffset2 + 7);
	  aoffset2 += 8;

	  ctemp17 = *(aoffset3 + 0);
	  ctemp18 = *(aoffset3 + 1);
	  ctemp19 = *(aoffset3 + 2);
	  ctemp20 = *(aoffset3 + 3);
	  ctemp21 = *(aoffset3 + 4);
	  ctemp22 = *(aoffset3 + 5);
	  ctemp23 = *(aoffset3 + 6);
	  ctemp24 = *(aoffset3 + 7);
	  aoffset3 += 8;

	  ctemp25 = *(aoffset4 + 0);
	  ctemp26 = *(aoffset4 + 1);
	  ctemp27 = *(aoffset4 + 2);
	  ctemp28 = *(aoffset4 + 3);
	  ctemp29 = *(aoffset4 + 4);
	  ctemp30 = *(aoffset4 + 5);
	  ctemp31 = *(aoffset4 + 6);
	  ctemp32 = *(aoffset4 + 7);
	  aoffset4 += 8;

	  ctemp33 = *(aoffset5 + 0);
	  ctemp34 = *(aoffset5 + 1);
	  ctemp35 = *(aoffset5 + 2);
	  ctemp36 = *(aoffset5 + 3);
	  ctemp37 = *(aoffset5 + 4);
	  ctemp38 = *(aoffset5 + 5);
	  ctemp39 = *(aoffset5 + 6);
	  ctemp40 = *(aoffset5 + 7);
	  aoffset5 += 8;

	  ctemp41 = *(aoffset6 + 0);
	  ctemp42 = *(aoffset6 + 1);
	  ctemp43 = *(aoffset6 + 2);
	  ctemp44 = *(aoffset6 + 3);
	  ctemp45 = *(aoffset6 + 4);
	  ctemp46 = *(aoffset6 + 5);
	  ctemp47 = *(aoffset6 + 6);
	  ctemp48 = *(aoffset6 + 7);
	  aoffset6 += 8;

	  ctemp49 = *(aoffset7 + 0);
	  ctemp50 = *(aoffset7 + 1);
	  ctemp51 = *(aoffset7 + 2);
	  ctemp52 = *(aoffset7 + 3);
	  ctemp53 = *(aoffset7 + 4);
	  ctemp54 = *(aoffset7 + 5);
	  ctemp55 = *(aoffset7 + 6);
	  ctemp56 = *(aoffset7 + 7);
	  aoffset7 += 8;

	  ctemp57 = *(aoffset8 + 0);
	  ctemp58 = *(aoffset8 + 1);
	  ctemp59 = *(aoffset8 + 2);
	  ctemp60 = *(aoffset8 + 3);
	  ctemp61 = *(aoffset8 + 4);
	  ctemp62 = *(aoffset8 + 5);
	  ctemp63 = *(aoffset8 + 6);
	  ctemp64 = *(aoffset8 + 7);
	  aoffset8 += 8;

	  *(boffset5 +  0) = ctemp01;
	  *(boffset5 +  1) = ctemp02;
	  *(boffset5 +  2) = ctemp03;
	  *(boffset5 +  3) = ctemp04;
	  *(boffset5 +  4) = ctemp05;
	  *(boffset5 +  5) = ctemp06;
	  *(boffset5 +  6) = ctemp07;
	  *(boffset5 +  7) = ctemp08;

	  *(boffset5 +  8) = ctemp09;
	  *(boffset5 +  9) = ctemp10;
	  *(boffset5 + 10) = ctemp11;
	  *(boffset5 + 11) = ctemp12;
	  *(boffset5 + 12) = ctemp13;
	  *(boffset5 + 13) = ctemp14;
	  *(boffset5 + 14) = ctemp15;
	  *(boffset5 + 15) = ctemp16;

	  *(boffset5 + 16) = ctemp17;
	  *(boffset5 + 17) = ctemp18;
	  *(boffset5 + 18) = ctemp19;
	  *(boffset5 + 19) = ctemp20;
	  *(boffset5 + 20) = ctemp21;
	  *(boffset5 + 21) = ctemp22;
	  *(boffset5 + 22) = ctemp23;
	  *(boffset5 + 23) = ctemp24;

	  *(boffset5 + 24) = ctemp25;
	  *(boffset5 + 25) = ctemp26;
	  *(boffset5 + 26) = ctemp27;
	  *(boffset5 + 27) = ctemp28;
	  *(boffset5 + 28) = ctemp29;
	  *(boffset5 + 29) = ctemp30;
	  *(boffset5 + 30) = ctemp31;
	  *(boffset5 + 31) = ctemp32;

	  *(boffset5 + 32) = ctemp33;
	  *(boffset5 + 33) = ctemp34;
	  *(boffset5 + 34) = ctemp35;
	  *(boffset5 + 35) = ctemp36;
	  *(boffset5 + 36) = ctemp37;
	  *(boffset5 + 37) = ctemp38;
	  *(boffset5 + 38) = ctemp39;
	  *(boffset5 + 39) = ctemp40;

	  *(boffset5 + 40) = ctemp41;
	  *(boffset5 + 41) = ctemp42;
	  *(boffset5 + 42) = ctemp43;
	  *(boffset5 + 43) = ctemp44;
	  *(boffset5 + 44) = ctemp45;
	  *(boffset5 + 45) = ctemp46;
	  *(boffset5 + 46) = ctemp47;
	  *(boffset5 + 47) = ctemp48;

	  *(boffset5 + 48) = ctemp49;
	  *(boffset5 + 49) = ctemp50;
	  *(boffset5 + 50) = ctemp51;
	  *(boffset5 + 51) = ctemp52;
	  *(boffset5 + 52) = ctemp53;
	  *(boffset5 + 53) = ctemp54;
	  *(boffset5 + 54) = ctemp55;
	  *(boffset5 + 55) = ctemp56;

	  *(boffset5 + 56) = ctemp57;
	  *(boffset5 + 57) = ctemp58;
	  *(boffset5 + 58) = ctemp59;
	  *(boffset5 + 59) = ctemp60;
	  *(boffset5 + 60) = ctemp61;
	  *(boffset5 + 61) = ctemp62;
	  *(boffset5 + 62) = ctemp63;
	  *(boffset5 + 63) = ctemp64;

	  boffset5 += 64;

      }
      if (n & 4){
	ctemp01 = *(aoffset1 + 0);
	ctemp02 = *(aoffset1 + 1);
	ctemp03 = *(aoffset1 + 2);
	ctemp04 = *(aoffset1 + 3);
	aoffset1 += 4;

	ctemp05 = *(aoffset2 + 0);
	ctemp06 = *(aoffset2 + 1);
	ctemp07 = *(aoffset2 + 2);
	ctemp08 = *(aoffset2 + 3);
	aoffset2 += 4;

	ctemp09 = *(aoffset3 + 0);
	ctemp10 = *(aoffset3 + 1);
	ctemp11 = *(aoffset3 + 2);
	ctemp12 = *(aoffset3 + 3);
	aoffset3 += 4;

	ctemp13 = *(aoffset4 + 0);
	ctemp14 = *(aoffset4 + 1);
	ctemp15 = *(aoffset4 + 2);
	ctemp16 = *(aoffset4 + 3);
	aoffset4 += 4;

	ctemp17 = *(aoffset5 + 0);
	ctemp18 = *(aoffset5 + 1);
	ctemp19 = *(aoffset5 + 2);
	ctemp20 = *(aoffset5 + 3);
	aoffset5 += 4;

	ctemp21 = *(aoffset6 + 0);
	ctemp22 = *(aoffset6 + 1);
	ctemp23 = *(aoffset6 + 2);
	ctemp24 = *(aoffset6 + 3);
	aoffset6 += 4;

	ctemp25 = *(aoffset7 + 0);
	ctemp26 = *(aoffset7 + 1);
	ctemp27 = *(aoffset7 + 2);
	ctemp28 = *(aoffset7 + 3);
	aoffset7 += 4;

	ctemp29 = *(aoffset8 + 0);
	ctemp30 = *(aoffset8 + 1);
	ctemp31 = *(aoffset8 + 2);
	ctemp32 = *(aoffset8 + 3);
	aoffset8 += 4;

	*(boffset2 +  0) = ctemp01;
	*(boffset2 +  1) = ctemp02;
	*(boffset2 +  2) = ctemp03;
	*(boffset2 +  3) = ctemp04;
	*(boffset2 +  4) = ctemp05;
	*(boffset2 +  5) = ctemp06;
	*(boffset2 +  6) = ctemp07;
	*(boffset2 +  7) = ctemp08;
	*(boffset2 +  8) = ctemp09;
	*(boffset2 +  9) = ctemp10;
	*(boffset2 + 10) = ctemp11;
	*(boffset2 + 11) = ctemp12;
	*(boffset2 + 12) = ctemp13;
	*(boffset2 + 13) = ctemp14;
	*(boffset2 + 14) = ctemp15;
	*(boffset2 + 15) = ctemp16;

	*(boffset2 + 16) = ctemp17;
	*(boffset2 + 17) = ctemp18;
	*(boffset2 + 18) = ctemp19;
	*(boffset2 + 19) = ctemp20;
	*(boffset2 + 20) = ctemp21;
	*(boffset2 + 21) = ctemp22;
	*(boffset2 + 22) = ctemp23;
	*(boffset2 + 23) = ctemp24;
	*(boffset2 + 24) = ctemp25;
	*(boffset2 + 25) = ctemp26;
	*(boffset2 + 26) = ctemp27;
	*(boffset2 + 27) = ctemp28;
	*(boffset2 + 28) = ctemp29;
	*(boffset2 + 29) = ctemp30;
	*(boffset2 + 30) = ctemp31;
	*(boffset2 + 31) = ctemp32;

	boffset2 += 32;
      }

      if (n & 2){
	ctemp01 = *(aoffset1 + 0);
	ctemp02 = *(aoffset1 + 1);
	aoffset1 += 2;

	ctemp03 = *(aoffset2 + 0);
	ctemp04 = *(aoffset2 + 1);
	aoffset2 += 2;

	ctemp05 = *(aoffset3 + 0);
	ctemp06 = *(aoffset3 + 1);
	aoffset3 += 2;

	ctemp07 = *(aoffset4 + 0);
	ctemp08 = *(aoffset4 + 1);
	aoffset4 += 2;

	ctemp09 = *(aoffset5 + 0);
	ctemp10 = *(aoffset5 + 1);
	aoffset5 += 2;

	ctemp11 = *(aoffset6 + 0);
	ctemp12 = *(aoffset6 + 1);
	aoffset6 += 2;

	ctemp13 = *(aoffset7 + 0);
	ctemp14 = *(aoffset7 + 1);
	aoffset7 += 2;

	ctemp15 = *(aoffset8 + 0);
	ctemp16 = *(aoffset8 + 1);
	aoffset8 += 2;

	*(boffset3 +  0) = ctemp01;
	*(boffset3 +  1) = ctemp02;
	*(boffset3 +  2) = ctemp03;
	*(boffset3 +  3) = ctemp04;
	*(boffset3 +  4) = ctemp05;
	*(boffset3 +  5) = ctemp06;
	*(boffset3 +  6) = ctemp07;
	*(boffset3 +  7) = ctemp08;
	*(boffset3 +  8) = ctemp09;
	*(boffset3 +  9) = ctemp10;
	*(boffset3 + 10) = ctemp11;
	*(boffset3 + 11) = ctemp12;
	*(boffset3 + 12) = ctemp13;
	*(boffset3 + 13) = ctemp14;
	*(boffset3 + 14) = ctemp15;
	*(boffset3 + 15) = ctemp16;
	boffset3 += 16;
      }

      if (n & 1){
	ctemp01 = *(aoffset1 + 0);
	aoffset1 ++;
	ctemp02 = *(aoffset2 + 0);
	aoffset2 ++;
	ctemp03 = *(aoffset3 + 0);
	aoffset3 ++;
	ctemp04 = *(aoffset4 + 0);
	aoffset4 ++;
	ctemp05 = *(aoffset5 + 0);
	aoffset5 ++;
	ctemp06 = *(aoffset6 + 0);
	aoffset6 ++;
	ctemp07 = *(aoffset7 + 0);
	aoffset7 ++;
	ctemp08 = *(aoffset8 + 0);
	aoffset8 ++;

	*(boffset4 +  0) = ctemp01;
	*(boffset4 +  1) = ctemp02;
	*(boffset4 +  2) = ctemp03;
	*(boffset4 +  3) = ctemp04;
	*(boffset4 +  4) = ctemp05;
	*(boffset4 +  5) = ctemp06;
	*(boffset4 +  6) = ctemp07;
	*(boffset4 +  7) = ctemp08;
	boffset4 += 8;
      }

      j--;
    }while(j > 0);
  }

  if (m & 4){

    aoffset1  = aoffset;
    aoffset2  = aoffset1 + lda;
    aoffset3  = aoffset2 + lda;
    aoffset4  = aoffset3 + lda;
    aoffset += 4 * lda;

    boffset1  = boffset;
    boffset  += 64;

    i = (n >> 4);
    if (i > 0){
	  do{
	ctemp01 = *(aoffset1 + 0);
	ctemp02 = *(aoffset1 + 1);
	ctemp03 = *(aoffset1 + 2);
	ctemp04 = *(aoffset1 + 3);
	ctemp05 = *(aoffset1 + 4);
	ctemp06 = *(aoffset1 + 5);
	ctemp07 = *(aoffset1 + 6);
	ctemp08 = *(aoffset1 + 7);
	ctemp09 = *(aoffset1 + 8);
	ctemp10 = *(aoffset1 + 9);
	ctemp11 = *(aoffset1 + 10);
	ctemp12 = *(aoffset1 + 11);
	ctemp13 = *(aoffset1 + 12);
	ctemp14 = *(aoffset1 + 13);
	ctemp15 = *(aoffset1 + 14);
	ctemp16 = *(aoffset1 + 15);
	aoffset1 += 16;

	ctemp17 = *(aoffset2 + 0);
	ctemp18 = *(aoffset2 + 1);
	ctemp19 = *(aoffset2 + 2);
	ctemp20 = *(aoffset2 + 3);
	ctemp21 = *(aoffset2 + 4);
	ctemp22 = *(aoffset2 + 5);
	ctemp23 = *(aoffset2 + 6);
	ctemp24 = *(aoffset2 + 7);
	ctemp25 = *(aoffset2 + 8);
	ctemp26 = *(aoffset2 + 9);
	ctemp27 = *(aoffset2 + 10);
	ctemp28 = *(aoffset2 + 11);
	ctemp29 = *(aoffset2 + 12);
	ctemp30 = *(aoffset2 + 13);
	ctemp31 = *(aoffset2 + 14);
	ctemp32 = *(aoffset2 + 15);
	aoffset2 += 16;

	ctemp33 = *(aoffset3 + 0);
	ctemp34 = *(aoffset3 + 1);
	ctemp35 = *(aoffset3 + 2);
	ctemp36 = *(aoffset3 + 3);
	ctemp37 = *(aoffset3 + 4);
	ctemp38 = *(aoffset3 + 5);
	ctemp39 = *(aoffset3 + 6);
	ctemp40 = *(aoffset3 + 7);
	ctemp41 = *(aoffset3 + 8);
	ctemp42 = *(aoffset3 + 9);
	ctemp43 = *(aoffset3 + 10);
	ctemp44 = *(aoffset3 + 11);
	ctemp45 = *(aoffset3 + 12);
	ctemp46 = *(aoffset3 + 13);
	ctemp47 = *(aoffset3 + 14);
	ctemp48 = *(aoffset3 + 15);
	aoffset3 += 16;

	ctemp49 = *(aoffset4 + 0);
	ctemp50 = *(aoffset4 + 1);
	ctemp51 = *(aoffset4 + 2);
	ctemp52 = *(aoffset4 + 3);
	ctemp53 = *(aoffset4 + 4);
	ctemp54 = *(aoffset4 + 5);
	ctemp55 = *(aoffset4 + 6);
	ctemp56 = *(aoffset4 + 7);
	ctemp57 = *(aoffset4 + 8);
	ctemp58 = *(aoffset4 + 9);
	ctemp59 = *(aoffset4 + 10);
	ctemp60 = *(aoffset4 + 11);
	ctemp61 = *(aoffset4 + 12);
	ctemp62 = *(aoffset4 + 13);
	ctemp63 = *(aoffset4 + 14);
	ctemp64 = *(aoffset4 + 15);
	aoffset4 += 16;

	*(boffset1 +  0) = ctemp01;
	*(boffset1 +  1) = ctemp02;
	*(boffset1 +  2) = ctemp03;
	*(boffset1 +  3) = ctemp04;
	*(boffset1 +  4) = ctemp05;
	*(boffset1 +  5) = ctemp06;
	*(boffset1 +  6) = ctemp07;
	*(boffset1 +  7) = ctemp08;
	*(boffset1 +  8) = ctemp09;
	*(boffset1 +  9) = ctemp10;
	*(boffset1 + 10) = ctemp11;
	*(boffset1 + 11) = ctemp12;
	*(boffset1 + 12) = ctemp13;
	*(boffset1 + 13) = ctemp14;
	*(boffset1 + 14) = ctemp15;
	*(boffset1 + 15) = ctemp16;

	*(boffset1 + 16) = ctemp17;
	*(boffset1 + 17) = ctemp18;
	*(boffset1 + 18) = ctemp19;
	*(boffset1 + 19) = ctemp20;
	*(boffset1 + 20) = ctemp21;
	*(boffset1 + 21) = ctemp22;
	*(boffset1 + 22) = ctemp23;
	*(boffset1 + 23) = ctemp24;
	*(boffset1 + 24) = ctemp25;
	*(boffset1 + 25) = ctemp26;
	*(boffset1 + 26) = ctemp27;
	*(boffset1 + 27) = ctemp28;
	*(boffset1 + 28) = ctemp29;
	*(boffset1 + 29) = ctemp30;
	*(boffset1 + 30) = ctemp31;
	*(boffset1 + 31) = ctemp32;

	*(boffset1 + 32) = ctemp33;
	*(boffset1 + 33) = ctemp34;
	*(boffset1 + 34) = ctemp35;
	*(boffset1 + 35) = ctemp36;
	*(boffset1 + 36) = ctemp37;
	*(boffset1 + 37) = ctemp38;
	*(boffset1 + 38) = ctemp39;
	*(boffset1 + 39) = ctemp40;
	*(boffset1 + 40) = ctemp41;
	*(boffset1 + 41) = ctemp42;
	*(boffset1 + 42) = ctemp43;
	*(boffset1 + 43) = ctemp44;
	*(boffset1 + 44) = ctemp45;
	*(boffset1 + 45) = ctemp46;
	*(boffset1 + 46) = ctemp47;
	*(boffset1 + 47) = ctemp48;

	*(boffset1 + 48) = ctemp49;
	*(boffset1 + 49) = ctemp50;
	*(boffset1 + 50) = ctemp51;
	*(boffset1 + 51) = ctemp52;
	*(boffset1 + 52) = ctemp53;
	*(boffset1 + 53) = ctemp54;
	*(boffset1 + 54) = ctemp55;
	*(boffset1 + 55) = ctemp56;
	*(boffset1 + 56) = ctemp57;
	*(boffset1 + 57) = ctemp58;
	*(boffset1 + 58) = ctemp59;
	*(boffset1 + 59) = ctemp60;
	*(boffset1 + 60) = ctemp61;
	*(boffset1 + 61) = ctemp62;
	*(boffset1 + 62) = ctemp63;
	*(boffset1 + 63) = ctemp64;

    boffset1 += m * 16;
	i --;
	}while(i > 0);
    }

    if (n & 8){
	ctemp01 = *(aoffset1 + 0);
	ctemp02 = *(aoffset1 + 1);
	ctemp03 = *(aoffset1 + 2);
	ctemp04 = *(aoffset1 + 3);
	ctemp05 = *(aoffset1 + 4);
	ctemp06 = *(aoffset1 + 5);
	ctemp07 = *(aoffset1 + 6);
	ctemp08 = *(aoffset1 + 7);
	aoffset1 += 8;

	ctemp09 = *(aoffset2 + 0);
	ctemp10 = *(aoffset2 + 1);
	ctemp11 = *(aoffset2 + 2);
	ctemp12 = *(aoffset2 + 3);
	ctemp13 = *(aoffset2 + 4);
	ctemp14 = *(aoffset2 + 5);
	ctemp15 = *(aoffset2 + 6);
	ctemp16 = *(aoffset2 + 7);
	aoffset2 += 8;

	ctemp17 = *(aoffset3 + 0);
	ctemp18 = *(aoffset3 + 1);
	ctemp19 = *(aoffset3 + 2);
	ctemp20 = *(aoffset3 + 3);
	ctemp21 = *(aoffset3 + 4);
	ctemp22 = *(aoffset3 + 5);
	ctemp23 = *(aoffset3 + 6);
	ctemp24 = *(aoffset3 + 7);
	aoffset3 += 8;

	ctemp25 = *(aoffset4 + 0);
	ctemp26 = *(aoffset4 + 1);
	ctemp27 = *(aoffset4 + 2);
	ctemp28 = *(aoffset4 + 3);
	ctemp29 = *(aoffset4 + 4);
	ctemp30 = *(aoffset4 + 5);
	ctemp31 = *(aoffset4 + 6);
	ctemp32 = *(aoffset4 + 7);
	aoffset4 += 8;

	*(boffset5 +  0) = ctemp01;
	*(boffset5 +  1) = ctemp02;
	*(boffset5 +  2) = ctemp03;
	*(boffset5 +  3) = ctemp04;
	*(boffset5 +  4) = ctemp05;
	*(boffset5 +  5) = ctemp06;
	*(boffset5 +  6) = ctemp07;
	*(boffset5 +  7) = ctemp08;

	*(boffset5 +  8) = ctemp09;
	*(boffset5 +  9) = ctemp10;
	*(boffset5 + 10) = ctemp11;
	*(boffset5 + 11) = ctemp12;
	*(boffset5 + 12) = ctemp13;
	*(boffset5 + 13) = ctemp14;
	*(boffset5 + 14) = ctemp15;
	*(boffset5 + 15) = ctemp16;

	*(boffset5 + 16) = ctemp17;
	*(boffset5 + 17) = ctemp18;
	*(boffset5 + 18) = ctemp19;
	*(boffset5 + 19) = ctemp20;
	*(boffset5 + 20) = ctemp21;
	*(boffset5 + 21) = ctemp22;
	*(boffset5 + 22) = ctemp23;
	*(boffset5 + 23) = ctemp24;

	*(boffset5 + 24) = ctemp25;
	*(boffset5 + 25) = ctemp26;
	*(boffset5 + 26) = ctemp27;
	*(boffset5 + 27) = ctemp28;
	*(boffset5 + 28) = ctemp29;
	*(boffset5 + 29) = ctemp30;
	*(boffset5 + 30) = ctemp31;
	*(boffset5 + 31) = ctemp32;

	boffset5 += 32;
    }

    if (n & 4) {
      ctemp01 = *(aoffset1 + 0);
      ctemp02 = *(aoffset1 + 1);
      ctemp03 = *(aoffset1 + 2);
      ctemp04 = *(aoffset1 + 3);
      aoffset1 += 4;

      ctemp05 = *(aoffset2 + 0);
      ctemp06 = *(aoffset2 + 1);
      ctemp07 = *(aoffset2 + 2);
      ctemp08 = *(aoffset2 + 3);
      aoffset2 += 4;

      ctemp09 = *(aoffset3 + 0);
      ctemp10 = *(aoffset3 + 1);
      ctemp11 = *(aoffset3 + 2);
      ctemp12 = *(aoffset3 + 3);
      aoffset3 += 4;

      ctemp13 = *(aoffset4 + 0);
      ctemp14 = *(aoffset4 + 1);
      ctemp15 = *(aoffset4 + 2);
      ctemp16 = *(aoffset4 + 3);
      aoffset4 += 4;

      *(boffset2 +  0) = ctemp01;
      *(boffset2 +  1) = ctemp02;
      *(boffset2 +  2) = ctemp03;
      *(boffset2 +  3) = ctemp04;
      *(boffset2 +  4) = ctemp05;
      *(boffset2 +  5) = ctemp06;
      *(boffset2 +  6) = ctemp07;
      *(boffset2 +  7) = ctemp08;

      *(boffset2 +  8) = ctemp09;
      *(boffset2 +  9) = ctemp10;
      *(boffset2 + 10) = ctemp11;
      *(boffset2 + 11) = ctemp12;
      *(boffset2 + 12) = ctemp13;
      *(boffset2 + 13) = ctemp14;
      *(boffset2 + 14) = ctemp15;
      *(boffset2 + 15) = ctemp16;
      boffset2 += 16;
    }

    if (n & 2){
      ctemp01 = *(aoffset1 + 0);
      ctemp02 = *(aoffset1 + 1);
      aoffset1 += 2;

      ctemp03 = *(aoffset2 + 0);
      ctemp04 = *(aoffset2 + 1);
      aoffset2 += 2;

      ctemp05 = *(aoffset3 + 0);
      ctemp06 = *(aoffset3 + 1);
      aoffset3 += 2;

      ctemp07 = *(aoffset4 + 0);
      ctemp08 = *(aoffset4 + 1);
      aoffset4 += 2;

      *(boffset3 +  0) = ctemp01;
      *(boffset3 +  1) = ctemp02;
      *(boffset3 +  2) = ctemp03;
      *(boffset3 +  3) = ctemp04;
      *(boffset3 +  4) = ctemp05;
      *(boffset3 +  5) = ctemp06;
      *(boffset3 +  6) = ctemp07;
      *(boffset3 +  7) = ctemp08;
      boffset3 += 8;
    }

    if (n & 1){
      ctemp01 = *(aoffset1 + 0);
      aoffset1 ++;
      ctemp02 = *(aoffset2 + 0);
      aoffset2 ++;
      ctemp03 = *(aoffset3 + 0);
      aoffset3 ++;
      ctemp04 = *(aoffset4 + 0);
      aoffset4 ++;

      *(boffset4 +  0) = ctemp01;
      *(boffset4 +  1) = ctemp02;
      *(boffset4 +  2) = ctemp03;
      *(boffset4 +  3) = ctemp04;
      boffset4 += 4;
    }
  }

  if (m & 2){
    aoffset1  = aoffset;
    aoffset2  = aoffset1 + lda;
    aoffset += 2 * lda;

    boffset1  = boffset;
    boffset  += 32;

    i = (n >> 4);
    if (i > 0){
	    do{
	  ctemp01 = *(aoffset1 + 0);
	  ctemp02 = *(aoffset1 + 1);
	  ctemp03 = *(aoffset1 + 2);
	  ctemp04 = *(aoffset1 + 3);
	  ctemp05 = *(aoffset1 + 4);
	  ctemp06 = *(aoffset1 + 5);
	  ctemp07 = *(aoffset1 + 6);
	  ctemp08 = *(aoffset1 + 7);
	  ctemp09 = *(aoffset1 + 8);
	  ctemp10 = *(aoffset1 + 9);
	  ctemp11 = *(aoffset1 + 10);
	  ctemp12 = *(aoffset1 + 11);
	  ctemp13 = *(aoffset1 + 12);
	  ctemp14 = *(aoffset1 + 13);
	  ctemp15 = *(aoffset1 + 14);
	  ctemp16 = *(aoffset1 + 15);
	  aoffset1 += 16;

	  ctemp17 = *(aoffset2 + 0);
	  ctemp18 = *(aoffset2 + 1);
	  ctemp19 = *(aoffset2 + 2);
	  ctemp20 = *(aoffset2 + 3);
	  ctemp21 = *(aoffset2 + 4);
	  ctemp22 = *(aoffset2 + 5);
	  ctemp23 = *(aoffset2 + 6);
	  ctemp24 = *(aoffset2 + 7);
	  ctemp25 = *(aoffset2 + 8);
	  ctemp26 = *(aoffset2 + 9);
	  ctemp27 = *(aoffset2 + 10);
	  ctemp28 = *(aoffset2 + 11);
	  ctemp29 = *(aoffset2 + 12);
	  ctemp30 = *(aoffset2 + 13);
	  ctemp31 = *(aoffset2 + 14);
	  ctemp32 = *(aoffset2 + 15);
	  aoffset2 += 16;

	  *(boffset1 +  0) = ctemp01;
	  *(boffset1 +  1) = ctemp02;
	  *(boffset1 +  2) = ctemp03;
	  *(boffset1 +  3) = ctemp04;
	  *(boffset1 +  4) = ctemp05;
	  *(boffset1 +  5) = ctemp06;
	  *(boffset1 +  6) = ctemp07;
	  *(boffset1 +  7) = ctemp08;
	  *(boffset1 +  8) = ctemp09;
	  *(boffset1 +  9) = ctemp10;
	  *(boffset1 + 10) = ctemp11;
	  *(boffset1 + 11) = ctemp12;
	  *(boffset1 + 12) = ctemp13;
	  *(boffset1 + 13) = ctemp14;
	  *(boffset1 + 14) = ctemp15;
	  *(boffset1 + 15) = ctemp16;

	  *(boffset1 + 16) = ctemp17;
	  *(boffset1 + 17) = ctemp18;
	  *(boffset1 + 18) = ctemp19;
	  *(boffset1 + 19) = ctemp20;
	  *(boffset1 + 20) = ctemp21;
	  *(boffset1 + 21) = ctemp22;
	  *(boffset1 + 22) = ctemp23;
	  *(boffset1 + 23) = ctemp24;
	  *(boffset1 + 24) = ctemp25;
	  *(boffset1 + 25) = ctemp26;
	  *(boffset1 + 26) = ctemp27;
	  *(boffset1 + 27) = ctemp28;
	  *(boffset1 + 28) = ctemp29;
	  *(boffset1 + 29) = ctemp30;
	  *(boffset1 + 30) = ctemp31;
	  *(boffset1 + 31) = ctemp32;

	  boffset1 += m * 16;
	  i --;
	}while(i > 0);
      }

    if (n & 8){
	ctemp01 = *(aoffset1 + 0);
	ctemp02 = *(aoffset1 + 1);
	ctemp03 = *(aoffset1 + 2);
	ctemp04 = *(aoffset1 + 3);
	ctemp05 = *(aoffset1 + 4);
	ctemp06 = *(aoffset1 + 5);
	ctemp07 = *(aoffset1 + 6);
	ctemp08 = *(aoffset1 + 7);
	aoffset1 += 8;

	ctemp09 = *(aoffset2 + 0);
	ctemp10 = *(aoffset2 + 1);
	ctemp11 = *(aoffset2 + 2);
	ctemp12 = *(aoffset2 + 3);
	ctemp13 = *(aoffset2 + 4);
	ctemp14 = *(aoffset2 + 5);
	ctemp15 = *(aoffset2 + 6);
	ctemp16 = *(aoffset2 + 7);
	aoffset2 += 8;

	*(boffset5 +  0) = ctemp01;
	*(boffset5 +  1) = ctemp02;
	*(boffset5 +  2) = ctemp03;
	*(boffset5 +  3) = ctemp04;
	*(boffset5 +  4) = ctemp05;
	*(boffset5 +  5) = ctemp06;
	*(boffset5 +  6) = ctemp07;
	*(boffset5 +  7) = ctemp08;

	*(boffset5 +  8) = ctemp09;
	*(boffset5 +  9) = ctemp10;
	*(boffset5 + 10) = ctemp11;
	*(boffset5 + 11) = ctemp12;
	*(boffset5 + 12) = ctemp13;
	*(boffset5 + 13) = ctemp14;
	*(boffset5 + 14) = ctemp15;
	*(boffset5 + 15) = ctemp16;

	 boffset5 += 16;
    }

    if (n & 4){
      ctemp01 = *(aoffset1 + 0);
      ctemp02 = *(aoffset1 + 1);
      ctemp03 = *(aoffset1 + 2);
      ctemp04 = *(aoffset1 + 3);
      aoffset1 += 4;

      ctemp05 = *(aoffset2 + 0);
      ctemp06 = *(aoffset2 + 1);
      ctemp07 = *(aoffset2 + 2);
      ctemp08 = *(aoffset2 + 3);
      aoffset2 += 4;

      *(boffset2 +  0) = ctemp01;
      *(boffset2 +  1) = ctemp02;
      *(boffset2 +  2) = ctemp03;
      *(boffset2 +  3) = ctemp04;
      *(boffset2 +  4) = ctemp05;
      *(boffset2 +  5) = ctemp06;
      *(boffset2 +  6) = ctemp07;
      *(boffset2 +  7) = ctemp08;
      boffset2 += 8;
    }

    if (n & 2){
      ctemp01 = *(aoffset1 + 0);
      ctemp02 = *(aoffset1 + 1);
      aoffset1 += 2;

      ctemp03 = *(aoffset2 + 0);
      ctemp04 = *(aoffset2 + 1);
      aoffset2 += 2;

      *(boffset3 +  0) = ctemp01;
      *(boffset3 +  1) = ctemp02;
      *(boffset3 +  2) = ctemp03;
      *(boffset3 +  3) = ctemp04;
      boffset3 += 4;
    }

    if (n & 1){
      ctemp01 = *(aoffset1 + 0);
      aoffset1 ++;
      ctemp02 = *(aoffset2 + 0);
      aoffset2 ++;

      *(boffset4 +  0) = ctemp01;
      *(boffset4 +  1) = ctemp02;
      boffset4 += 2;
    }
  }

  if (m & 1){
    aoffset1  = aoffset;
    // aoffset += lda;

    boffset1  = boffset;
    // boffset  += 8;

    i = (n >> 4);
    if (i > 0){
      do{
	ctemp01 = *(aoffset1 + 0);
	ctemp02 = *(aoffset1 + 1);
	ctemp03 = *(aoffset1 + 2);
	ctemp04 = *(aoffset1 + 3);
	ctemp05 = *(aoffset1 + 4);
	ctemp06 = *(aoffset1 + 5);
	ctemp07 = *(aoffset1 + 6);
	ctemp08 = *(aoffset1 + 7);
	ctemp09 = *(aoffset1 + 8);
	ctemp10 = *(aoffset1 + 9);
	ctemp11 = *(aoffset1 + 10);
	ctemp12 = *(aoffset1 + 11);
	ctemp13 = *(aoffset1 + 12);
	ctemp14 = *(aoffset1 + 13);
	ctemp15 = *(aoffset1 + 14);
	ctemp16 = *(aoffset1 + 15);
	aoffset1 += 16;

	*(boffset1 +  0) = ctemp01;
	*(boffset1 +  1) = ctemp02;
	*(boffset1 +  2) = ctemp03;
	*(boffset1 +  3) = ctemp04;
	*(boffset1 +  4) = ctemp05;
	*(boffset1 +  5) = ctemp06;
	*(boffset1 +  6) = ctemp07;
	*(boffset1 +  7) = ctemp08;
	*(boffset1 +  8) = ctemp09;
	*(boffset1 +  9) = ctemp10;
	*(boffset1 + 10) = ctemp11;
	*(boffset1 + 11) = ctemp12;
	*(boffset1 + 12) = ctemp13;
	*(boffset1 + 13) = ctemp14;
	*(boffset1 + 14) = ctemp15;
	*(boffset1 + 15) = ctemp16;

	boffset1 += 16 * m;
	 i --;
       }while(i > 0);
     }

     if (n & 8){
       ctemp01 = *(aoffset1 + 0);
       ctemp02 = *(aoffset1 + 1);
       ctemp03 = *(aoffset1 + 2);
       ctemp04 = *(aoffset1 + 3);
       ctemp05 = *(aoffset1 + 4);
       ctemp06 = *(aoffset1 + 5);
       ctemp07 = *(aoffset1 + 6);
       ctemp08 = *(aoffset1 + 7);
       aoffset1 += 8;

       *(boffset5 +  0) = ctemp01;
       *(boffset5 +  1) = ctemp02;
       *(boffset5 +  2) = ctemp03;
       *(boffset5 +  3) = ctemp04;
       *(boffset5 +  4) = ctemp05;
       *(boffset5 +  5) = ctemp06;
       *(boffset5 +  6) = ctemp07;
       *(boffset5 +  7) = ctemp08;
       // boffset2 += 4;
     }

     if (n & 4){
       ctemp01 = *(aoffset1 + 0);
       ctemp02 = *(aoffset1 + 1);
       ctemp03 = *(aoffset1 + 2);
       ctemp04 = *(aoffset1 + 3);
       aoffset1 += 4;

       *(boffset2 +  0) = ctemp01;
       *(boffset2 +  1) = ctemp02;
       *(boffset2 +  2) = ctemp03;
       *(boffset2 +  3) = ctemp04;
       // boffset2 += 4;
     }

     if (n & 2){
       ctemp01 = *(aoffset1 + 0);
       ctemp02 = *(aoffset1 + 1);
       aoffset1 += 2;

       *(boffset3 +  0) = ctemp01;
       *(boffset3 +  1) = ctemp02;
       // boffset3 += 2;
     }

     if (n & 1){
       ctemp01 = *(aoffset1 + 0);
       aoffset1 ++;
      *(boffset4 +  0) = ctemp01;
      boffset4 ++;
    }
  }

  return 0;
}
