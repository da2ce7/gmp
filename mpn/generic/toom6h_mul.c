/* Implementation of the algorithm for Toom-Cook 6.5-way.

   Contributed to the GNU project by Marco Bodrato.

   THE FUNCTION IN THIS FILE IS INTERNAL WITH A MUTABLE INTERFACE.  IT IS ONLY
   SAFE TO REACH IT THROUGH DOCUMENTED INTERFACES.  IN FACT, IT IS ALMOST
   GUARANTEED THAT IT WILL CHANGE OR DISAPPEAR IN A FUTURE GNU MP RELEASE.

Copyright 2009 Free Software Foundation, Inc.

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


#include "gmp.h"
#include "gmp-impl.h"


#if HAVE_NATIVE_mpn_sublsh_n
#define DO_mpn_sublsh_n(dst,src,n,s,ws) mpn_sublsh_n(dst,dst,src,n,s)
#else
static mp_limb_t
DO_mpn_sublsh_n(mp_ptr dst, mp_srcptr src, mp_size_t n, unsigned int s, mp_ptr ws)
{
#if USE_MUL_1 && 0
  return mpn_submul_1(dst,src,n,CNST_LIMB(1) <<(s));
#else
  mp_limb_t __cy;
  __cy = mpn_lshift(ws,src,n,s);
  return    __cy + mpn_sub_n(dst,dst,ws,n);
#endif
}
#endif

#if HAVE_NATIVE_mpn_addlsh_n
#define DO_mpn_addlsh_n(dst,src,n,s,ws) mpn_addlsh_n(dst,dst,src,n,s)
#else
static mp_limb_t
DO_mpn_addlsh_n(mp_ptr dst, mp_srcptr src, mp_size_t n, unsigned int s, mp_ptr ws)
{
#if USE_MUL_1 && 0
  return mpn_addmul_1(dst,src,n,CNST_LIMB(1) <<(s));
#else
  mp_limb_t __cy;
  __cy = mpn_lshift(ws,src,n,s);
  return    __cy + mpn_add_n(dst,dst,ws,n);
#endif
}
#endif

#if HAVE_NATIVE_mpn_subrsh
#define DO_mpn_subrsh(dst,nd,src,ns,s,ws) mpn_subrsh(dst,nd,src,ns,s)
#else
/* FIXME: This is not a correct definition, it assumes no carry */
#define DO_mpn_subrsh(dst,nd,src,ns,s,ws)				\
do {									\
  mp_limb_t __cy;							\
  MPN_DECR_U (dst, nd, src[0] >> s);					\
  __cy = DO_mpn_sublsh_n (dst, src + 1, ns - 1, GMP_NUMB_BITS - s, ws);	\
  MPN_DECR_U (dst + ns - 1, nd - ns + 1, __cy);				\
} while (0)
#endif


/* Stores |{ap,n}-{bp,n}| in {rp,n}, returns the sign. */
static int
abs_sub_n (mp_ptr rp, mp_srcptr ap, mp_srcptr bp, mp_size_t n)
{
  mp_limb_t  x, y;
  while (--n >= 0)
    {
      x = ap[n];
      y = bp[n];
      if (x != y)
	{
	  n++;
	  if (x > y)
	    {
	      mpn_sub_n (rp, ap, bp, n);
	      return 0;
	    }
	  else
	    {
	      mpn_sub_n (rp, bp, ap, n);
	      return 1;
	    }
	}
      rp[n] = 0;
    }
  return 0;
}

/* Gets {pp,n} and (sign?-1:1)*{np,n}. Computes at once: 
     {pp,n} <- ({pp,n}+{np,n})/2^{ps+1}
     {pn,n} <- ({pp,n}-{np,n})/2^{ns+1}
   Finally recompose them obtaining:
     {pp,n+off} <- {pp,n}+{np,n}*2^{off*GMP_NUMB_BITS}
*/
static void
toom_couple_handling (mp_ptr pp, mp_size_t n, mp_ptr np,
		      int nsign, mp_size_t off, int ps, int ns)
{
  if (nsign) {
#ifdef HAVE_NATIVE_mpn_rsh1sub_n
    mpn_rsh1sub_n (np, pp, np, n);
#else
    mpn_sub_n (np, pp, np, n);
    mpn_rshift (np, np, n, 1);
#endif
  } else {
#ifdef HAVE_NATIVE_mpn_rsh1add_n
    mpn_rsh1add_n (np, pp, np, n);
#else
    mpn_add_n (np, pp, np, n);
    mpn_rshift (np, np, n, 1);
#endif
  }

#ifdef HAVE_NATIVE_mpn_rsh1sub_n
  if (ps == 1)
    mpn_rsh1sub_n (pp, pp, np, n);
  else
#endif
  {
    mpn_sub_n (pp, pp, np, n);
    if (ps > 0)
      mpn_rshift (pp, pp, n, ps);
  }
  if (ns > 0)
    mpn_rshift (np, np, n, ns);
  pp[n] = mpn_add_n (pp+off, pp+off, np, n-off);
  ASSERT_NOCARRY (mpn_add_1(pp+n, np+n-off, off, pp[n]) );
}

