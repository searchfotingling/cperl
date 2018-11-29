/* ex: set ro ft=c: -*- mode: c; buffer-read-only: t -*-
   !!!!!!!   DO NOT EDIT THIS FILE   !!!!!!!
   This file is built by regen/feature.pl.
   Any changes made here will be lost!
 */


#ifndef PERL_FEATURE_H_
#define PERL_FEATURE_H_

#if defined(PERL_CORE) || defined (PERL_EXT)

#define HINT_FEATURE_SHIFT	26

#define FEATURE_BUNDLE_DEFAULT	0
#define FEATURE_BUNDLE_510	1
#define FEATURE_BUNDLE_511	2
#define FEATURE_BUNDLE_515	3
#define FEATURE_BUNDLE_523	4
#define FEATURE_BUNDLE_527	5
#define FEATURE_BUNDLE_CUSTOM	(HINT_FEATURE_MASK >> HINT_FEATURE_SHIFT)

#define CURRENT_HINTS \
    (PL_curcop == &PL_compiling ? PL_hints : PL_curcop->cop_hints)
#define CURRENT_FEATURE_BUNDLE \
    ((CURRENT_HINTS & HINT_FEATURE_MASK) >> HINT_FEATURE_SHIFT)

/* Avoid using ... && Perl_feature_is_enabled(...) as that triggers a bug in
   the HP-UX cc on PA-RISC */
#define FEATURE_IS_ENABLED(name)				        \
	((CURRENT_HINTS & HINT_LOCALIZE_HH)				\
	    ? Perl_feature_is_enabled(aTHX_ STR_WITH_LEN(name)) : FALSE)
/* The longest string we pass in.  */
#define MAX_FEATURE_LEN (sizeof("shaped_arrays")-1)

#ifdef USE_CPERL
#define FEATURE_FC_IS_ENABLED 1
#else
#define FEATURE_FC_IS_ENABLED \
    ( \
	CURRENT_FEATURE_BUNDLE == FEATURE_BUNDLE_CUSTOM && \
	 FEATURE_IS_ENABLED("fc") \
    )
#endif

#define FEATURE_SAY_IS_ENABLED \
    ( \
	(CURRENT_FEATURE_BUNDLE >= FEATURE_BUNDLE_510 && \
	 CURRENT_FEATURE_BUNDLE <= FEATURE_BUNDLE_527) \
     || (CURRENT_FEATURE_BUNDLE == FEATURE_BUNDLE_CUSTOM && \
	 FEATURE_IS_ENABLED("say")) \
    )

#define FEATURE_STATE_IS_ENABLED \
    ( \
	(CURRENT_FEATURE_BUNDLE >= FEATURE_BUNDLE_510 && \
	 CURRENT_FEATURE_BUNDLE <= FEATURE_BUNDLE_527) \
     || (CURRENT_FEATURE_BUNDLE == FEATURE_BUNDLE_CUSTOM && \
	 FEATURE_IS_ENABLED("state")) \
    )

#define FEATURE_SWITCH_IS_ENABLED \
    ( \
	(CURRENT_FEATURE_BUNDLE >= FEATURE_BUNDLE_510 && \
	 CURRENT_FEATURE_BUNDLE <= FEATURE_BUNDLE_527) \
     || (CURRENT_FEATURE_BUNDLE == FEATURE_BUNDLE_CUSTOM && \
	 FEATURE_IS_ENABLED("switch")) \
    )

#define FEATURE_BITWISE_IS_ENABLED \
    ( \
	CURRENT_FEATURE_BUNDLE == FEATURE_BUNDLE_527 \
     || (CURRENT_FEATURE_BUNDLE == FEATURE_BUNDLE_CUSTOM && \
	 FEATURE_IS_ENABLED("bitwise")) \
    )

#define FEATURE_EVALBYTES_IS_ENABLED \
    ( \
	(CURRENT_FEATURE_BUNDLE >= FEATURE_BUNDLE_515 && \
	 CURRENT_FEATURE_BUNDLE <= FEATURE_BUNDLE_527) \
     || (CURRENT_FEATURE_BUNDLE == FEATURE_BUNDLE_CUSTOM && \
	 FEATURE_IS_ENABLED("evalbytes")) \
    )

#ifdef USE_CPERL
#define FEATURE_SIGNATURES_IS_ENABLED 1
#else
#define FEATURE_SIGNATURES_IS_ENABLED \
    ( \
	CURRENT_FEATURE_BUNDLE == FEATURE_BUNDLE_CUSTOM && \
	 FEATURE_IS_ENABLED("signatures") \
    )
