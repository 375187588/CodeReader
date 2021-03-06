// ami_test_i.h,v 1.4 2000/05/11 14:03:53 mk1 Exp

// ============================================================================
//
// = LIBRARY
//   TAO/tests/AMI
//
// = FILENAME
//   ami_test_i.h
//
// = AUTHOR
//   Michael Kircher <Michael.Kircher@mchp.siemens.de>
//
// ============================================================================

#ifndef TAO_AMI_TEST_I_H
#define TAO_AMI_TEST_I_H

#ifdef TAO_HAS_AMI_EXCEPTIONS
#include "ami_testS-hand.h"
#else
#include "ami_testS.h"
#endif

class AMI_Test_i : public POA_A::AMI_Test
{
  // = TITLE
  //   AMI Test implementation
  //
  // = DESCRIPTION
  //   Implements the AMI_Test interface in test.idl
  //
public:
  AMI_Test_i (CORBA::ORB_ptr orb);
  // ctor

  // The AMI_Test methods.
  CORBA::Long foo (CORBA::Long_out out_l,
                   CORBA::Long in_l,
                   const char* in_str,
                   CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     A::DidTheRightThing));
  
  void shutdown (CORBA::Environment&)
    ACE_THROW_SPEC ((CORBA::SystemException));

  CORBA::Long yadda (CORBA::Environment &ACE_TRY_ENV)
      ACE_THROW_SPEC ((CORBA::SystemException));

  void yadda (CORBA::Long yadda,
              CORBA::Environment &ACE_TRY_ENV)
      ACE_THROW_SPEC ((CORBA::SystemException));

private:
  CORBA::ORB_var orb_;

  CORBA::Long number_;

  CORBA::Long yadda_;
};


#endif /* TAO_AMI_TEST_I_H */