static int
abs_sub_add_n (mp_ptr rm, mp_ptr rp, mp_srcptr rs, mp_size_t n) {
  int result;
  result = abs_sub_n (rm, rp, rs, n);
  ASSERT_NOCARRY(mpn_add_n (rp, rp, rs, n));
  return result;
}

static int
mpn_toom_ev_pm1(mp_ptr rp, mp_ptr rm,
		mp_srcptr ap, unsigned int q, mp_size_t n, mp_size_t t,
		mp_ptr ws)
{
  /* {ap,q*n+t} -> {rp,n+1} {rm,n+1} , with {ws, n+1}*/
  ASSERT( n >= t );
  ASSERT( t > 0 );
  ASSERT( q > 2 );
  if( (q & 1) == 0) {
    rp[n] = mpn_add(rp, ap+n*(q-2), n, ap+n*q, t);
    q--;
    ws[n] = mpn_add_n(ws, ap+n*(q-2), ap+n*q, n);
    q-=3;
    rp[n]+= mpn_add_n(rp, rp, ap+n*q, n);
  } else {
    ws[n] = mpn_add(ws, ap+n*(q-2), n, ap+n*q, t);
    q-=3;
    rp[n] = mpn_add_n(rp, ap+n*q, ap+n*(q+2), n);
  }
  while(q) {
    q--;
    ws[n] += mpn_add_n(ws, ws, ap+n*q, n);
    q--;
    rp[n] += mpn_add_n(rp, rp, ap+n*q, n);
  }
  return abs_sub_add_n (rm, rp, ws, n + 1);
}

static int
mpn_toom_ev_rsh(mp_ptr rp, mp_ptr rm,
		mp_srcptr ap, unsigned int q, mp_size_t n, mp_size_t t,
		unsigned int s, mp_ptr ws, mp_ptr scratch)
{
  unsigned int i;
  /* {ap,q*n+t} -> {rp,n+1} {rm,n+1} , with {ws, n+1}*/
  ASSERT( n >= t );
  ASSERT( s != 0 ); /* or _ev_pm1 should be used */
  ASSERT( q > 1 );
  ASSERT( s*q < GMP_NUMB_BITS );
  rp[n] = mpn_lshift(rp, ap, n, s*q);
  ws[n] = mpn_lshift(ws, ap+n, n, s*(q-1));
  if( (q & 1) != 0) {
    ASSERT_NOCARRY(mpn_add(ws,ws,n+1,ap+n*q,t));
    rp[n] += DO_mpn_addlsh_n(rp, ap+n*(q-1), n, s, scratch);
  } else {
    ASSERT_NOCARRY(mpn_add(rp,rp,n+1,ap+n*q,t));
  }
  for(i=2; i<q-1; i++)
  {
    rp[n] += DO_mpn_addlsh_n(rp, ap+n*i, n, s*(q-i), scratch);
    i++;
    ws[n] += DO_mpn_addlsh_n(ws, ap+n*i, n, s*(q-i), scratch);
  };
  return abs_sub_add_n (rm, rp, ws, n + 1);
}


#if GMP_NUMB_BITS < 21
#error Not implemented.
#endif


/* FIXME: tuneup should decide the threshold */
#ifndef MUL_TOOM6H_THRESHOLD
#define MUL_TOOM6H_THRESHOLD 256
#endif

#if TUNE_PROGRAM_BUILD
#define MAYBE_mul_basecase 1
#define MAYBE_mul_toom22   1
#define MAYBE_mul_toom33   1
#define MAYBE_mul_toom6h   1
#else
#define MAYBE_mul_basecase						\
  (MUL_TOOM6H_THRESHOLD < 6 * MUL_TOOM22_THRESHOLD)
#define MAYBE_mul_toom22						\
  (MUL_TOOM6H_THRESHOLD < 6 * MUL_TOOM33_THRESHOLD)
