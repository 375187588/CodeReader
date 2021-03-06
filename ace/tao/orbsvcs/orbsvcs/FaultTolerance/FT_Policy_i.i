//FT_Policy_i.i,v 1.3 2000/10/08 21:47:40 bala Exp
ACE_INLINE
TAO_FT_Request_Duration_Policy::TAO_FT_Request_Duration_Policy (const TimeBase::TimeT &duration)
  : request_duration_ (duration)
{
}

ACE_INLINE
TAO_FT_Request_Duration_Policy::TAO_FT_Request_Duration_Policy (const TAO_FT_Request_Duration_Policy &rhs)
  : FT::RequestDurationPolicy (),
    TAO_Local_RefCounted_Object (),
    request_duration_ (rhs.request_duration_)
{
}

ACE_INLINE
TAO_FT_Heart_Beat_Policy::TAO_FT_Heart_Beat_Policy (
    const CORBA::Boolean heartbeat,
    const TimeBase::TimeT &interval,
    const TimeBase::TimeT &timeout)
  : heartbeat_ (heartbeat),
    heartbeat_interval_ (interval),
    heartbeat_timeout_ (timeout)
{
}

ACE_INLINE
TAO_FT_Heart_Beat_Policy::TAO_FT_Heart_Beat_Policy (const TAO_FT_Heart_Beat_Policy &rhs)
  : FT::HeartbeatPolicy (),
    TAO_Local_RefCounted_Object (),
    heartbeat_ (rhs.heartbeat_),
    heartbeat_interval_ (rhs.heartbeat_interval_),
    heartbeat_timeout_ (rhs.heartbeat_timeout_)
{
}


ACE_INLINE
TAO_FT_Heart_Beat_Enabled_Policy::TAO_FT_Heart_Beat_Enabled_Policy (
    const CORBA::Boolean heartbeat)
  : heartbeat_enabled_value_ (heartbeat)
{
}

ACE_INLINE
TAO_FT_Heart_Beat_Enabled_Policy::TAO_FT_Heart_Beat_Enabled_Policy (
    const TAO_FT_Heart_Beat_Enabled_Policy &rhs)
  : FT::HeartbeatEnabledPolicy (),
    TAO_Local_RefCounted_Object (),
    heartbeat_enabled_value_ (rhs.heartbeat_enabled_value_)
{
}
