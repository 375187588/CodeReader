/* -*- C++ -*- */
//=============================================================================
/**
 *  @file   Messaging_Policy_i.h
 *
 *  Messaging_Policy_i.h,v 1.35 2001/06/12 18:58:08 fhunleth Exp
 *
 *  @author Carlos O'Ryan (coryan@cs.wustl.edu)
 */
//=============================================================================


#ifndef TAO_MESSAGING_POLICY_I_H
#define TAO_MESSAGING_POLICY_I_H
#include "ace/pre.h"

#include "tao/orbconf.h"
#include "tao/MessagingC.h"
#include "tao/LocalObject.h"

#if defined(_MSC_VER)
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif /* _MSC_VER >= 1200 */
#pragma warning(disable:4250)
#endif /* _MSC_VER */

#if (TAO_HAS_RELATIVE_ROUNDTRIP_TIMEOUT_POLICY == 1)

class TAO_Export TAO_RelativeRoundtripTimeoutPolicy
  : public Messaging::RelativeRoundtripTimeoutPolicy,
    public TAO_Local_RefCounted_Object
{
  // = TITLE
  //   Messaging::RelativeRoundtripTimeoutPolicy implementation
  //
  // = DESCRIPTION
  //   This policy controls the total (round-trip) timeout time for a
  //   request.
  //
public:
  /// Constructor.
  TAO_RelativeRoundtripTimeoutPolicy (const TimeBase::TimeT& relative_expiry);

  /// Copy constructor.
  TAO_RelativeRoundtripTimeoutPolicy (const TAO_RelativeRoundtripTimeoutPolicy &rhs);

  /// Implement the timeout hook, this is set in the ORB_Core at
  /// initialization time.
  static void hook (TAO_ORB_Core *orb_core,
                    TAO_Stub *stub,
                    int &has_timeout,
                    ACE_Time_Value &time_value);

  /// Helper method for the implementation of
  /// CORBA::ORB::create_policy.
  static CORBA::Policy_ptr create (const CORBA::Any& val,
                                   CORBA::Environment &ACE_TRY_ENV = TAO_default_environment ());

  /// Returns a copy of <this>.
  virtual TAO_RelativeRoundtripTimeoutPolicy *clone (void) const;

  // = The Messaging::RelativeRoundtripTimeoutPolicy methods
  virtual TimeBase::TimeT relative_expiry (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual CORBA::PolicyType policy_type (CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual CORBA::Policy_ptr copy (CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual void destroy (CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  /// Change the CORBA representation to the ACE representation.
  void set_time_value (ACE_Time_Value &time_value);

  // Return the cached policy type for this policy.
  virtual TAO_Cached_Policy_Type _tao_cached_type (void) const;

private:
  /// The attribute
  TimeBase::TimeT relative_expiry_;
};

#endif /* TAO_HAS_RELATIVE_ROUNDTRIP_TIMEOUT_POLICY == 1 */

////////////////////////////////////////////////////////////////////////////////

#if (TAO_HAS_SYNC_SCOPE_POLICY == 1)

class TAO_Export TAO_Sync_Scope_Policy
  : public Messaging::SyncScopePolicy,
    public TAO_Local_RefCounted_Object
{
  // = TITLE
  //   Messaging::SyncScopePolicy implementation.
  //
  // = DESCRIPTION
  //   This policy controls the sync strategy used by the ORB to
  //   transport requests.
  //
public:
  /// Constructor.
  TAO_Sync_Scope_Policy (Messaging::SyncScope synchronization);

  /// Copy constructor.
  TAO_Sync_Scope_Policy (const TAO_Sync_Scope_Policy &rhs);

  /// Implement the Sync_Scope hook, this is set in the ORB_Core at
  /// initialization time.
  static void hook (TAO_ORB_Core *orb_core,
                    TAO_Stub *stub,
                    int &has_synchronization,
                    int &scope);

  /// Helper method for the implementation of
  /// CORBA::ORB::create_policy.
  static CORBA::Policy_ptr create (const CORBA::Any& val,
                                   CORBA::Environment &ACE_TRY_ENV = TAO_default_environment ());

  /// Returns a copy of <this>.
  virtual TAO_Sync_Scope_Policy *clone (void) const;

  // = The Messaging::SyncScopePolicy methods.

  virtual Messaging::SyncScope synchronization (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  void get_synchronization (Messaging::SyncScope &synchronization) const;

  virtual CORBA::PolicyType policy_type (CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual CORBA::Policy_ptr copy (CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual void destroy (CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  // Return the cached policy type for this policy.
  virtual TAO_Cached_Policy_Type _tao_cached_type (void) const;
private:

  /// The attribute
  Messaging::SyncScope synchronization_;
};

#endif /* TAO_HAS_SYNC_SCOPE_POLICY == 1 */

#if defined (__ACE_INLINE__)
#include "tao/Messaging_Policy_i.i"
#endif /* __ACE_INLINE__ */

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma warning(pop)
#endif /* _MSC_VER */

#include "ace/post.h"
#endif /* TAO_MESSAGING_POLICY_I_H */
