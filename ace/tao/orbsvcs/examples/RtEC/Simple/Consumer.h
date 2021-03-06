/* -*- C++ -*- */
// Consumer.h,v 1.3 2000/04/24 22:28:54 coryan Exp
//
// ============================================================================
//
// = LIBRARY
//   ORBSVCS Real-time Event Channel examples
//
// = FILENAME
//   Consumer
//
// = AUTHOR
//   Carlos O'Ryan (coryan@cs.wustl.edu)
//
// ============================================================================

#ifndef CONSUMER_H
#define CONSUMER_H

#include "orbsvcs/RtecEventCommS.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

class Consumer : public POA_RtecEventComm::PushConsumer
{
  // = TITLE
  //   Simple consumer object
  //
  // = DESCRIPTION
  //   This class is a consumer of events.
  //   It simply registers for one event type.
  //
public:
  Consumer (void);
  // Constructor

  int run (int argc, char* argv[]);
  // Run the test

  // = The RtecEventComm::PushConsumer methods

  virtual void push (const RtecEventComm::EventSet& events,
                     CORBA::Environment &_env)
    ACE_THROW_SPEC ((CORBA::SystemException));
  virtual void disconnect_push_consumer (CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException));
  // The skeleton methods.

private:
  CORBA::ULong event_count_;
  // Keep track of the number of events received.

  CORBA::ORB_ptr orb_;
  // The orb, just a pointer because the ORB does not outlive the
  // run() method...
};

#endif /* CONSUMER_H */
