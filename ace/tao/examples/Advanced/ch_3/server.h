// server.h,v 1.2 1999/08/30 17:31:12 schmidt Exp

// ============================================================================
//
// = LIBRARY
//    TAO/examples/Advanced/ch_3
//
// = FILENAME
//    server.h
//
// = AUTHORS
//   Source code used in TAO has been modified and adapted from the code
//   provided in the book, "Advanced CORBA Programming with C++" by Michi
//   Henning and Steve Vinoski. Copyright 1999. Addison-Wesley, Reading,
//   MA.  Used with permission of Addison-Wesley.
//
//   Modified for TAO by Mike Moran <mm4@cs.wustl.edu>
//
// ============================================================================

#ifndef server_HH_
#define server_HH_

#include "timeS.h"

class Time_impl : public virtual POA_Time 
{ 
public:
  virtual TimeOfDay get_gmt (void) throw (CORBA::SystemException);
};

#endif /* server_HH_ */
