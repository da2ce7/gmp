/* Include file for internal GNU MP types and definitions.

Copyright (C) 1991, 1993, 1994, 1995, 1996 Free Software Foundation, Inc.

This file is part of the GNU MP Library.

The GNU MP Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Library General Public License as published by
the Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

The GNU MP Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
License for more details.

You should have received a copy of the GNU Library General Public License
along with the GNU MP Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111-1307, USA. */

/* When using gcc, make sure to use its builtin alloca.  */
#if ! defined (alloca) && defined (__GNUC__)
#define alloca __builtin_alloca
#define HAVE_ALLOCA
#endif

/* When using cc, do whatever necessary to allow use of alloca.  For many
   machines, this means including alloca.h.  IBM's compilers need a #pragma
   in "each module that needs to use alloca".  */
#if ! defined (alloca)
/* We need lots of variants for MIPS, to cover all versions and perversions
   of OSes for MIPS.  */
#if defined (__mips) || defined (MIPSEL) || defined (MIPSEB) \
 || defined (_MIPSEL) || defined (_MIPSEB) || defined (__sgi) \
 || defined (__alpha) || defined (__sparc) || defined (sparc) \
 || defined (__ksr__)
#include <alloca.h>
#define HAVE_ALLOCA
#endif
#if defined (_IBMR2)
#pragma alloca
#define HAVE_ALLOCA
#endif
#if defined (__DECC)
#define alloca(x) __ALLOCA(x)
#define HAVE_ALLOCA
#endif
#endif

#if defined (alloca)
#define HAVE_ALLOCA
#endif

#if ! defined (HAVE_ALLOCA) || USE_STACK_ALLOC
#include "stack-alloc.h"
#else
#define TMP_DECL(m)
#define TMP_ALLOC(x) alloca(x)
#define TMP_MARK(m)
#define TMP_FREE(m)
#endif

#ifndef NULL
#define NULL ((void *) 0)
#endif

#if ! defined (__GNUC__)
#define inline			/* Empty */
#endif

#define ABS(x) (x >= 0 ? x : -x)
#define MIN(l,o) ((l) < (o) ? (l) : (o))
#define MAX(h,i) ((h) > (i) ? (h) : (i))

/* Field access macros.  */
#define SIZ(x) ((x)->_mp_size)
#define ABSIZ(x) ABS (SIZ (x))
#define PTR(x) ((x)->_mp_d)
#define LIMBS(x) ((x)->_mp_d)
#define EXP(x) ((x)->_mp_exp)
#define PREC(x) ((x)->_mp_prec)
#define ALLOC(x) ((x)->_mp_alloc)

#include "gmp-mparam.h"
/* #include "longlong.h" */

#if (__STDC__-0) || defined (__cplusplus)
void *malloc (size_t);
void *realloc (void *, size_t);
void free (void *);

extern void *	(*_mp_allocate_func) (size_t);
extern void *	(*_mp_reallocate_func) (void *, size_t, size_t);
extern void	(*_mp_free_func) (void *, size_t);

void *_mp_default_allocate (size_t);
void *_mp_default_reallocate (void *, size_t, size_t);
void _mp_default_free (void *, size_t);

#else

#define const			/* Empty */
#define signed			/* Empty */

void *malloc ();
void *realloc ();
void free ();

extern void *	(*_mp_allocate_func) ();
extern void *	(*_mp_reallocate_func) ();
extern void	(*_mp_free_func) ();

void *_mp_default_allocate ();
void *_mp_default_reallocate ();
void _mp_default_free ();
#endif

#if defined (__GNUC__) && defined (__i386__)
#if 0			/* check that these actually improve things */
#define MPN_COPY_INCR(DST, SRC, N)					\
  __asm__ ("cld\n\trep\n\tmovsl" : :					\
	   "D" (DST), "S" (SRC), "c" (N) :				\
	   "cx", "di", "si", "memory")
#define MPN_COPY_DECR(DST, SRC, N)					\
  __asm__ ("std\n\trep\n\tmovsl" : :					\
	   "D" ((DST) + (N) - 1), "S" ((SRC) + (N) - 1), "c" (N) :	\
	   "cx", "di", "si", "memory")
