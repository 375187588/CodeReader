// -*- C++ -*-
//=============================================================================
/**
 *  @file   Adapter_Activator.h
 *
 *  Adapter_Activator.h,v 1.1 2000/11/10 20:51:19 brunsch Exp
 *
 *  @brief  This class implements ImR's Adapter Activator.
 *
 *  @author Darrell Brunsch <brunsch@cs.wustl.edu>
 */
//=============================================================================

#ifndef IMR_ADAPTER_ACTIVATOR_H
#define IMR_ADAPTER_ACTIVATOR_H

#include "tao/PortableServer/PortableServerC.h"

/**
 * @class ImR_Adapter_Activator
 *
 * @brief Implementation Repository Adapter Activator
 *
 * Part of the ServantLocator/AdapterActivator combination that is used to
 * receive forwardable requests from clients.  The Adapter Activator creates
 * the POA structure that the request expects.  For each POA created, the
 * same ServantLocator will be registered in each one.
 */
class ImR_Adapter_Activator : public PortableServer::AdapterActivator
{
public:
  /// Constructor
  ImR_Adapter_Activator (PortableServer::ServantLocator_ptr servant);

  /// Called when a POA needs to be created.
  virtual CORBA::Boolean unknown_adapter (
    PortableServer::POA_ptr parent,
    const char *name,
    CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ()
  )
    ACE_THROW_SPEC ((CORBA::SystemException));

private:
  /// The ServantLocator registered in each new POA.
  PortableServer::ServantLocator_ptr servant_locator_;
};

#endif /* IMR_ADAPTER_ACTIVATOR_H */
