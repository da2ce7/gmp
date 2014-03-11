/* POWER4/PowerPC970 gmp-mparam.h -- Compiler/machine parameter header file.

Copyright 2008-2010 Free Software Foundation, Inc.

This file is part of the GNU MP Library.

The GNU MP Library is free software; you can redistribute it and/or modify
it under the terms of either:

  * the GNU Lesser General Public License as published by the Free
    Software Foundation; either version 3 of the License, or (at your
    option) any later version.

or

  * the GNU General Public License as published by the Free Software
    Foundation; either version 2 of the License, or (at your option) any
    later version.

or both in parallel, as here.

The GNU MP Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received copies of the GNU General Public License and the
GNU Lesser General Public License along with the GNU MP Library.  If not,
see https://www.gnu.org/licenses/.  */

#define GMP_LIMB_BITS 64
#define GMP_LIMB_BYTES 8


#define MOD_1_NORM_THRESHOLD                 0  /* always */
#define MOD_1_UNNORM_THRESHOLD               0  /* always */
#define MOD_1N_TO_MOD_1_1_THRESHOLD          6
#define MOD_1U_TO_MOD_1_1_THRESHOLD          5
#define MOD_1_1_TO_MOD_1_2_THRESHOLD         9
#define MOD_1_2_TO_MOD_1_4_THRESHOLD        22
#define PREINV_MOD_1_TO_MOD_1_THRESHOLD     16
#define USE_PREINV_DIVREM_1                  0
#define DIV_QR_1N_PI1_METHOD                 1
#define DIV_QR_1_NORM_THRESHOLD              1
#define DIV_QR_1_UNNORM_THRESHOLD            1
#define DIV_QR_2_PI2_THRESHOLD           MP_SIZE_T_MAX  /* never */
#define DIVEXACT_1_THRESHOLD                 0  /* always (native) */
#define BMOD_1_TO_MOD_1_THRESHOLD           34

#define MUL_TOOM22_THRESHOLD                14
#define MUL_TOOM33_THRESHOLD                53
#define MUL_TOOM44_THRESHOLD               136
#define MUL_TOOM6H_THRESHOLD               197
#define MUL_TOOM8H_THRESHOLD               296

#define MUL_TOOM32_TO_TOOM43_THRESHOLD      89
#define MUL_TOOM32_TO_TOOM53_THRESHOLD      59
#define MUL_TOOM42_TO_TOOM53_THRESHOLD      89
#define MUL_TOOM42_TO_TOOM63_THRESHOLD      96
#define MUL_TOOM43_TO_TOOM54_THRESHOLD      79

#define SQR_BASECASE_THRESHOLD               0  /* always (native) */
#define SQR_TOOM2_THRESHOLD                 22
#define SQR_TOOM3_THRESHOLD                 85
#define SQR_TOOM4_THRESHOLD                130
#define SQR_TOOM6_THRESHOLD                270
#define SQR_TOOM8_THRESHOLD                430

#define MULMID_TOOM42_THRESHOLD             32

#define MULMOD_BNM1_THRESHOLD               12
#define SQRMOD_BNM1_THRESHOLD               15

#define MUL_FFT_MODF_THRESHOLD             380  /* k = 5 */
#define MUL_FFT_TABLE3                                      \
  { {    380, 5}, {     13, 6}, {      7, 5}, {     15, 6}, \
    {      8, 5}, {     17, 6}, {      9, 5}, {     19, 6}, \
    {     10, 5}, {     21, 6}, {     13, 5}, {     28, 6}, \
    {     19, 7}, {     10, 6}, {     21, 7}, {     12, 6}, \
    {     25, 7}, {     21, 8}, {     11, 7}, {     25, 8}, \
    {     13, 7}, {     27, 8}, {     21, 9}, {     11, 8}, \
    {     25, 6}, {    101, 8}, {     27, 9}, {     15, 8}, \
    {     35, 9}, {     19, 8}, {     39, 9}, {     23, 8}, \
    {     49, 9}, {     27,10}, {     15, 9}, {     39,10}, \
    {     23,11}, {     15,10}, {     31, 9}, {     71,10}, \
    {     47, 9}, {     95,10}, {     55,11}, {     31,10}, \
    {     63, 8}, {    255, 9}, {    131,10}, {     87,11}, \
    {     47,10}, {     95, 9}, {    191,10}, {    103,12}, \
    {     31,11}, {     63,10}, {    127, 9}, {    255, 8}, \
    {    511,10}, {    135, 9}, {    271,11}, {     79,10}, \
    {    159, 9}, {    319,10}, {    167,11}, {     95,10}, \
    {    191, 9}, {    383, 8}, {    767,10}, {    207, 9}, \
    {    415,11}, {    111,12}, {     63,11}, {    127,10}, \
    {    255, 9}, {    511,10}, {    271, 9}, {    543,11}, \
    {    143,10}, {    287, 9}, {    575,10}, {    303, 9}, \
    {    607,10}, {    319, 9}, {    639,10}, {    351,12}, \
    {     95,11}, {    191,10}, {    383, 9}, {    767,11}, \
    {    207,10}, {    415, 9}, {    831,13}, {   8192,14}, \
    {  16384,15}, {  32768,16}, {  65536,17}, { 131072,18}, \
    { 262144,19}, { 524288,20}, {1048576,21}, {2097152,22}, \
    {4194304,23}, {8388608,24} }
