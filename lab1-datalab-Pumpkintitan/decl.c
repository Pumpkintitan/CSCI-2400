#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TMin INT_MIN
#define TMax INT_MAX

#include "btest.h"
#include "bits.h"

test_rec test_set[] = {
/* Copyright (C) 1991-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
/* We do not support C11 <threads.h>.  */
 {"bitNor", (funct_t) bitNor, (funct_t) test_bitNor, 2, "& ~", 8, 1,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"fitsShort", (funct_t) fitsShort, (funct_t) test_fitsShort, 1,
    "! ~ & ^ | + << >>", 8, 1,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"thirdBits", (funct_t) thirdBits, (funct_t) test_thirdBits, 0,
    "! ~ & ^ | + << >>", 8, 1,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"anyEvenBit", (funct_t) anyEvenBit, (funct_t) test_anyEvenBit, 1,
    "! ~ & ^ | + << >>", 12, 2,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"copyLSB", (funct_t) copyLSB, (funct_t) test_copyLSB, 1,
    "! ~ & ^ | + << >>", 5, 2,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"implication", (funct_t) implication, (funct_t) test_implication, 2, "! ~ ^ |", 5, 2,
     {{0,1},{0,1},{TMin,TMax}}},
 {"bitMask", (funct_t) bitMask, (funct_t) test_bitMask, 2,
    "! ~ & ^ | + << >>", 16, 3,
  {{0, 31},{0,31},{TMin,TMax}}},
 {"ezThreeFourths", (funct_t) ezThreeFourths, (funct_t) test_ezThreeFourths, 1,
    "! ~ & ^ | + << >>", 12, 3,
  {{TMin,TMax},{TMin,TMax},{TMin,TMax}}},
 {"satMul3", (funct_t) satMul3, (funct_t) test_satMul3, 1,
    "~ & ^ | + << >>", 25, 3,
  {{TMin,TMax},{TMin,TMax},{TMin,TMax}}},
 {"bitParity", (funct_t) bitParity, (funct_t) test_bitParity, 1, "! ~ & ^ | + << >>", 20, 4,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"ilog2", (funct_t) ilog2, (funct_t) test_ilog2, 1, "! ~ & ^ | + << >>", 90, 4,
  {{1, TMax},{TMin,TMax},{TMin,TMax}}},
 {"trueThreeFourths", (funct_t) trueThreeFourths, (funct_t) test_trueThreeFourths, 1,
    "! ~ & ^ | + << >>", 20, 4,
  {{TMin,TMax},{TMin,TMax},{TMin,TMax}}},
/*
 * Extra credit
 */
 {"float_neg", (funct_t) float_neg, (funct_t) test_float_neg, 1,
    "$", 10, 2,
     {{1, 1},{1,1},{1,1}}},
 {"float_i2f", (funct_t) float_i2f, (funct_t) test_float_i2f, 1,
    "$", 30, 4,
     {{1, 1},{1,1},{1,1}}},
 {"float_twice", (funct_t) float_twice, (funct_t) test_float_twice, 1,
    "$", 30, 4,
     {{1, 1},{1,1},{1,1}}},
  {"", NULL, NULL, 0, "", 0, 0,
   {{0, 0},{0,0},{0,0}}}
};
