// -*- C++ -*-

// ===================================================================
/**
 *  @file   QOPPolicy.h
 *
 *  QOPPolicy.h,v 1.3 2001/07/12 01:31:49 othman Exp
 *
 *  @author Ossama Othman <ossama@uci.edu>
 */
// ===================================================================


#ifndef TAO_QOP_POLICY_H
#define TAO_QOP_POLICY_H

#include "ace/pre.h"

#include "security_export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "orbsvcs/SecurityLevel2C.h"

/**
 * @class TAO_QOPPolicy
 *
 * @brief Implementation of the SecurityLevel2::QOPPolicy interface.
 *
 * This policy can be used to affect the quality of protection (QoP)
 * for invocation on a per-object basis.  For example, it can be set
 * as a policy override using the standard
 * CORBA::Object::_set_policy_overrides() method.
 * @par
 * This policy can be created by using the CORBA::ORB::create_policy()
 * method by passing it the Security::SecQOPPolicy policy
 * type, and the appropriate Security::QOP enumeration (inserted into
 * a CORBA::Any).
 */
class TAO_Security_Export TAO_QOPPolicy
  : public virtual SecurityLevel2::QOPPolicy,
    public virtual TAO_Local_RefCounted_Object
{
  friend class TAO_Security_PolicyFactory;

public:

  /**
   * @name CORBA::Policy Methods
   */
  //@{
  virtual CORBA::PolicyType policy_type (CORBA::Environment &ACE_TRY_ENV =
                                           TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual CORBA::Policy_ptr copy (CORBA::Environment &ACE_TRY_ENV =
                                    TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual void destroy (CORBA::Environment &ACE_TRY_ENV =
                          TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));
  //@}

  /// Return the Quality-of-Protection value associated with this
  /// policy.
  virtual Security::QOP qop (CORBA::Environment &ACE_TRY_ENV =
                               TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

protected:

  /// Constructor
  TAO_QOPPolicy (Security::QOP qop);

  /// Destructor
  /**
   * Protected destructor to enforce the fact this class is reference
   * counted, and should not be destroyed using delete() by anything
   * other than the reference counting mechanism.
   */
  ~TAO_QOPPolicy (void);

private:

  /// Quality of protection which can be specified for an object
  /// reference and used to protect messages.
  Security::QOP qop_;

};

#include "ace/post.h"

#endif  /* TAO_QOP_POLICY_H */
