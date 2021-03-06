/* -*- C++ -*- */
// Today.h,v 1.4 1998/11/27 16:58:03 schmidt Exp

// ===========================================================
//
// = LIBRARY
//    ACE_wrappers/examples/DLL
//
// = FILENAME
//    Today.h
//
// = DESCRIPTION
//    This class denotes the Today magazine which is derived from 
//    Magazine.
//
// = AUTHOR
//    Kirthika Parameswaran <kirthika@cs.wustl.edu>
//
// ===========================================================

#ifndef TODAY_H
#define TODAY_H

#include "ace/OS.h"
#include "Magazine.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

class Today : public Magazine
{
  // = TITLE 
  //   This is an derived class of Magazine.
  // 
  // = DESCRIPTION
  //   Polymoriphism is exploited and an object pointer of Magazine 
  //   is bound to the Today object at runtime.
public:

  void title (void);
  // The virtual abstract class method which returns the title of the
  // magazine.
};

#endif /* TODAY_H */
