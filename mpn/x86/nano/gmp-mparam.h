/* x86/nano gmp-mparam.h -- Compiler/machine parameter header file.

Copyright 1991, 1993, 1994, 2000-2011 Free Software Foundation, Inc.

This file is part of the GNU MP Library.

The GNU MP Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published
by the Free Software Foundation; either version 3 of the License, or (at
your option) any later version.

The GNU MP Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the GNU MP Library.  If not, see https://www.gnu.org/licenses/.  */

#define GMP_LIMB_BITS 32
#define GMP_LIMB_BYTES 4

/* Generated by tuneup.c, 2011-11-25, gcc 4.2 */

#define MOD_1_1P_METHOD                      1
#define MOD_1_NORM_THRESHOLD                 3
#define MOD_1_UNNORM_THRESHOLD               3
#define MOD_1N_TO_MOD_1_1_THRESHOLD         10
#define MOD_1U_TO_MOD_1_1_THRESHOLD          9
#define MOD_1_1_TO_MOD_1_2_THRESHOLD         0  /* never mpn_mod_1_1p */
#define MOD_1_2_TO_MOD_1_4_THRESHOLD        53
#define PREINV_MOD_1_TO_MOD_1_THRESHOLD     12
#define USE_PREINV_DIVREM_1                  1
#define DIV_QR_2_PI2_THRESHOLD           MP_SIZE_T_MAX  /* never */
#define DIVEXACT_1_THRESHOLD                 0  /* always (native) */
#define BMOD_1_TO_MOD_1_THRESHOLD           32

#define MUL_TOOM22_THRESHOLD                16
#define MUL_TOOM33_THRESHOLD               132
#define MUL_TOOM44_THRESHOLD               195
#define MUL_TOOM6H_THRESHOLD               270
#define MUL_TOOM8H_THRESHOLD               478

#define MUL_TOOM32_TO_TOOM43_THRESHOLD     129
#define MUL_TOOM32_TO_TOOM53_THRESHOLD     138
#define MUL_TOOM42_TO_TOOM53_THRESHOLD     130
#define MUL_TOOM42_TO_TOOM63_THRESHOLD     135

#define SQR_BASECASE_THRESHOLD               0  /* always (native) */
#define SQR_TOOM2_THRESHOLD                 28
#define SQR_TOOM3_THRESHOLD                194
#define SQR_TOOM4_THRESHOLD                502
#define SQR_TOOM6_THRESHOLD                746
#define SQR_TOOM8_THRESHOLD               1005

#define MULMID_TOOM42_THRESHOLD             40

#define MULMOD_BNM1_THRESHOLD               14
#define SQRMOD_BNM1_THRESHOLD               19

#define POWM_SEC_TABLE  4,23,258,828,2246

#define MUL_FFT_MODF_THRESHOLD             308  /* k = 5 */
#define MUL_FFT_TABLE3                                      \
  { {    308, 5}, {     13, 6}, {      7, 5}, {     17, 6}, \
    {      9, 5}, {     19, 6}, {     11, 5}, {     23, 6}, \
    {     13, 7}, {      7, 6}, {     17, 7}, {      9, 6}, \
    {     19, 7}, {     11, 6}, {     24, 7}, {     15, 6}, \
    {     31, 7}, {     19, 8}, {     11, 7}, {     25, 8}, \
    {     15, 7}, {     33, 8}, {     19, 7}, {     39, 8}, \
    {     23, 7}, {     47, 9}, {     15, 8}, {     31, 7}, \
    {     63, 8}, {     39, 9}, {     23, 8}, {     47,10}, \
    {     15, 9}, {     31, 8}, {     63, 9}, {     47,10}, \
    {     31, 9}, {     71,10}, {     47, 9}, {     95,11}, \
    {     31,10}, {     63, 9}, {    127, 8}, {    255,10}, \
    {     79, 9}, {    159,10}, {     95, 9}, {    191,11}, \
    {     63,10}, {    127, 9}, {    255, 8}, {    543, 9}, \
    {    287, 8}, {    575, 7}, {   1215,10}, {    159,11}, \
    {     95,10}, {    191,12}, {     63,11}, {    127,10}, \
    {    255, 9}, {    543, 8}, {   1087,10}, {    287, 9}, \
    {    607, 8}, {   1215,11}, {    159,10}, {    319, 9}, \
    {    639,10}, {    351, 9}, {    703, 8}, {   1407, 9}, \
    {    735, 8}, {   1471,11}, {    191,10}, {    383, 9}, \
    {    767,10}, {    415, 9}, {    831,11}, {    223,10}, \
    {    447, 9}, {    895,10}, {    479, 9}, {    959, 8}, \
    {   1919,12}, {   4096,13}, {   8192,14}, {  16384,15}, \
    {  32768,16} }
