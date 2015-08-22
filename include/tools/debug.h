// (c) 1992 Allen I. Holub
#line 111 "0.tr"
#ifndef __DEBUG_H
#define __DEBUG_H

#ifdef  DEBUG
#define PRIVATE
#define D(x) x			/* expand only when debugging     */
#define ND(x)			/* expand only when not debugging */
#else
#define PRIVATE static
#define D(x)
#define ND(x) x
#endif
#define PUBLIC

/*
 * NUMELE(array)	Evaluates to the array size in elements
 * LASTELE(array)	Evaluates to a pointer to the last element
 * INBOUNDS(array,p)    Evaluates to true if p points into the array.
 * RANGE(a,b,c)		Evaluates to true if a <= b <= c max(a,b)
 * valuates to a or b, whichever is larger min(a,b)		Evaluates to
 * a or b, whichever is smaller associated with a pointer NBITS(type)
 * eturns number of bits in a variable of the indicated type; MAXINT
 * valuates to the value of the largest signed integer
 */

#define NUMELE(a)	(sizeof(a)/sizeof(*(a)))
#define LASTELE(a)	((a) + (NUMELE(a)-1))
#define TOOHIGH(a,p)	((p) - (a) > (NUMELE(a) - 1))
#define TOOLOW(a,p)	((p) - (a) <  0 )
#define INBOUNDS(a,p)	( ! (TOOHIGH(a,p) || TOOLOW(a,p)) )

/*
 * Portability note: Some systems won't allow UL for unsined long in the _IS
 * macro. You can use the following if so:
 * 
 * (unsigned long)1
 * 
 * Bob Muller, who suggested the foregoing, also reports: "There also seems to
 * be an issue with the notion of shifting; the DEC Ultrix compiler, for
 * example, says that (unsigned long)((unsigned long)1 << 32) == 1, while the
 * Sun SunOS 4 compiler says that it is 0."
 */

#define _IS(t,x) ( ((t)(1UL << (x))) !=0)
/* Evaluate true if the width of a      */
/* variable of type of t is < x. The != */
/* 0 assures that the answer is 1 or 0  */

#define NBITS(t) (4 * (1  + _IS(t, 4) + _IS(t, 8) + _IS(t,12) + _IS(t,16) \
		          + _IS(t,20) + _IS(t,24) + _IS(t,28) + _IS(t,32) ) )

#define MAXINT (((unsigned)~0) >> 1)

#ifndef max
#define max(a,b) ( ((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a,b) ( ((a) < (b)) ? (a) : (b))
#endif

#define RANGE(a,b,c)	( (a) <= (b) && (b) <= (c) )

/*
 * The distribution disk doesn't include dmalloc.h, so don't define
 * MAP_MALLOC anywhere.
 */
#ifdef MAP_MALLOC
#include <tools/dmalloc.h>
#endif

#endif				/* #ifdef __DEBUG_H */
