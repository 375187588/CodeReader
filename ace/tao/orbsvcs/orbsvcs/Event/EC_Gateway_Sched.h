/* -*- C++ -*- */
/**
 *  @file   EC_Gateway_Sched.h
 *
 *  EC_Gateway_Sched.h,v 1.3 2000/10/31 03:11:12 coryan Exp
 *
 *  @author Carlos O'Ryan (coryan@cs.wustl.edu)
 *
 * Based on previous work by Tim Harrison (harrison@cs.wustl.edu) and
 * other members of the DOC group. More details can be found in:
 *
 * http://doc.ece.uci.edu/~coryan/EC/index.html
 *
 *
 */

#ifndef TAO_EC_GATEWAY_SCHED_H
#define TAO_EC_GATEWAY_SCHED_H
#include "ace/pre.h"

#include "EC_Gateway.h"
#include "orbsvcs/RtecSchedulerC.h"
#include "sched_event_export.h"

// ****************************************************************

/**
 * @class TAO_EC_Gateway_Sched
 *
 * @brief Extend the EC_Gateway_IIOP interface to support scheduling.
 */
class TAO_RTSchedEvent_Export TAO_EC_Gateway_Sched : public TAO_EC_Gateway_IIOP
{
public:
  TAO_EC_Gateway_Sched (void);
  ~TAO_EC_Gateway_Sched (void);

  /**
   * To do its job this class requires to know the local and remote
   * ECs it will connect to; furthermore it also requires to build
   * RT_Infos for the local and remote schedulers.
   * @todo part of the RT_Info is hardcoded, we need to make it
   * parametric.
   */
  void init (RtecEventChannelAdmin::EventChannel_ptr rmt_ec,
             RtecEventChannelAdmin::EventChannel_ptr lcl_ec,
             RtecScheduler::Scheduler_ptr rmt_sched,
             RtecScheduler::Scheduler_ptr lcl_sched,
             const char* lcl_name,
             const char* rmt_name,
             CORBA::Environment &env = TAO_default_environment ());
};

#include "ace/post.h"
#endif /* ACE_EC_GATEWAY_SCHED_H */
