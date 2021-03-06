// -*- C++ -*-

// ===================================================================
/**
 *  @file   PolicyFactory_Registry.h
 *
 *  PolicyFactory_Registry.h,v 1.5 2000/11/15 18:01:10 coryan Exp
 *
 *  @author Ossama Othman <ossama@uci.edu>
 */
// ===================================================================

#ifndef TAO_POLICY_FACTORY_REGISTRY_H
#define TAO_POLICY_FACTORY_REGISTRY_H

#include "ace/pre.h"

#include "corbafwd.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "PortableInterceptorC.h"
#include "PolicyC.h"
#include "ace/Map_Manager.h"

class TAO_ORB_Core;

/**
 * @class TAO_PolicyFactory_Registry
 *
 * @brief
 * ORB-specific registry that contains all portable interceptor
 * policy factories.
 */
class TAO_Export TAO_PolicyFactory_Registry
{
public:

  /**
   * The type of table that maps policy type to policy factory.
   *
   * @note
   * An ACE_Null_Mutex is used for this type since policy factories
   * are only registered when CORBA::ORB_init() is called, at which a
   * point a lock has already been acquired.  In short, the table is
   * only modified during ORB bootstrap-time.
   */
  typedef ACE_Map_Manager<
    CORBA::PolicyType,
    PortableInterceptor::PolicyFactory_ptr,
    ACE_Null_Mutex> TABLE;

public:

  /// Constructor
  TAO_PolicyFactory_Registry (void);

  /// Destructor.  Releases duplicated PolicyFactory references.
  ~TAO_PolicyFactory_Registry (void);

  /// Register a PolicyFactory with the underlying PolicyFactory
  /// sequence.  This method should only be called during ORB
  /// initialization.
  void register_policy_factory (
    CORBA::PolicyType type,
    PortableInterceptor::PolicyFactory_ptr policy_factory,
    CORBA::Environment &ACE_TRY_ENV);

  /// Construct a policy of the given type with the information
  /// contained in the CORBA::Any <value>.
  CORBA::Policy_ptr create_policy (CORBA::PolicyType type,
                                   const CORBA::Any &value,
                                   CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     CORBA::PolicyError));

private:

  /// The table that maps policy type to policy factory.
  TABLE factories_;

};

#include "ace/post.h"

#endif  /* TAO_POLICY_FACTORY_REGISTRY_H */
