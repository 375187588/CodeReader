// -*- C++ -*-

#include "test_i.h"

ACE_RCSID (IORInterceptors,
           test_i,
           "test_i.cpp,v 1.1 2000/12/26 19:18:55 othman Exp")

test_i::test_i (CORBA::ORB_ptr orb)
  : orb_ (CORBA::ORB::_duplicate (orb))
{
}

void
test_i::shutdown (CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  ACE_DEBUG ((LM_DEBUG,
              "\"test_i\" is shutting down.\n"));
  this->orb_->shutdown (0, ACE_TRY_ENV);
}