#define MAYBE_mul_toom33						\
  (MUL_TOOM6H_THRESHOLD < 6 * MUL_TOOM44_THRESHOLD)
#define MAYBE_mul_toom6h						\
  (MUL_FFT_THRESHOLD >= 6 * MUL_TOOM6H_THRESHOLD)
#endif

#define TOOM6H_MUL_N_REC(p, a, b, n, ws)				\
  do {									\
    if (MAYBE_mul_basecase						\
	&& BELOW_THRESHOLD (n, MUL_TOOM22_THRESHOLD))			\
      mpn_mul_basecase (p, a, n, b, n);					\
    else if (MAYBE_mul_toom22						\
	     && BELOW_THRESHOLD (n, MUL_TOOM33_THRESHOLD))		\
      mpn_toom22_mul (p, a, n, b, n, ws);				\
    else if (MAYBE_mul_toom33						\
	     && BELOW_THRESHOLD (n, MUL_TOOM44_THRESHOLD))		\
      mpn_toom33_mul (p, a, n, b, n, ws);				\
    else if (! MAYBE_mul_toom6h						\
	     || BELOW_THRESHOLD (n, MUL_TOOM6H_THRESHOLD))		\
      mpn_toom44_mul (p, a, n, b, n, ws);				\
    else								\
      mpn_toom6h_mul (p, a, n, b, n, ws);				\
  } while (0)

#define TOOM6H_MUL_REC(p, a, na, b, nb, ws)		\
  do {	mpn_mul (p, a, na, b, nb);			\
  } while (0)

/* S(n) <= (n+5)\6*10+4+MAX(S((n+5)\6),1+2*(n+5)\6),
   since n>42; S(n) <= ceil(log(n)/log(6))*(10+4)+n*12\6 < n*2 + lg2(n)*6
 */
#define mpn_toom6h_mul_n_itch(n)					\
( ((n) - MUL_TOOM6H_THRESHOLD)*2 +					\
   MAX(MUL_TOOM6H_THRESHOLD*2 + GMP_NUMB_BITS*6,			\
       mpn_toom44_mul_itch(MUL_TOOM6H_THRESHOLD,MUL_TOOM6H_THRESHOLD)) )

mp_size_t
mpn_toom6h_mul_itch (mp_size_t an, mp_size_t bn) {
  mp_size_t estimatedN;
  estimatedN = (an + bn) / (size_t) 10 + 1;
  return mpn_toom6h_mul_n_itch( estimatedN * 6 );
}

/* Toom-6.5 , compute the product {pp,an+bn} <- {ap,an} * {bp,bn}
   With: an >= bn >= 46, an*6 <  bn * 17.
   It _may_ work with bn<=46 and bn*17 < an*6 < bn*18

   Evaluate in: infinity, +4, -4, +2, -2, +1, -1, +1/2, -1/2, +1/4, -1/4, 0.
*/

