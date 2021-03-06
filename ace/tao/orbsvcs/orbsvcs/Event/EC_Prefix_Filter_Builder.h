/* -*- C++ -*- */
/**
 *  @file   EC_Prefix_Filter_Builder.h
 *
 *  EC_Prefix_Filter_Builder.h,v 1.5 2000/10/31 03:11:12 coryan Exp
 *
 *  @author Carlos O'Ryan (coryan@cs.wustl.edu)
 *
 * Based on previous work by Tim Harrison (harrison@cs.wustl.edu) and
 * other members of the DOC group. More details can be found in:
 *
 * http://doc.ece.uci.edu/~coryan/EC/index.html
 */

#ifndef TAO_EC_PREFIX_FILTER_BUILDER_H
#define TAO_EC_PREFIX_FILTER_BUILDER_H
#include "ace/pre.h"

#include "EC_Filter_Builder.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

class TAO_EC_Filter;
class TAO_EC_Event_Channel;

/**
 * @class TAO_EC_Prefix_Filter_Builder
 *
 * @brief Implement a builder for the fundamental filters.
 *
 * The prefix filtering mechanisms in the Event channel
 * (source/type based filtering + disjunctions and conjunctions)
 * are constructed using this class.
 */
class TAO_RTEvent_Export TAO_EC_Prefix_Filter_Builder : public TAO_EC_Filter_Builder
{
public:
  /// constructor.
  TAO_EC_Prefix_Filter_Builder (TAO_EC_Event_Channel* ec);

  /// destructor...
  virtual ~TAO_EC_Prefix_Filter_Builder (void);

  // = The TAO_EC_Filter_Builder methods...
  TAO_EC_Filter* build (TAO_EC_ProxyPushSupplier *supplier,
                        RtecEventChannelAdmin::ConsumerQOS& qos,
                        CORBA::Environment &env) const;

private:
  /// Recursively build the filter tree.
  TAO_EC_Filter* recursive_build (TAO_EC_ProxyPushSupplier *supplier,
                                  RtecEventChannelAdmin::ConsumerQOS& qos,
                                  CORBA::ULong& pos) const;

private:
  /// The event channel.
  TAO_EC_Event_Channel* event_channel_;
};

#if defined (__ACE_INLINE__)
#include "EC_Prefix_Filter_Builder.i"
#endif /* __ACE_INLINE__ */

#include "ace/post.h"
#endif /* TAO_EC_PREFIX_FILTER_BUILDER_H */