#define MPN_NORMALIZE_NOT_ZERO(P, N)					\
  do {									\
    __asm__ ("std\n\trepe\n\tscasl" : "=c" (N) :			\
	     "a" (0), "D" ((P) + (N) - 1), "0" (N) :			\
	     "cx", "di");						\
    (N)++;								\
  } while (0)
#endif
#endif

/* Copy NLIMBS *limbs* from SRC to DST.  */
#ifndef MPN_COPY_INCR
#define MPN_COPY_INCR(DST, SRC, NLIMBS) \
  do {									\
    mp_size_t __i;							\
    for (__i = 0; __i < (NLIMBS); __i++)				\
      (DST)[__i] = (SRC)[__i];						\
  } while (0)
#endif

#ifndef MPN_COPY_DECR
#define MPN_COPY_DECR(DST, SRC, NLIMBS) \
  do {									\
    mp_size_t __i;							\
    for (__i = (NLIMBS) - 1; __i >= 0; __i--)				\
      (DST)[__i] = (SRC)[__i];						\
  } while (0)
#endif

/* Define MPN_COPY for vector computers.  Since #pragma cannot be in a macro,
   rely on function inlining. */
#if defined (_CRAY) || defined (__uxp__)
static inline void
_MPN_COPY (d, s, n) mp_ptr d; mp_srcptr s; mp_size_t n;
{
  int i;				/* Faster for Cray with plain int */
#pragma _CRI ivdep			/* Cray PVP systems */
#pragma loop noalias d,s		/* Fujitsu VPP systems */
  for (i = 0; i < n; i++)
    d[i] = s[i];
}
#define MPN_COPY _MPN_COPY
#endif

#ifndef MPN_COPY
#define MPN_COPY MPN_COPY_INCR
#endif

/* Zero NLIMBS *limbs* AT DST.  */
#ifndef MPN_ZERO
#define MPN_ZERO(DST, NLIMBS) \
  do {									\
    mp_size_t __i;							\
    for (__i = 0; __i < (NLIMBS); __i++)				\
      (DST)[__i] = 0;							\
  } while (0)
#endif

#ifndef MPN_NORMALIZE
#define MPN_NORMALIZE(DST, NLIMBS) \
  do {									\
    while (NLIMBS > 0)							\
      {									\
	if ((DST)[(NLIMBS) - 1] != 0)					\
	  break;							\
	NLIMBS--;							\
      }									\
  } while (0)
#endif
#ifndef MPN_NORMALIZE_NOT_ZERO
#define MPN_NORMALIZE_NOT_ZERO(DST, NLIMBS) \
  do {									\
    while (1)								\
      {									\
	if ((DST)[(NLIMBS) - 1] != 0)					\
	  break;							\
	NLIMBS--;							\
      }									\
  } while (0)
#endif

/* Initialize X of type mpz_t with space for NLIMBS limbs.  X should be a
   temporary variable; it will be automatically cleared out at function
   return.  We use __x here to make it possible to accept both mpz_ptr and
   mpz_t arguments.  */
#define MPZ_TMP_INIT(X, NLIMBS) \
  do {									\
    mpz_ptr __x = (X);							\
    __x->_mp_alloc = (NLIMBS);						\
    __x->_mp_d = (mp_ptr) TMP_ALLOC ((NLIMBS) * BYTES_PER_MP_LIMB);	\
  } while (0)

#define MPN_MUL_N_RECURSE(prodp, up, vp, size, tspace) \
  do {									\
    if ((size) < KARATSUBA_MUL_THRESHOLD)				\
      __gmpn_mul_basecase (prodp, up, size, vp, size);			\
    else								\
      __gmpn_mul_n (prodp, up, vp, size, tspace);			\
  } while (0);
#define MPN_SQR_RECURSE(prodp, up, size, tspace) \
  do {									\
    if ((size) < KARATSUBA_SQR_THRESHOLD)				\
      __gmpn_sqr_basecase (prodp, up, size);				\
    else								\
      __gmpn_sqr (prodp, up, size, tspace);				\
  } while (0);