#endif

#define FEATURE___SUB___IS_ENABLED \
    ( \
	(CURRENT_FEATURE_BUNDLE >= FEATURE_BUNDLE_515 && \
	 CURRENT_FEATURE_BUNDLE <= FEATURE_BUNDLE_523) \
     || (CURRENT_FEATURE_BUNDLE == FEATURE_BUNDLE_CUSTOM && \
	 FEATURE_IS_ENABLED("__SUB__")) \
    )

#define FEATURE_REFALIASING_IS_ENABLED \
    ( \
	CURRENT_FEATURE_BUNDLE == FEATURE_BUNDLE_CUSTOM && \
	 FEATURE_IS_ENABLED("refaliasing") \
    )

#define FEATURE_POSTDEREF_QQ_IS_ENABLED \
    ( \
	(CURRENT_FEATURE_BUNDLE >= FEATURE_BUNDLE_523 && \
	 CURRENT_FEATURE_BUNDLE <= FEATURE_BUNDLE_527) \
     || (CURRENT_FEATURE_BUNDLE == FEATURE_BUNDLE_CUSTOM && \
	 FEATURE_IS_ENABLED("postderef_qq")) \
    )

#define FEATURE_UNIEVAL_IS_ENABLED \
    ( \
	(CURRENT_FEATURE_BUNDLE >= FEATURE_BUNDLE_515 && \
	 CURRENT_FEATURE_BUNDLE <= FEATURE_BUNDLE_527) \
     || (CURRENT_FEATURE_BUNDLE == FEATURE_BUNDLE_CUSTOM && \
	 FEATURE_IS_ENABLED("unieval")) \
    )

#define FEATURE_MYREF_IS_ENABLED \
    ( \
	CURRENT_FEATURE_BUNDLE == FEATURE_BUNDLE_CUSTOM && \
	 FEATURE_IS_ENABLED("myref") \
    )

#ifdef USE_CPERL
#define FEATURE_SHAPED_ARRAYS_IS_ENABLED 1
#else
#define FEATURE_SHAPED_ARRAYS_IS_ENABLED \
    ( \
	CURRENT_FEATURE_BUNDLE == FEATURE_BUNDLE_CUSTOM && \
	 FEATURE_IS_ENABLED("shaped_arrays") \
    )
#endif

#define FEATURE_UNICODE_IS_ENABLED \
    ( \
	(CURRENT_FEATURE_BUNDLE >= FEATURE_BUNDLE_511 && \
	 CURRENT_FEATURE_BUNDLE <= FEATURE_BUNDLE_527) \
     || (CURRENT_FEATURE_BUNDLE == FEATURE_BUNDLE_CUSTOM && \
	 FEATURE_IS_ENABLED("unicode")) \
    )


#endif /* PERL_CORE or PERL_EXT */

#ifdef PERL_IN_OP_C
PERL_STATIC_INLINE void
S_enable_feature_bundle(pTHX_ SV *ver)
{
    SV *comp_ver = sv_newmortal();
    PL_hints = (PL_hints &~ HINT_FEATURE_MASK)
	     | (
		  (sv_setnv(comp_ver, 5.027),
		   vcmp(ver, upg_version(comp_ver, FALSE)) >= 0)
			? FEATURE_BUNDLE_527 :
		  (sv_setnv(comp_ver, 5.023),
		   vcmp(ver, upg_version(comp_ver, FALSE)) >= 0)
			? FEATURE_BUNDLE_523 :
		  (sv_setnv(comp_ver, 5.015),
		   vcmp(ver, upg_version(comp_ver, FALSE)) >= 0)
			? FEATURE_BUNDLE_515 :
		  (sv_setnv(comp_ver, 5.011),
		   vcmp(ver, upg_version(comp_ver, FALSE)) >= 0)
			? FEATURE_BUNDLE_511 :
		  (sv_setnv(comp_ver, 5.009005),
		   vcmp(ver, upg_version(comp_ver, FALSE)) >= 0)
			? FEATURE_BUNDLE_510 :
			  FEATURE_BUNDLE_DEFAULT
	       ) << HINT_FEATURE_SHIFT;
    /* special case */
    assert(PL_curcop == &PL_compiling);
    if (FEATURE_UNICODE_IS_ENABLED) PL_hints |=  HINT_UNI_8_BIT;
    else			    PL_hints &= ~HINT_UNI_8_BIT;
}
#endif /* PERL_IN_OP_C */

#endif /* PERL_FEATURE_H_ */

/* ex: set ro: */
