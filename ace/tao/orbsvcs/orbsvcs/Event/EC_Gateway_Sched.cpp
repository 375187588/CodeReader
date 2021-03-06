// EC_Gateway_Sched.cpp,v 1.2 2001/02/02 02:31:47 fhunleth Exp

#include "EC_Gateway_Sched.h"
#include "orbsvcs/Time_Utilities.h"

ACE_RCSID(Event, EC_Gateway_sched, "EC_Gateway_Sched.cpp,v 1.2 2001/02/02 02:31:47 fhunleth Exp")

TAO_EC_Gateway_Sched::TAO_EC_Gateway_Sched (void)
  :  TAO_EC_Gateway_IIOP ()
{
}

TAO_EC_Gateway_Sched::~TAO_EC_Gateway_Sched (void)
{
}

void
TAO_EC_Gateway_Sched::init (RtecEventChannelAdmin::EventChannel_ptr rmt_ec,
                           RtecEventChannelAdmin::EventChannel_ptr lcl_ec,
                           RtecScheduler::Scheduler_ptr rmt_sched,
                           RtecScheduler::Scheduler_ptr lcl_sched,
                           const char* lcl_name,
                           const char* rmt_name,
                           CORBA::Environment &ACE_TRY_ENV)
{
  ACE_GUARD (TAO_SYNCH_MUTEX, ace_mon, this->lock_);

  this->init_i (rmt_ec, lcl_ec, ACE_TRY_ENV);
  ACE_CHECK;

  // @@ Should we throw a system exception here?
  if (CORBA::is_nil (rmt_sched)
      || CORBA::is_nil (lcl_sched)
      || lcl_name == 0
      || rmt_name == 0)
    ACE_THROW (CORBA::BAD_PARAM ());

  this->rmt_info_ =
    rmt_sched->create (rmt_name, ACE_TRY_ENV);
  ACE_CHECK;

  // @@ TODO Many things are hard-coded in the RT_Info here.

  // The worst case execution time is far less than 500 usecs, but
  // that is a safe estimate....
  ACE_Time_Value tv (0, 500);
  TimeBase::TimeT time;
  ORBSVCS_Time::Time_Value_to_TimeT (time, tv);
  rmt_sched->set (this->rmt_info_,
                  RtecScheduler::VERY_HIGH_CRITICALITY,
                  time, time, time,
                  25000 * 10,
                  RtecScheduler::VERY_LOW_IMPORTANCE,
                  time,
                  0,
                  RtecScheduler::OPERATION,
                  ACE_TRY_ENV);
  ACE_CHECK;

  this->lcl_info_ =
    lcl_sched->create (lcl_name, ACE_TRY_ENV);
  ACE_CHECK;

  tv = ACE_Time_Value (0, 500);
  ORBSVCS_Time::Time_Value_to_TimeT (time, tv);
  lcl_sched->set (this->lcl_info_,
                  RtecScheduler::VERY_HIGH_CRITICALITY,
                  time, time, time,
                  25000 * 10,
                  RtecScheduler::VERY_LOW_IMPORTANCE,
                  time,
                  1,
                  RtecScheduler::REMOTE_DEPENDANT,
                  ACE_TRY_ENV);
  ACE_CHECK;
}