/* If KARATSUBA_MUL_THRESHOLD is not already defined, define it to a
   value which is good on most machines.  */
#ifndef KARATSUBA_MUL_THRESHOLD
#define KARATSUBA_MUL_THRESHOLD 12
#endif

/* We can't handle KARATSUBA_MUL_THRESHOLD smaller than 2.  */
#if KARATSUBA_MUL_THRESHOLD < 2
#undef KARATSUBA_MUL_THRESHOLD
#define KARATSUBA_MUL_THRESHOLD 2
#endif

#ifndef KARATSUBA_SQR_THRESHOLD
#define KARATSUBA_SQR_THRESHOLD (2*KARATSUBA_MUL_THRESHOLD)
#endif

/* Structure for conversion between internal binary format and
   strings in base 2..36.  */
struct bases
{
  /* Number of digits in the conversion base that always fits in an mp_limb_t.
     For example, for base 10 on a machine where a mp_limb_t has 32 bits this
     is 9, since 10**9 is the largest number that fits into a mp_limb_t.  */
  int chars_per_limb;

  /* log(2)/log(conversion_base) */
  double chars_per_bit_exactly;

  /* base**chars_per_limb, i.e. the biggest number that fits a word, built by
     factors of base.  Exception: For 2, 4, 8, etc, big_base is log2(base),
     i.e. the number of bits used to represent each digit in the base.  */
  mp_limb_t big_base;

  /* A BITS_PER_MP_LIMB bit approximation to 1/big_base, represented as a
     fixed-point number.  Instead of dividing by big_base an application can
     choose to multiply by big_base_inverted.  */
  mp_limb_t big_base_inverted;
};

extern const struct bases __mp_bases[];
extern mp_size_t __gmp_default_fp_limb_precision;

/* Divide the two-limb number in (NH,,NL) by D, with DI being the largest
   limb not larger than (2**(2*BITS_PER_MP_LIMB))/D - (2**BITS_PER_MP_LIMB).
   If this would yield overflow, DI should be the largest possible number
   (i.e., only ones).  For correct operation, the most significant bit of D
   has to be set.  Put the quotient in Q and the remainder in R.  */
#define udiv_qrnnd_preinv(q, r, nh, nl, d, di) \
  do {									\
    mp_limb_t _q, _ql, _r;						\
    mp_limb_t _xh, _xl;							\
    umul_ppmm (_q, _ql, (nh), (di));					\
    _q += (nh);			/* DI is 2**BITS_PER_MP_LIMB too small */\
    umul_ppmm (_xh, _xl, _q, (d));					\
    sub_ddmmss (_xh, _r, (nh), (nl), _xh, _xl);				\
    if (_xh != 0)							\
      {									\
	sub_ddmmss (_xh, _r, _xh, _r, 0, (d));				\
	_q += 1;							\
	if (_xh != 0)							\
	  {								\
	    sub_ddmmss (_xh, _r, _xh, _r, 0, (d));			\
	    _q += 1;							\
	  }								\
      }									\
    if (_r >= (d))							\
      {									\
	_r -= (d);							\
	_q += 1;							\
      }									\
    (r) = _r;								\
    (q) = _q;								\
  } while (0)
/* Like udiv_qrnnd_preinv, but for for any value D.  DNORM is D shifted left
   so that its most significant bit is set.  LGUP is ceil(log2(D)).  */
