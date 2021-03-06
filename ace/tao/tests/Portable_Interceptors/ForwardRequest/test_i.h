// -*- C++ -*-

//=============================================================================
/**
 * @file test_i.h
 *
 * test_i.h,v 1.2 2001/03/01 18:11:52 othman Exp
 *
 * Implementation header for the "test" IDL interface for the
 * PortableInterceptor::ForwardRequest test.
 *
 * @author Ossama Othman <ossama@uci.edu>
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
class test_i : public virtual POA_ForwardRequestTest::test
{
public:

  /// Constructor.
  test_i (CORBA::Short num,
          CORBA::ORB_ptr orb);

  /// Destructor.
  ~test_i (void);

  /// Return the number assigned to this object.
  virtual CORBA::Short number (CORBA::Environment &ACE_TRY_ENV =
                                 TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  /// Shutdown the ORB.
  virtual void shutdown (CORBA::Environment &ACE_TRY_ENV =
                           TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

private:

  /// The number assigned to this object.
  CORBA::Short number_;

  /// Pseudo-reference to the ORB.
  CORBA::ORB_var orb_;

};

#endif  /* TEST_I_H */
