// Policy_Manager.i,v 1.23 2001/06/12 18:58:13 fhunleth Exp

ACE_INLINE
TAO_Policy_Manager::TAO_Policy_Manager (void)
  : impl_ (TAO_POLICY_ORB_SCOPE)
{
}

ACE_INLINE CORBA::Policy_ptr
TAO_Policy_Manager::get_policy (
      CORBA::PolicyType policy,
      CORBA::Environment &ACE_TRY_ENV)
{
  ACE_GUARD_RETURN (TAO_SYNCH_MUTEX, ace_mon, this->mutex_, 0);
  return this->impl_.get_policy (policy, ACE_TRY_ENV);
}

ACE_INLINE CORBA::PolicyList *
TAO_Policy_Manager::get_policy_overrides (
        const CORBA::PolicyTypeSeq & ts,
        CORBA::Environment &ACE_TRY_ENV)
      ACE_THROW_SPEC ((
                       CORBA::SystemException
                       ))
{
  ACE_GUARD_RETURN (TAO_SYNCH_MUTEX, ace_mon, this->mutex_, 0);
  return this->impl_.get_policy_overrides (ts, ACE_TRY_ENV);
}

ACE_INLINE void
TAO_Policy_Manager::set_policy_overrides (
        const CORBA::PolicyList & policies,
        CORBA::SetOverrideType set_add,
        CORBA::Environment &ACE_TRY_ENV)
      ACE_THROW_SPEC ((
                       CORBA::SystemException,
                       CORBA_InvalidPolicies
                       ))
{
  ACE_GUARD (TAO_SYNCH_MUTEX, ace_mon, this->mutex_);
  this->impl_.set_policy_overrides (policies, set_add, ACE_TRY_ENV);
}

ACE_INLINE CORBA::Policy_ptr
TAO_Policy_Manager::get_cached_policy (TAO_Cached_Policy_Type type)
{

  // @@ Previous code used a "double-checked locking hack" to check
  // if the policy was set before grabbing the lock to actually get
  // it, so that could save a lock operation.  This was removed, as
  // it is not as easy to do this anymore.

  ACE_GUARD_RETURN (TAO_SYNCH_MUTEX, ace_mon, this->mutex_, 0);

  return this->impl_.get_cached_policy (type);
}



// ****************************************************************

ACE_INLINE
TAO_Policy_Current::TAO_Policy_Current (void)
{
}

ACE_INLINE
TAO_Policy_Current_Impl::TAO_Policy_Current_Impl (void)
  : manager_impl_ (TAO_POLICY_THREAD_SCOPE)
{
}

ACE_INLINE CORBA::Policy_ptr
TAO_Policy_Current_Impl::get_policy (
      CORBA::PolicyType policy,
      CORBA::Environment &ACE_TRY_ENV)
{
  return this->manager_impl_.get_policy (policy, ACE_TRY_ENV);
}

ACE_INLINE CORBA::Policy_ptr
TAO_Policy_Current_Impl::get_cached_policy (TAO_Cached_Policy_Type type)
{
  return this->manager_impl_.get_cached_policy (type);
}

// ****************************************************************

ACE_INLINE CORBA::Policy_ptr
TAO_Policy_Current::get_policy (
      CORBA::PolicyType policy,
      CORBA::Environment &ACE_TRY_ENV)
{
  TAO_Policy_Current_Impl &impl = this->implementation ();

  return impl.get_policy (policy, ACE_TRY_ENV);
}

ACE_INLINE CORBA::PolicyList *
TAO_Policy_Current::get_policy_overrides (
        const CORBA::PolicyTypeSeq & ts,
        CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException))

{
  TAO_Policy_Current_Impl &impl = this->implementation ();

  return impl.get_policy_overrides (ts, ACE_TRY_ENV);
}

ACE_INLINE void
TAO_Policy_Current::set_policy_overrides (const CORBA::PolicyList & policies,
                                          CORBA::SetOverrideType set_add,
                                          CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException,
                   CORBA_InvalidPolicies))
{
  TAO_Policy_Current_Impl &impl = this->implementation ();

  impl.set_policy_overrides (policies, set_add, ACE_TRY_ENV);
}

ACE_INLINE CORBA::Policy_ptr
TAO_Policy_Current::get_cached_policy (TAO_Cached_Policy_Type type)
{
  TAO_Policy_Current_Impl &impl = this->implementation ();

  return impl.get_cached_policy (type);
}

