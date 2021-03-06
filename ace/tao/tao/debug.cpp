// debug.cpp,v 1.25 2001/03/26 21:17:08 coryan Exp
// @ (#)debug.cpp       1.3 95/10/02

// Copyright 1994-1995 by Sun Microsystems Inc.
// All Rights Reserved
//
// ORB:         Simple debug/trace support
//
// THREADING NOTE: the global values here  (debug_{level,filter,stream)
// are assumed to be modified "safely", e.g. in the main thread as
// part of process initialization.  They are treated as immutable
// values through all of this debuging package.
//
// XXX on Windows, make it always use OutputDebugString () instead of stdio.

#include "tao/debug.h"

ACE_RCSID(tao, debug, "debug.cpp,v 1.25 2001/03/26 21:17:08 coryan Exp")

TAO_Export u_int TAO_debug_level = 0;
