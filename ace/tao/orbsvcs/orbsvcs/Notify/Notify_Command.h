/* -*- C++ -*- */
// Notify_Command.h,v 1.2 2000/08/30 01:28:55 pradeep Exp
//
// ============================================================================
//
// = LIBRARY
//   ORBSVCS Notification
//
// = FILENAME
//   Notify_Command.h
//
// = DESCRIPTION
//   Command Object base class used by Notify's Worker Task objects.
//
// = AUTHOR
//   Pradeep Gore <pradeep@cs.wustl.edu>
//
// ============================================================================

#ifndef TAO_NOTIFY_COMMAND_H
#define TAO_NOTIFY_COMMAND_H

#include "ace/pre.h"
#include "ace/Message_Block.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "tao/corba.h"
#include "notify_export.h"

class TAO_Notify_Event_Processor;
class TAO_Notify_Event;

class TAO_Notify_Export TAO_Notify_Command : public ACE_Message_Block
{
  // = TITLE
  //   TAO_Notify_Command
  //
  // = DESCRIPTION
  //   Base class for Command Objects.
  //   Command objects are executed by the Notify_Worker_Task.
  //
 public:
  TAO_Notify_Command (TAO_Notify_Event_Processor* event_processor, TAO_Notify_Event* event);
  ~TAO_Notify_Command ();

  virtual int execute (CORBA::Environment& ACE_TRY_ENV) = 0;
  // Command callback

protected:
  // = Data Members
  TAO_Notify_Event_Processor* event_processor_;
  // The command objects should notify the event processor once they have successfully
  // executed commands.

  TAO_Notify_Event* event_;
  // The event that we "execute" this command on.
};


#if defined (__ACE_INLINE__)
#include "Notify_Command.i"
#endif /* __ACE_INLINE__ */

#include "ace/post.h"

#endif /* TAO_NOTIFY_COMMAND_H */
