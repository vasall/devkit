#ifndef VASALL_DEVKIT_HELPER_H
#define VASALL_DEVKIT_HELPER_H

/******************************************************************************
 * 
 * 				 DEFINES/MACROS
 *
 ******************************************************************************/

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define CLAMP(v, lo, hi) MAX((lo), MIN((v), (hi)))

/*
 * Round v to exactly 0 if it is closer to 0 than eps, e.g. to remove float
 * error like sinf(pi) being about -8.7e-8 instead of 0. Note that v is
 * evaluated up to three times, so pass a variable, not a function call.
 */
#define SNAP_ZERO(v, eps) ((((v) > -(eps)) && ((v) < (eps))) ? 0 : (v))

/******************************************************************************
 * 
 * 				   STRUCTURES 
 *
 ******************************************************************************/

/******************************************************************************
 * 
 * 				PUBLIC INTERFACE
 *
 ******************************************************************************/

#endif /* VASALL_DEVKIT_HELPER_H */

