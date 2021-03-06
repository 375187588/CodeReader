// test_i.h,v 1.1 2000/09/17 12:17:15 bala Exp

// ============================================================================
//
// = LIBRARY
//   TAO/orbsvcs/tests/FaultTolerance/IOGR
//
// = FILENAME
//   test_i.h
//
// = AUTHOR
//   Bala Natarajan <bala@cs.wustl.edu>
//
// ============================================================================

#ifndef TAO_FT_IOGR_TEST_I_H
#define TAO_FT_IOGR_TEST_I_H

#include "testS.h"

class Simple_Server_i : public POA_Simple_Server
{
  // = TITLE
  //   Simpler Server implementation
  //
  // = DESCRIPTION
  //   Implements the Simple_Server interface in test.idl
  //
public:
  Simple_Server_i (CORBA::ORB_ptr orb);
  // ctor

  Simple_Server_i (void);
  // ctor

  // = The Simple_Server methods.
  void remote_call (CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException));

  void shutdown (CORBA::Environment&)
    ACE_THROW_SPEC ((CORBA::SystemException));

private:
  CORBA::ORB_var orb_;
};

#endif /* TAO_FT_IOGR_TEST_I_H */
