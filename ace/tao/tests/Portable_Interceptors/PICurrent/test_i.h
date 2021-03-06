// -*- C++ -*-

//=============================================================================
/**
 * @file    test_i.h
 *
 * test_i.h,v 1.1 2001/09/24 08:31:39 othman Exp
 *
 * Implementation header for the "test" IDL interface for the
 * PortableInterceptor::Current test.
 *
 * @author  Ossama Othman <ossama@uci.edu>
 */
//=============================================================================

#ifndef TEST_I_H
#define TEST_I_H

#include "testS.h"

/**
 * @class test_i
 *
 * @brief Simple test class.
 *
 * This class implements the "test" interface used in this test.
 */
class test_i : public virtual POA_PICurrentTest::test
{
public:

  /// Constructor.
  test_i (PortableInterceptor::Current_ptr current,
          PortableInterceptor::SlotId id,
          CORBA::ORB_ptr orb);

  /// Destructor.
  ~test_i (void);

  /// Return the number assigned to this object.
  virtual void invoke_me (CORBA::Environment &ACE_TRY_ENV =
                            TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  /// Shutdown the ORB.
  virtual void shutdown (CORBA::Environment &ACE_TRY_ENV =
                           TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

private:

  /// Reference to the PICurrent object.
  PortableInterceptor::Current_var current_;

  /// SlotId in the PICurrent object assigned to this test.
  PortableInterceptor::SlotId slot_id_;

  /// Pseudo-reference to the ORB.
  CORBA::ORB_var orb_;

};

#endif  /* TEST_I_H */