void
mpn_toom6h_mul   (mp_ptr pp,
		  mp_srcptr ap, mp_size_t an,
		  mp_srcptr bp, mp_size_t bn, mp_ptr scratch)
{
  mp_size_t n, s, t;
  int p, q, half;
  int sign;

  /***************************** decomposition *******************************/

  ASSERT( an >= bn);
  /* Can not handle too much unbalancement */
  ASSERT( bn >= 42 );
  /* Can not handle too much unbalancement */
  ASSERT((an*3 <  bn * 8) || ( bn >= 46 && an*6 <  bn * 17 ));

  /* Limit num/den is a rational number between
     (12/11)^(log(4)/log(2*4-1)) and (12/11)^(log(6)/log(2*6-1))             */
#define LIMIT_numerator (18)
#define LIMIT_denominat (17)

  if( an * LIMIT_denominat < LIMIT_numerator * bn ) /* is 6*... < 6*... */
    { p = q = 6; }
  else if( an * 5 * LIMIT_numerator < LIMIT_denominat * 7 * bn )
    { p = 7; q = 6; }
  else if( an * 5 * LIMIT_denominat < LIMIT_numerator * 7 * bn )
    { p = 7; q = 5; }
  else if( an * LIMIT_numerator < LIMIT_denominat * 2 * bn )  /* is 4*... < 8*... */
    { p = 8; q = 5; }
  else if( an * LIMIT_denominat < LIMIT_numerator * 2 * bn )  /* is 4*... < 8*... */
    { p = 8; q = 4; }
  else 
    { p = 9; q = 4; }

  half = (p ^ q) & 1;
  n = 1 + (q * an >= p * bn ? (an - 1) / (size_t) p : (bn - 1) / (size_t) q);
  p--; q--;

  s = an - p * n;
  t = bn - q * n;

  /* With LIMIT = 16/15, the following recover is needed only if bn<=73*/
  if (half) { /* Recover from badly chosen splitting */
    if (s<1) {p--; s+=n; half=0;}
    else if (t<1) {q--; t+=n; half=0;}
  }
#undef LIMIT_numerator
#undef LIMIT_denominat

  ASSERT (0 < s && s <= n);
  ASSERT (0 < t && t <= n);
  ASSERT (half || s + t > 3);
  ASSERT (n > 2);

#define   r4    (pp + 3 * n)			/* 3n+1 */
#define   r2    (pp + 7 * n)			/* 3n+1 */
#define   r0    (pp +11 * n)			/* s+t <= 2*n */
#define   r5    (scratch)			/* 3n+1 */
#define   r3    (scratch + 3 * n + 1)		/* 3n+1 */
#define   r1    (scratch + 6 * n + 2)		/* 3n+1 */
#define   v0    (pp + 7 * n)			/* n+1 */
#define   v1    (pp + 8 * n+1)			/* n+1 */
#define   v2    (pp + 9 * n+2)			/* n+1 */
#define   v3    (scratch + 9 * n + 3)		/* n+1 */
#define   wsi   (scratch + 9 * n + 3)		/* 3n+1 */
#define   wse   (scratch +10 * n + 4)		/* 2n+1 */

  /* Alloc also 3n+1 limbs for wsi... toom_interpolate_12pts may
     need all of them  */
/*   if (scratch == NULL) */
/*     scratch = TMP_SALLOC_LIMBS(mpn_toom6h_mul_n_itch(n * 6)); */
  ASSERT (12 * n + 6 <= mpn_toom6h_mul_itch(an,bn));
  ASSERT (12 * n + 6 <= mpn_toom6h_mul_n_itch(n * 6));

  /********************** evaluation and recursive calls *********************/
  /* $\pm1/2$ */
  sign = mpn_toom_ev_rsh (v2, v0, ap, p, n, s, 1, pp, wse) ^
	 mpn_toom_ev_rsh (v3, v1, bp, q, n, t, 1, pp, wse);
  TOOM6H_MUL_N_REC(pp, v0, v1, n + 1, wse); /* A(-1/2)*B(-1/2)*2^. */
  TOOM6H_MUL_N_REC(r5, v2, v3, n + 1, wse); /* A(+1/2)*B(+1/2)*2^. */
  toom_couple_handling(r5, 2 * n + 1, pp, sign, n, 1+half , half);

  /* $\pm1$ */
  sign = mpn_toom_eval_pm1 (v2, v0, p, ap, n, s,    pp);
  if (q == 3)
    sign ^= mpn_toom_eval_dgr3_pm1 (v3, v1, bp, n, t,    pp);
  else
    sign ^= mpn_toom_eval_pm1 (v3, v1, q, bp, n, t,    pp);
  TOOM6H_MUL_N_REC(pp, v0, v1, n + 1, wse); /* A(-1)*B(-1) */
  TOOM6H_MUL_N_REC(r3, v2, v3, n + 1, wse); /* A(1)*B(1) */
  toom_couple_handling(r3, 2 * n + 1, pp, sign, n, 0, 0);

  /* $\pm4$ */
  sign = mpn_toom_eval_pm2exp (v2, v0, p, ap, n, s, 2, pp) ^
	 mpn_toom_eval_pm2exp (v3, v1, q, bp, n, t, 2, pp);
  TOOM6H_MUL_N_REC(pp, v0, v1, n + 1, wse); /* A(-4)*B(-4) */
  TOOM6H_MUL_N_REC(r1, v2, v3, n + 1, wse); /* A(+4)*B(+4) */
  toom_couple_handling(r1, 2 * n + 1, pp, sign, n, 2, 4);

  /* $\pm1/4$ */
  sign = mpn_toom_ev_rsh (v2, v0, ap, p, n, s, 2, pp, wse) ^
	 mpn_toom_ev_rsh (v3, v1, bp, q, n, t, 2, pp, wse);
  TOOM6H_MUL_N_REC(pp, v0, v1, n + 1, wse); /* A(-1/4)*B(-1/4)*4^. */
  TOOM6H_MUL_N_REC(r4, v2, v3, n + 1, wse); /* A(+1/4)*B(+1/4)*4^. */
  toom_couple_handling(r4, 2 * n + 1, pp, sign, n, 2*(1+half), 2*(half));

  /* $\pm2$ */
  sign = mpn_toom_eval_pm2 (v2, v0, p, ap, n, s, pp) ^
	 mpn_toom_eval_pm2 (v3, v1, q, bp, n, t, pp);
  TOOM6H_MUL_N_REC(pp, v0, v1, n + 1, wse); /* A(-2)*B(-2) */
  TOOM6H_MUL_N_REC(r2, v2, v3, n + 1, wse); /* A(+2)*B(+2) */
  toom_couple_handling(r2, 2 * n + 1, pp, sign, n, 1, 2);

#undef v0
#undef v1
#undef v2
#undef v3
#undef wse

  /* A(0)*B(0) */
  TOOM6H_MUL_N_REC(pp, ap, bp, n, wsi);

  /* Infinity */
  if( half != 0) { 
    if(s>t) {
      TOOM6H_MUL_REC(r0, ap + p * n, s, bp + q * n, t, wsi);
    } else {
      TOOM6H_MUL_REC(r0, bp + q * n, t, ap + p * n, s, wsi);
    };
  };

  toom_interpolate_12pts (pp, r1, r3, r5, n, s+t, half, wsi);

#undef r0
#undef r1
#undef r2
#undef r3
#undef r4
#undef r5
#undef wsi
}