#define MUL_FFT_TABLE3_SIZE 89
#define MUL_FFT_THRESHOLD                 1856

#define SQR_FFT_MODF_THRESHOLD             396  /* k = 5 */
#define SQR_FFT_TABLE3                                      \
  { {    396, 5}, {     13, 6}, {      7, 5}, {     21, 6}, \
    {     11, 5}, {     23, 6}, {     21, 7}, {     11, 6}, \
    {     25, 7}, {     15, 6}, {     31, 7}, {     19, 6}, \
    {     39, 7}, {     21, 8}, {     11, 7}, {     23, 6}, \
    {     47, 7}, {     27, 8}, {     15, 7}, {     33, 8}, \
    {     19, 7}, {     39, 8}, {     23, 7}, {     47, 8}, \
    {     27, 9}, {     15, 8}, {     31, 7}, {     63, 8}, \
    {     39, 9}, {     23, 8}, {     47,10}, {     15, 9}, \
    {     31, 8}, {     63, 9}, {     39, 8}, {     79, 9}, \
    {     47,10}, {     31, 9}, {     79,10}, {     47, 9}, \
    {     95,11}, {     31,10}, {     63, 9}, {    127,10}, \
    {     79, 9}, {    159,10}, {     95,11}, {     63,10}, \
    {    127, 9}, {    255, 8}, {    543,10}, {    143, 9}, \
    {    287, 8}, {    607, 7}, {   1215, 6}, {   2431,10}, \
    {    159, 8}, {    639,11}, {     95,10}, {    191,12}, \
    {     63,11}, {    127,10}, {    255, 9}, {    543, 8}, \
    {   1087,10}, {    287, 9}, {    607, 8}, {   1215,11}, \
    {    159,10}, {    319, 9}, {    671,10}, {    351, 9}, \
    {    703, 8}, {   1407, 9}, {    735, 8}, {   1471, 7}, \
    {   2943,11}, {    191,10}, {    383, 9}, {    799,10}, \
    {    415, 9}, {    895,10}, {    479,12}, {   4096,13}, \
    {   8192,14}, {  16384,15}, {  32768,16} }
#define SQR_FFT_TABLE3_SIZE 87
#define SQR_FFT_THRESHOLD                 2368

#define MULLO_BASECASE_THRESHOLD             0  /* always */
#define MULLO_DC_THRESHOLD                  51
#define MULLO_MUL_N_THRESHOLD             3369

#define DC_DIV_QR_THRESHOLD                 56
#define DC_DIVAPPR_Q_THRESHOLD             183
#define DC_BDIV_QR_THRESHOLD                55
#define DC_BDIV_Q_THRESHOLD                118

#define INV_MULMOD_BNM1_THRESHOLD           30
#define INV_NEWTON_THRESHOLD               266
#define INV_APPR_THRESHOLD                 218

#define BINV_NEWTON_THRESHOLD              268
#define REDC_1_TO_REDC_N_THRESHOLD          56

#define MU_DIV_QR_THRESHOLD               1308
#define MU_DIVAPPR_Q_THRESHOLD            1528
#define MUPI_DIV_QR_THRESHOLD              124
#define MU_BDIV_QR_THRESHOLD               855
#define MU_BDIV_Q_THRESHOLD               1334

#define MATRIX22_STRASSEN_THRESHOLD         14
#define HGCD_THRESHOLD                     104
#define HGCD_APPR_THRESHOLD                139
#define HGCD_REDUCE_THRESHOLD             2121
#define GCD_DC_THRESHOLD                   456
#define GCDEXT_DC_THRESHOLD                321
#define JACOBI_BASE_METHOD                   4

#define GET_STR_DC_THRESHOLD                11
#define GET_STR_PRECOMPUTE_THRESHOLD        25
#define SET_STR_DC_THRESHOLD               542
#define SET_STR_PRECOMPUTE_THRESHOLD       840