#define MUL_FFT_TABLE3_SIZE 102
#define MUL_FFT_THRESHOLD                 7424

#define SQR_FFT_MODF_THRESHOLD             308  /* k = 5 */
#define SQR_FFT_TABLE3                                      \
  { {    308, 5}, {     17, 6}, {      9, 5}, {     19, 6}, \
    {     10, 5}, {     21, 6}, {     13, 5}, {     28, 6}, \
    {     21, 7}, {     11, 6}, {     23, 7}, {     14, 6}, \
    {     29, 7}, {     21, 8}, {     11, 7}, {     25, 8}, \
    {     13, 7}, {     27, 8}, {     15, 7}, {     31, 8}, \
    {     17, 7}, {     35, 8}, {     21, 9}, {     11, 8}, \
    {     27, 9}, {     15, 8}, {     35, 9}, {     19, 8}, \
    {     39, 9}, {     23, 8}, {     47, 9}, {     27,10}, \
    {     15, 9}, {     39,10}, {     23, 9}, {     51,11}, \
    {     15,10}, {     31, 9}, {     67,10}, {     39, 9}, \
    {     83,10}, {     47, 9}, {     95,10}, {     55,11}, \
    {     31,10}, {     79,11}, {     47,10}, {     95, 9}, \
    {    191, 8}, {    383,12}, {     31,11}, {     63,10}, \
    {    127, 9}, {    255, 8}, {    511,10}, {    135, 9}, \
    {    271, 8}, {    543,11}, {     79,10}, {    159, 9}, \
    {    319, 8}, {    639, 9}, {    335,10}, {    175,11}, \
    {     95,10}, {    191, 9}, {    383, 8}, {    767,10}, \
    {    207, 9}, {    415,11}, {    111,12}, {     63,11}, \
    {    127,10}, {    255, 9}, {    511,10}, {    271, 9}, \
    {    543,10}, {    287, 9}, {    575,10}, {    303,11}, \
    {    159,10}, {    319, 9}, {    639,10}, {    335,11}, \
    {    175,10}, {    351,12}, {     95,11}, {    191,10}, \
    {    383, 9}, {    767,11}, {    207,10}, {    415, 9}, \
    {    831,11}, {    223,13}, {   8192,14}, {  16384,15}, \
    {  32768,16}, {  65536,17}, { 131072,18}, { 262144,19}, \
    { 524288,20}, {1048576,21}, {2097152,22}, {4194304,23}, \
    {8388608,24} }
#define SQR_FFT_TABLE3_SIZE 105
#define SQR_FFT_THRESHOLD                 6272

#define MULLO_BASECASE_THRESHOLD             5
#define MULLO_DC_THRESHOLD                  45
#define MULLO_MUL_N_THRESHOLD            13463

#define DC_DIV_QR_THRESHOLD                 43
#define DC_DIVAPPR_Q_THRESHOLD             167
#define DC_BDIV_QR_THRESHOLD                46
#define DC_BDIV_Q_THRESHOLD                120

#define INV_MULMOD_BNM1_THRESHOLD           42
#define INV_NEWTON_THRESHOLD               177
#define INV_APPR_THRESHOLD                 173

#define BINV_NEWTON_THRESHOLD              214
#define REDC_1_TO_REDC_N_THRESHOLD          56

#define MU_DIV_QR_THRESHOLD                998
#define MU_DIVAPPR_Q_THRESHOLD            1017
#define MUPI_DIV_QR_THRESHOLD               90
#define MU_BDIV_QR_THRESHOLD               889
#define MU_BDIV_Q_THRESHOLD               1017

#define POWM_SEC_TABLE  3,22,90,579,1925

#define MATRIX22_STRASSEN_THRESHOLD         15
#define HGCD_THRESHOLD                     110
#define HGCD_APPR_THRESHOLD                111
#define HGCD_REDUCE_THRESHOLD             5010
#define GCD_DC_THRESHOLD                   358
#define GCDEXT_DC_THRESHOLD                241
#define JACOBI_BASE_METHOD                   4

#define GET_STR_DC_THRESHOLD                11
#define GET_STR_PRECOMPUTE_THRESHOLD        23
#define SET_STR_DC_THRESHOLD               802
#define SET_STR_PRECOMPUTE_THRESHOLD      1712

#define FAC_DSC_THRESHOLD                  557
#define FAC_ODD_THRESHOLD                   25