#undef TOOM6H_MUL_N_REC
#undef TOOM6H_MUL_REC
#undef MAYBE_mul_basecase
#undef MAYBE_mul_toom22
#undef MAYBE_mul_toom33
#undef MAYBE_mul_toom6h



#ifndef SQR_TOOM6_THRESHOLD
#define SQR_TOOM6_THRESHOLD MUL_TOOM6H_THRESHOLD
#endif

#ifdef  SQR_TOOM8_THRESHOLD
#define SQR_TOOM6_MAX (SQR_TOOM8_THRESHOLD+6*2-1)
#else
#define SQR_TOOM6_MAX (SQR_FFT_THRESHOLD+6*2-1)
#endif

#if TUNE_PROGRAM_BUILD
#define MAYBE_sqr_basecase 1
#define MAYBE_sqr_above_basecase   1
#define MAYBE_sqr_toom2   1
#define MAYBE_sqr_above_toom2   1
#define MAYBE_sqr_toom3   1
#define MAYBE_sqr_above_toom3   1
#define MAYBE_sqr_above_toom4   1
#else
#define MAYBE_sqr_basecase					\
  (SQR_TOOM6_THRESHOLD < 6 * SQR_TOOM2_THRESHOLD)
#define MAYBE_sqr_above_basecase				\
  (SQR_TOOM6_MAX >= 6 * SQR_TOOM2_THRESHOLD)
#define MAYBE_sqr_toom2						\
  (SQR_TOOM6_THRESHOLD < 6 * SQR_TOOM3_THRESHOLD)
#define MAYBE_sqr_above_toom2					\
  (SQR_TOOM6_MAX >= 6 * SQR_TOOM3_THRESHOLD)
#define MAYBE_sqr_toom3						\
  (SQR_TOOM6_THRESHOLD < 6 * SQR_TOOM4_THRESHOLD)
#define MAYBE_sqr_above_toom3					\
  (SQR_TOOM6_MAX >= 6 * SQR_TOOM4_THRESHOLD)
#define MAYBE_sqr_above_toom4					\
  (SQR_TOOM6_MAX >= 6 * SQR_TOOM6_THRESHOLD)
#endif

#define TOOM6_SQR_REC(p, a, n, ws)					\
  do {									\
    if (MAYBE_sqr_basecase && ( !MAYBE_sqr_above_basecase		\
	|| BELOW_THRESHOLD (n, SQR_TOOM2_THRESHOLD)))			\
      mpn_sqr_basecase (p, a, n);					\
    else if (MAYBE_sqr_toom2 && ( !MAYBE_sqr_above_toom2		\
	     || BELOW_THRESHOLD (n, SQR_TOOM3_THRESHOLD)))		\
      mpn_toom2_sqr (p, a, n, ws);					\
    else if (MAYBE_sqr_toom3 && ( !MAYBE_sqr_above_toom3		\
	     || BELOW_THRESHOLD (n, SQR_TOOM4_THRESHOLD)))		\
      mpn_toom3_sqr (p, a, n, ws);					\
    else if (! MAYBE_sqr_above_toom4					\
	     || BELOW_THRESHOLD (n, SQR_TOOM6_THRESHOLD))		\
      mpn_toom4_sqr (p, a, n, ws);					\
    else								\
      mpn_toom6_sqr (p, a, n, ws);					\
  } while (0)

