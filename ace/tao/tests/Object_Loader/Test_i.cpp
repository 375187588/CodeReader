// Test_i.cpp,v 1.3 2001/05/20 15:46:58 bala Exp

#include "Test_i.h"

#if !defined(__ACE_INLINE__)
#include "Test_i.i"
#endif /* __ACE_INLINE__ */

ACE_RCSID(Object_Loader, Test_i, "Test_i.cpp,v 1.3 2001/05/20 15:46:58 bala Exp")

CORBA::Long
Test_i::instance_count_ = 0;

Test_i::Test_i (PortableServer::POA_ptr poa)
  :  poa_ (PortableServer::POA::_duplicate (poa))
{
  Test_i::instance_count_++;
}

CORBA::Long
Test_i::instance_count (CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  return Test_i::instance_count_;
}

void
Test_i::destroy (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  PortableServer::POA_var poa =
    this->_default_POA (ACE_TRY_ENV);
  ACE_CHECK;
  PortableServer::ObjectId_var oid =
    poa->servant_to_id (this, ACE_TRY_ENV);
  ACE_CHECK;
  poa->deactivate_object (oid.in (), ACE_TRY_ENV);
  ACE_CHECK;
}

PortableServer::POA_ptr
Test_i::_default_POA (CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  return PortableServer::POA::_duplicate (this->poa_.in ());
}
