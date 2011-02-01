/* Intel Atom/32 gmp-mparam.h -- Compiler/machine parameter header file.

Copyright 1991, 1993, 1994, 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007,
2008, 2009, 2010, 2011 Free Software Foundation, Inc.

This file is part of the GNU MP Library.

The GNU MP Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

The GNU MP Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the GNU MP Library.  If not, see http://www.gnu.org/licenses/.  */

#define GMP_LIMB_BITS 32
#define BYTES_PER_MP_LIMB 4

/* Generated by tuneup.c */

#define MOD_1_NORM_THRESHOLD                 3
#define MOD_1_UNNORM_THRESHOLD              10
#define MOD_1N_TO_MOD_1_1_THRESHOLD         55
#define MOD_1U_TO_MOD_1_1_THRESHOLD          9
#define MOD_1_1_TO_MOD_1_2_THRESHOLD         0
#define MOD_1_2_TO_MOD_1_4_THRESHOLD        15
#define PREINV_MOD_1_TO_MOD_1_THRESHOLD  MP_SIZE_T_MAX  /* never */
#define USE_PREINV_DIVREM_1                  1  /* native */
#define DIVEXACT_1_THRESHOLD                 0  /* always (native) */
#define BMOD_1_TO_MOD_1_THRESHOLD        MP_SIZE_T_MAX  /* never */

#define MUL_TOOM22_THRESHOLD                18
#define MUL_TOOM33_THRESHOLD                69
#define MUL_TOOM44_THRESHOLD               178
#define MUL_TOOM6H_THRESHOLD               254
#define MUL_TOOM8H_THRESHOLD               357

#define MUL_TOOM32_TO_TOOM43_THRESHOLD      73
#define MUL_TOOM32_TO_TOOM53_THRESHOLD      85
#define MUL_TOOM42_TO_TOOM53_THRESHOLD     105
#define MUL_TOOM42_TO_TOOM63_THRESHOLD      58

#define SQR_BASECASE_THRESHOLD               0  /* always (native) */
#define SQR_TOOM2_THRESHOLD                 34
#define SQR_TOOM3_THRESHOLD                109
#define SQR_TOOM4_THRESHOLD                184
#define SQR_TOOM6_THRESHOLD                256
#define SQR_TOOM8_THRESHOLD                357

#define MULMOD_BNM1_THRESHOLD               16
#define SQRMOD_BNM1_THRESHOLD                7

#define MUL_FFT_MODF_THRESHOLD             380  /* k = 5 */
#define MUL_FFT_TABLE3                                      \
  { {    380, 5}, {     17, 6}, {      9, 5}, {     19, 6}, \
    {     11, 5}, {     23, 6}, {     21, 7}, {     11, 6}, \
    {     25, 7}, {     13, 6}, {     27, 7}, {     15, 6}, \
    {     31, 7}, {     21, 8}, {     11, 7}, {     27, 8}, \
    {     15, 7}, {     33, 8}, {     19, 7}, {     39, 8}, \
    {     23, 7}, {     47, 8}, {     27, 9}, {     15, 8}, \
    {     39, 9}, {     23, 8}, {     47,10}, {     15, 9}, \
    {     31, 8}, {     67, 9}, {     39, 8}, {     79, 9}, \
    {     47,10}, {     31, 9}, {     79,10}, {     47, 9}, \
    {     95,11}, {     31,10}, {     63, 9}, {    127, 8}, \
    {    255, 9}, {    135,10}, {     79, 9}, {    159,10}, \
    {     95, 9}, {    191, 8}, {    383,11}, {     63,10}, \
    {    127, 9}, {    255, 8}, {    511,10}, {    143, 9}, \
    {    287, 8}, {    607,10}, {    159, 9}, {    319,11}, \
    {     95,10}, {    191, 9}, {    383,12}, {     63,11}, \
    {    127,10}, {    255, 9}, {    511,10}, {    271, 9}, \
    {    543, 8}, {   1087,10}, {    287, 9}, {    607,11}, \
    {    159,10}, {    319, 9}, {    639,10}, {    351, 9}, \
    {    703,11}, {    191,10}, {    415, 9}, {    831,11}, \
    {    223,10}, {    447,12}, {    127,11}, {    255,10}, \
    {    543, 9}, {   1087,11}, {    287,10}, {    607, 9}, \
    {   1215,11}, {    319,10}, {    639,11}, {    351,10}, \
    {    703,12}, {    191,11}, {    415,10}, {    831,11}, \
    {    479,13}, {   8192,14}, {  16384,15}, {  32768,16} }
