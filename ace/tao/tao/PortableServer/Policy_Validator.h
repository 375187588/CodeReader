//=============================================================================
/**
 *  @file    Policy_Validator.h
 *
 *  Policy_Validator.h,v 1.2 2001/09/18 00:05:53 irfan Exp
 *
 *  This file contains the declaration for the POA policy validator
 *  interface.
 *
 *  @author  Angelo Corsaro <corsaro@cs.wustl.edu>
 *  @author  Frank Hunleth  <fhuntleth@cs.wustl.edu>
 */
//=============================================================================

#ifndef TAO_POLICY_VALIDATOR_H_
#define TAO_POLICY_VALIDATOR_H_

#include "ace/pre.h"
#include "tao/corbafwd.h"
#include "portableserver_export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


// Forward declarations.
class TAO_Policy_Set;
class TAO_ORB_Core;

class TAO_PortableServer_Export TAO_POA_Policy_Validator
{
public:
  /// Constructor.
  TAO_POA_Policy_Validator (TAO_ORB_Core &orb_core);

  /// Destructor.
  virtual ~TAO_POA_Policy_Validator (void);

  /**
   * Validate that the policies in the specified set
   * are consistent and legal.  Throw an appropriate exception
   * if that is not the case.
   */
  void validate (TAO_Policy_Set &policies,
                 CORBA::Environment &ACE_TRY_ENV);

  /**
   * Add/merge policies.
   **/
  void merge_policies (TAO_Policy_Set &policies,
                       CORBA::Environment &ACE_TRY_ENV);

  /**
   * Return whether the specified policy type is legal for the
   * current configuration.  This is needed since the user can
   * potentially specify policies that are unknown to an
   * validate () routine, and these need to be caught.
   */
  CORBA::Boolean legal_policy (CORBA::PolicyType type);

  /**
   * Adds a validator to the "chain of validators". The <code>
   * TAO_POA_Policy_Validator </code> implements something that looks
   * like a chain of responsability in which different member of the
   * chain have the responsability of validating a given set of
   * policies.
   */
  void add_validator (TAO_POA_Policy_Validator *validator);


protected:
  virtual void validate_impl (TAO_Policy_Set &policies,
                              CORBA::Environment &ACE_TRY_ENV) = 0;

  virtual void merge_policies_impl (TAO_Policy_Set &policies,
                                    CORBA::Environment &ACE_TRY_ENV) = 0;

  virtual CORBA::Boolean legal_policy_impl (CORBA::PolicyType type) = 0;

  TAO_ORB_Core &orb_core_;

private:
  TAO_POA_Policy_Validator *next_;
  static TAO_POA_Policy_Validator *last_;
};

#include "ace/post.h"
#endif /* TAO_POLICY_VALIDATOR_H_ */
