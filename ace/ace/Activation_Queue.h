/* -*- C++ -*- */

//=============================================================================
/**
 *  @file    Activation_Queue.h
 *
 *  Activation_Queue.h,v 4.18 2001/09/27 22:35:47 schmidt Exp
 *
 *  @author Andres Kruse <Andres.Kruse@cern.ch> and
 *  @author Douglas C. Schmidt <schmidt@cs.wustl.edu>
 */
//=============================================================================

#ifndef ACE_ACTIVATION_QUEUE_H
#define ACE_ACTIVATION_QUEUE_H
#include "ace/pre.h"

#include "ace/Synch_T.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/Message_Queue.h"
#include "ace/Method_Request.h"

// Be compatible with the terminology in the POSA2 book!
#define ACE_Activation_List ACE_Activation_Queue

/**
 * @class ACE_Activation_Queue
 *
 * @brief Reifies a method into a request.  Subclasses typically
 * represent necessary state and behavior.
 *
 * A <Method_Request> is inserted in the <Activation_Queue>,
 * where it is subsequently removed by the <Scheduler>, which
 * invokes its <call> method..
 */
class ACE_Export ACE_Activation_Queue
{
public:
  // = Initialization and termination methods.
  /// Constructor.
  ACE_Activation_Queue (ACE_Message_Queue<ACE_SYNCH> *new_queue = 0);

  /// Destructor.
  virtual ~ACE_Activation_Queue (void);

  // = Activate Queue operations.

  // For the following two methods if <timeout> == 0, the caller will
  // block until action is possible, else will wait until the absolute
  // time specified in *<timeout> elapses.  These calls will return,
  // however, when queue is closed, deactivated, when a signal occurs,
  // or if the time specified in timeout elapses, (in which case errno
  // = EWOULDBLOCK).

  /// Dequeue the next available <Method_Request>.
  ACE_Method_Request *dequeue (ACE_Time_Value *tv = 0);

  /// Enqueue the <Method_Request> in priority order.  The priority is
  /// determined by the <priority> method of the <new_message_request>.
  int enqueue (ACE_Method_Request *new_method_request,
               ACE_Time_Value *tv = 0);

  /// Get the current number of method objects in the queue.
  int method_count (void) const;

  /// Returns 1 if the queue is empty, 0 otherwise.
  int is_empty (void) const;

  /// Returns 1 if the queue is full, 0 otherwise.
  int is_full (void) const;

  /// Dump the state of an request.
  void dump (void) const;

  /// Declare the dynamic allocation hooks.
  ACE_ALLOC_HOOK_DECLARE;

protected:
  /// Stores the <Method_Requests>.
  ACE_Message_Queue<ACE_SYNCH> *queue_;

  /// Keeps track of whether we need to delete the queue.
  int delete_queue_;

private:
  // = Prevent assignment and initialization.
  ACE_UNIMPLEMENTED_FUNC (void operator= (const ACE_Activation_Queue &))
  ACE_UNIMPLEMENTED_FUNC (ACE_Activation_Queue (const ACE_Activation_Queue &))
};

#if defined (__ACE_INLINE__)
#include "ace/Activation_Queue.i"
#endif /* __ACE_INLINE__ */

#include "ace/post.h"
#endif /* ACE_ACTIVATION_QUEUE_H */