#define MUL_FFT_TABLE3_SIZE 96
#define MUL_FFT_THRESHOLD                 3712

#define SQR_FFT_MODF_THRESHOLD             308  /* k = 5 */
#define SQR_FFT_TABLE3                                      \
  { {    308, 5}, {     21, 6}, {     11, 5}, {     23, 6}, \
    {     21, 7}, {     11, 6}, {     24, 7}, {     13, 6}, \
    {     27, 7}, {     15, 6}, {     31, 7}, {     21, 8}, \
    {     11, 7}, {     27, 8}, {     15, 7}, {     33, 8}, \
    {     19, 7}, {     39, 8}, {     23, 7}, {     47, 8}, \
    {     27, 9}, {     15, 8}, {     39, 9}, {     23, 8}, \
    {     47,10}, {     15, 9}, {     31, 8}, {     63, 9}, \
    {     39, 8}, {     79, 9}, {     47,10}, {     31, 9}, \
    {     79,10}, {     47, 9}, {     95,11}, {     31,10}, \
    {     63, 9}, {    127, 8}, {    255,10}, {     79, 9}, \
    {    159, 8}, {    319,10}, {     95, 9}, {    191, 8}, \
    {    383,11}, {     63,10}, {    127, 9}, {    255, 8}, \
    {    511, 9}, {    271, 8}, {    543,10}, {    143, 9}, \
    {    287, 8}, {    575, 9}, {    303,10}, {    159, 9}, \
    {    319, 8}, {    639,11}, {     95,10}, {    191, 9}, \
    {    383,12}, {     63,11}, {    127,10}, {    255, 9}, \
    {    511,10}, {    271, 9}, {    543, 8}, {   1087,10}, \
    {    287, 9}, {    575,10}, {    303, 9}, {    607,11}, \
    {    159,10}, {    319, 9}, {    639,10}, {    351, 9}, \
    {    703,11}, {    191,10}, {    383, 9}, {    767,10}, \
    {    415, 9}, {    831,11}, {    223,10}, {    479, 9}, \
    {    959,12}, {    127,11}, {    255,10}, {    543, 9}, \
    {   1087,11}, {    287,10}, {    607, 9}, {   1215,11}, \
    {    319,10}, {    639,11}, {    351,10}, {    703,12}, \
    {    191,11}, {    383,10}, {    767,11}, {    415,10}, \
    {    831,11}, {    479,10}, {    959,13}, {   8192,14}, \
    {  16384,15}, {  32768,16} }
#define SQR_FFT_TABLE3_SIZE 106
#define SQR_FFT_THRESHOLD                 2752

#define MULLO_BASECASE_THRESHOLD             9
#define MULLO_DC_THRESHOLD                  31
#define MULLO_MUL_N_THRESHOLD             6633

#define DC_DIV_QR_THRESHOLD                 31
#define DC_DIVAPPR_Q_THRESHOLD             108
#define DC_BDIV_QR_THRESHOLD                28
#define DC_BDIV_Q_THRESHOLD                 77

#define INV_MULMOD_BNM1_THRESHOLD           34
#define INV_NEWTON_THRESHOLD               139
#define INV_APPR_THRESHOLD                 102

#define BINV_NEWTON_THRESHOLD              162
#define REDC_1_TO_REDC_N_THRESHOLD          40

#define MU_DIV_QR_THRESHOLD               1142
#define MU_DIVAPPR_Q_THRESHOLD            1078
#define MUPI_DIV_QR_THRESHOLD               69
#define MU_BDIV_QR_THRESHOLD               889
#define MU_BDIV_Q_THRESHOLD                998

#define MATRIX22_STRASSEN_THRESHOLD         15
#define HGCD_THRESHOLD                     133
#define GCD_DC_THRESHOLD                   469
#define GCDEXT_DC_THRESHOLD                348
#define JACOBI_BASE_METHOD                   3

#define GET_STR_DC_THRESHOLD                17
#define GET_STR_PRECOMPUTE_THRESHOLD        28
#define SET_STR_DC_THRESHOLD               704
#define SET_STR_PRECOMPUTE_THRESHOLD      1362
