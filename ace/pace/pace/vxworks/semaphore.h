/* semaphore.h,v 1.1 2001/06/01 20:56:51 joeh Exp

 * ============================================================================
 *
 * = LIBRARY
 *    pace
 *
 * = FILENAME
 *    pace/vxworks/semaphore.h
 *
 * = AUTHOR
 *    Joe Hoffert
 *
 * ============================================================================ */

#ifndef PACE_SEMAPHORE_H_VXWORKS
#define PACE_SEMAPHORE_H_VXWORKS

#include <semaphore.h>

#if defined (PACE_HAS_CPLUSPLUS)
extern "C" {
#endif /* PACE_HAS_CPLUSPLUS */

typedef sem_t pace_sem_t;

#if defined (PACE_HAS_CPLUSPLUS)
}
#endif /* PACE_HAS_CPLUSPLUS */

#endif /* PACE_SEMAPHORE_H_VXWORKS */
