/* -*- C++ -*- */
// BiDir_Policy_i.h,v 1.2 2001/03/30 19:52:13 bala Exp
//

// ===================================================================
/**
 *  @file BiDir_Policy_i.h
 *
 *  BiDir_Policy_i.h,v 1.2 2001/03/30 19:52:13 bala Exp
 *
 *  @author Balachandran Natarajan <bala@cs.wustl.edu>
 */
// ===================================================================

#ifndef TAO_BIDIR_POLICY_I_H
#define TAO_BIDIR_POLICY_I_H
#include "ace/pre.h"
#include "bidirgiop_export.h"


#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


#include "BiDirGIOP.h"
#include "tao/LocalObject.h"

#if defined(_MSC_VER)
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif /* _MSC_VER >= 1200 */
#pragma warning(disable:4250)
#endif /* _MSC_VER */

/**
 * @class TAO_BidirectionalPolicy
 *
 * @brief  Implementation of the BiDirPolicy::BidirectionalPolicy
 *
 * This policy controls the whether the connections established  by the
 * clients can be made bi-directional or not. Further, this policy
 * also needs to be set by the server to use the connections
 * established by the clients to send requests.
 *
 */

class TAO_BiDirGIOP_Export TAO_BidirectionalPolicy
  : public BiDirPolicy::BidirectionalPolicy,
    public TAO_Local_RefCounted_Object
{

public:

  /// Constructor.
  TAO_BidirectionalPolicy (const BiDirPolicy::BidirectionalPolicyValue val);

  /// Copy constructor.
  TAO_BidirectionalPolicy (const TAO_BidirectionalPolicy &rhs);

  /// Returns a copy of <this>.
  virtual TAO_BidirectionalPolicy *clone (void) const;

  /// = The BiDir::BidirectionalPolicy methods
  virtual BiDirPolicy::BidirectionalPolicyValue value (
        CORBA::Environment &ACE_TRY_ENV =
          TAO_default_environment ()
      )
      ACE_THROW_SPEC ((
        CORBA::SystemException
      ));

  virtual CORBA::PolicyType policy_type (CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual CORBA::Policy_ptr copy (CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual void destroy (CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException));

private:

  /// The attribute
  BiDirPolicy::BidirectionalPolicyValue value_;
};



#if defined (__ACE_INLINE__)
#include "BiDir_Policy_i.inl"
#endif /* __ACE_INLINE__ */

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma warning(pop)
#endif /* _MSC_VER */

#include "ace/post.h"
#endif /* TAO_BIDIR_POLICY_I_H */
