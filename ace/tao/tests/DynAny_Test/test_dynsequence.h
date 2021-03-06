// -*- c++ -*-
// test_dynsequence.h,v 1.3 1999/06/06 19:01:19 parsons Exp
// ============================================================================
//
// = LIBRARY
//    TAO/tests/DynAny_Test
//
// = FILENAME
//    test_dynsequence.h
//
// = DESCRIPTION
//    Header file for class to test DynSequence.
//
// = AUTHOR
//    Jeff Parsons <parsons@cs.wustl.edu>
//
// ============================================================================

#if !defined (TEST_DYNSEQUENCE_H)
#define TEST_DYNSEQUENCE_H

#include "tao/corba.h"

class Test_DynSequence
{
public:
  Test_DynSequence (CORBA::ORB_var orb);
  ~Test_DynSequence (void);

  const char* test_name (void) const;

  int run_test (void);

private:
  CORBA::ORB_var orb_;
  char* test_name_;
  CORBA::ULong error_count_;
};

#endif /* TEST_DYNSEQUENCE_H */