void
mpn_toom6_sqr  (mp_ptr pp, mp_srcptr ap, mp_size_t an, mp_ptr scratch)
{
  mp_size_t n, s;

  /***************************** decomposition *******************************/

  ASSERT( an >= 18 );

  n = 1 + (an - 1) / (size_t) 6;

  s = an - 5 * n;

  ASSERT (0 < s && s <= n);

#define   r4    (pp + 3 * n)			/* 3n+1 */
#define   r2    (pp + 7 * n)			/* 3n+1 */
#define   r0    (pp +11 * n)			/* s+t <= 2*n */
#define   r5    (scratch)			/* 3n+1 */
#define   r3    (scratch + 3 * n + 1)		/* 3n+1 */
#define   r1    (scratch + 6 * n + 2)		/* 3n+1 */
#define   v0    (pp + 7 * n)			/* n+1 */
#define   v2    (pp + 9 * n+2)			/* n+1 */
#define   wse   (scratch + 9 * n + 3)		/* 3n+1 */

  /* Alloc also 3n+1 limbs for ws... toom_interpolate_12pts may
     need all of them, when DO_mpn_sublsh_n usea a scratch  */
/*   if (scratch== NULL) */
/*     scratch = TMP_SALLOC_LIMBS (12 * n + 6); */

  /********************** evaluation and recursive calls *********************/
  /* $\pm1/2$ */
  mpn_toom_ev_rsh (v2, v0, ap, 5, n, s, 1, pp, wse);
  TOOM6_SQR_REC(pp, v0, n + 1, wse); /* A(-1/2)*B(-1/2)*2^. */
  TOOM6_SQR_REC(r5, v2, n + 1, wse); /* A(+1/2)*B(+1/2)*2^. */
  toom_couple_handling(r5, 2 * n + 1, pp, 0, n, 1, 0);

  /* $\pm1$ */
  mpn_toom_eval_pm1 (v2, v0, 5, ap, n, s,    pp);
  TOOM6_SQR_REC(pp, v0, n + 1, wse); /* A(-1)*B(-1) */
  TOOM6_SQR_REC(r3, v2, n + 1, wse); /* A(1)*B(1) */
  toom_couple_handling(r3, 2 * n + 1, pp, 0, n, 0, 0);

  /* $\pm4$ */
  mpn_toom_eval_pm2exp (v2, v0, 5, ap, n, s, 2, pp);
  TOOM6_SQR_REC(pp, v0, n + 1, wse); /* A(-4)*B(-4) */
  TOOM6_SQR_REC(r1, v2, n + 1, wse); /* A(+4)*B(+4) */
  toom_couple_handling(r1, 2 * n + 1, pp, 0, n, 2, 4);

  /* $\pm1/4$ */
  mpn_toom_ev_rsh (v2, v0, ap, 5, n, s, 2, pp, wse);
  TOOM6_SQR_REC(pp, v0, n + 1, wse); /* A(-1/4)*B(-1/4)*4^. */
  TOOM6_SQR_REC(r4, v2, n + 1, wse); /* A(+1/4)*B(+1/4)*4^. */
  toom_couple_handling(r4, 2 * n + 1, pp, 0, n, 2, 0);

  /* $\pm2$ */
  mpn_toom_eval_pm2 (v2, v0, 5, ap, n, s, pp);
  TOOM6_SQR_REC(pp, v0, n + 1, wse); /* A(-2)*B(-2) */
  TOOM6_SQR_REC(r2, v2, n + 1, wse); /* A(+2)*B(+2) */
  toom_couple_handling(r2, 2 * n + 1, pp, 0, n, 1, 2);

#undef v0
#undef v2

  /* A(0)*B(0) */
  TOOM6_SQR_REC(pp, ap, n, wse);

  toom_interpolate_12pts (pp, r1, r3, r5, n, 2 * s, 0, wse);

#undef r0
#undef r1
#undef r2
#undef r3
#undef r4
#undef r5

}
#undef TOOM6_SQR_REC
#undef MAYBE_sqr_basecase
#undef MAYBE_sqr_above_basecase
#undef MAYBE_sqr_toom2
#undef MAYBE_sqr_above_toom2
#undef MAYBE_sqr_toom3
#undef MAYBE_sqr_above_toom3
#undef MAYBE_sqr_above_toom4