#define udiv_qrnnd_preinv2gen(q, r, nh, nl, d, di, dnorm, lgup) \
  do {									\
    mp_limb_t _n2, _n10, _n1, _nadj, _q1;				\
    mp_limb_t _xh, _xl;							\
    _n2 = ((nh) << (BITS_PER_MP_LIMB - (lgup))) + ((nl) >> 1 >> (l - 1));\
    _n10 = (nl) << (BITS_PER_MP_LIMB - (lgup));				\
    _n1 = ((mp_limb_signed_t) _n10 >> (BITS_PER_MP_LIMB - 1));		\
    _nadj = _n10 + (_n1 & (dnorm));					\
    umul_ppmm (_xh, _xl, di, _n2 - _n1);				\
    add_ssaaaa (_xh, _xl, _xh, _xl, 0, _nadj);				\
    _q1 = ~(_n2 + _xh);							\
    umul_ppmm (_xh, _xl, _q1, d);					\
    add_ssaaaa (_xh, _xl, _xh, _xl, nh, nl);				\
    _xh -= (d);								\
    (r) = _xl + ((d) & _xh);						\
    (q) = _xh - _q1;							\
  } while (0)
/* Exactly like udiv_qrnnd_preinv, but branch-free.  It is not clear which
   version to use.  */
#define udiv_qrnnd_preinv2norm(q, r, nh, nl, d, di) \
  do {									\
    mp_limb_t _n2, _n10, _n1, _nadj, _q1;				\
    mp_limb_t _xh, _xl;							\
    _n2 = (nh);								\
    _n10 = (nl);							\
    _n1 = ((mp_limb_signed_t) _n10 >> (BITS_PER_MP_LIMB - 1));		\
    _nadj = _n10 + (_n1 & (d));						\
    umul_ppmm (_xh, _xl, di, _n2 - _n1);				\
    add_ssaaaa (_xh, _xl, _xh, _xl, 0, _nadj);				\
    _q1 = ~(_n2 + _xh);							\
    umul_ppmm (_xh, _xl, _q1, d);					\
    add_ssaaaa (_xh, _xl, _xh, _xl, nh, nl);				\
    _xh -= (d);								\
    (r) = _xl + ((d) & _xh);						\
    (q) = _xh - _q1;							\
  } while (0)

/* The `mode' attribute was introduced in GCC 2.2, but we can only distinguish
   between GCC 2 releases from 2.5, since __GNUC_MINOR__ wasn't introduced
   until then.  */
#if __GNUC__ - 0 > 2 || defined (__GNUC_MINOR__) && ! defined (__APPLE_CC__)
/* Define stuff for longlong.h.  */
typedef unsigned int UQItype	__attribute__ ((mode (QI)));
typedef		 int SItype	__attribute__ ((mode (SI)));
typedef unsigned int USItype	__attribute__ ((mode (SI)));
typedef		 int DItype	__attribute__ ((mode (DI)));
typedef unsigned int UDItype	__attribute__ ((mode (DI)));
#else
typedef unsigned char UQItype;
typedef		 long SItype;
typedef unsigned long USItype;
#if defined _LONGLONG || defined _LONG_LONG_LIMB
typedef	long long int DItype;
typedef unsigned long long int UDItype;
#endif
#endif

typedef mp_limb_t UWtype;
typedef unsigned int UHWtype;
#define W_TYPE_SIZE BITS_PER_MP_LIMB

/* Define ieee_double_extract and _GMP_IEEE_FLOATS.  */

#if (defined (__arm__) && (defined (__ARMWEL__) || defined (__linux__)))
/* Special case for little endian ARM since floats remain in big-endian.  */
#define _GMP_IEEE_FLOATS 1
union ieee_double_extract
{
  struct
    {
      unsigned int manh:20;
      unsigned int exp:11;
      unsigned int sig:1;
      unsigned int manl:32;
    } s;
  double d;
};
#else
#if defined (_LITTLE_ENDIAN) || defined (__LITTLE_ENDIAN__)		\
 || defined (__alpha)							\
 || defined (__clipper__)						\
 || defined (__cris)							\
 || defined (__i386__)							\
 || defined (__i860__)							\
 || defined (__i960__)							\
 || defined (MIPSEL) || defined (_MIPSEL)				\
 || defined (__ns32000__)						\
 || defined (__WINNT) || defined (_WIN32)
