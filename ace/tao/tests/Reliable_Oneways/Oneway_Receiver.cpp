//
// Oneway_Receiver.cpp,v 1.1 2001/04/10 18:06:57 coryan Exp
//
#include "Oneway_Receiver.h"
#include "Shutdown_Helper.h"

ACE_RCSID(Reliable_Oneways, Oneway_Receiver, "Oneway_Receiver.cpp,v 1.1 2001/04/10 18:06:57 coryan Exp")

Oneway_Receiver::Oneway_Receiver (CORBA::ORB_ptr orb)
  : orb_ (CORBA::ORB::_duplicate (orb))
{
}

void
Oneway_Receiver::raise_no_permission (CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  ACE_THROW (CORBA::NO_PERMISSION ());
}

void
Oneway_Receiver::destroy (CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  PortableServer::POA_var poa = this->_default_POA (ACE_TRY_ENV);
  ACE_CHECK;

  PortableServer::ObjectId_var id =
    poa->servant_to_id (this, ACE_TRY_ENV);
  ACE_CHECK;

  poa->deactivate_object (id.in (), ACE_TRY_ENV);
  ACE_CHECK;
}

Test::Shutdown_Helper_ptr
Oneway_Receiver::get_shutdown_helper (CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  Shutdown_Helper *shutdown_helper;
  ACE_NEW_THROW_EX (shutdown_helper,
                    Shutdown_Helper (this->orb_.in ()),
                    CORBA::NO_MEMORY ());
  ACE_CHECK_RETURN (Test::Shutdown_Helper::_nil ());

  PortableServer::ServantBase_var transfer_ownership(shutdown_helper);

  return shutdown_helper->_this (ACE_TRY_ENV);
}