#define _GMP_IEEE_FLOATS 1
union ieee_double_extract
{
  struct
    {
      unsigned int manl:32;
      unsigned int manh:20;
      unsigned int exp:11;
      unsigned int sig:1;
    } s;
  double d;
};
#else /* Need this as an #else since the tests aren't made exclusive.  */
#if defined (_BIG_ENDIAN) || defined (__BIG_ENDIAN__)			\
 || defined (__a29k__) || defined (_AM29K)				\
 || defined (__arm__)							\
 || (defined (__convex__) && defined (_IEEE_FLOAT_))			\
 || defined (__i370__) || defined (__mvs__)				\
 || defined (__mc68000__) || defined (__mc68020__) || defined (__m68k__)\
    || defined(mc68020)							\
 || defined (__m88000__)						\
 || defined (MIPSEB) || defined (_MIPSEB)				\
 || defined (__hppa) || defined (__hppa__)				\
 || defined (__pyr__)							\
 || defined (__ibm032__)						\
 || defined (_IBMR2) || defined (_ARCH_PPC)				\
 || defined (__sh__)							\
 || defined (__sparc) || defined (sparc)				\
 || defined (__we32k__)
#define _GMP_IEEE_FLOATS 1
union ieee_double_extract
{
  struct
    {
      unsigned int sig:1;
      unsigned int exp:11;
      unsigned int manh:20;
      unsigned int manl:32;
    } s;
  double d;
};
#endif
#endif
#endif

#define MP_BASE_AS_DOUBLE (2.0 * ((mp_limb_t) 1 << (BITS_PER_MP_LIMB - 1)))
#if BITS_PER_MP_LIMB == 64
#define LIMBS_PER_DOUBLE 2
#else
#define LIMBS_PER_DOUBLE 3
#endif

double __gmp_scale2 _PROTO ((double, int));
int __gmp_extract_double _PROTO ((mp_ptr, double));

void __gmpn_mul_basecase _PROTO ((mp_ptr, mp_srcptr, mp_size_t, mp_srcptr, mp_size_t));
void __gmpn_sqr_basecase _PROTO ((mp_ptr, mp_srcptr, mp_size_t));
void __gmpn_mul_n _PROTO ((mp_ptr, mp_srcptr, mp_srcptr, mp_size_t, mp_ptr));
void __gmpn_sqr _PROTO ((mp_ptr, mp_srcptr, mp_size_t, mp_ptr));

extern int __gmp_junk;
extern const int __gmp_0;
#define DIVIDE_BY_ZERO (__gmp_junk = 10/__gmp_0)

#if defined _LONG_LONG_LIMB
#if defined (__STDC__)
#define CNST_LIMB(C) C##LL
#else
#define CNST_LIMB(C) C/**/LL
#endif
#else /* not _LONG_LONG_LIMB */
#if defined (__STDC__)
#define CNST_LIMB(C) C##L
#else
#define CNST_LIMB(C) C/**/L
#endif
#endif /* _LONG_LONG_LIMB */

/*** Stuff used by mpn/generic/prefsqr.c and mpn/generic/next_prime.c ***/
#if BITS_PER_MP_LIMB == 32
#define PP 0xC0CFD797L		/* 3 x 5 x 7 x 11 x 13 x ... x 29 */
#define PP_INVERTED 0x53E5645CL
#define PP_MAXPRIME 29
#define PP_MASK 0x208A28A8L
#endif

#if BITS_PER_MP_LIMB == 64
#define PP CNST_LIMB(0xE221F97C30E94E1D)	/* 3 x 5 x 7 x 11 x 13 x ... x 53 */
#define PP_INVERTED CNST_LIMB(0x21CFE6CFC938B36B)
#define PP_MAXPRIME 53
#define PP_MASK CNST_LIMB(0x208A20A08A28A8)
#endif

/* For testing and debugging.  */
#define MPZ_CHECK_FORMAT(z)						\
  do { if (SIZ(z) != 0 && PTR(z)[ABSIZ(z) - 1] == 0) abort ();		\
       if (ALLOC(z) < ABSIZ(z)) abort (); } while (0)
#define MPZ_PROVOKE_REALLOC(z)						\
  do { ALLOC(z) = ABSIZ(z); } while (0)
