/* -*- C++ -*- */
// Notify_Worker_Task.h,v 1.5 2000/09/09 01:52:42 pradeep Exp
//
// ============================================================================
//
// = LIBRARY
//   ORBSVCS Notification
//
// = FILENAME
//   Notify_Worker_Task.h
//
// = DESCRIPTION
//   Worker task handles command execution.
//
// = AUTHOR
//   Pradeep Gore <pradeep@cs.wustl.edu>
//
// ============================================================================

#ifndef TAO_NOTIFY_WORKER_TASK_H
#define TAO_NOTIFY_WORKER_TASK_H

#include "ace/pre.h"
#include "ace/Task.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "tao/corba.h"
#include "Notify_Command.h"
#include "notify_export.h"

class TAO_Notify_AdminProperties;

class TAO_Notify_Export TAO_Notify_Worker_Task
{
  // = TITLE
  //   TAO_Notify_Worker_Task
  //
  // = DESCRIPTION
  //   A worker task that we use for various event processing jobs.
  //   Also see TAO_Notify_Command - This task executes Notify_Command objects.
  //   This implementation simply executes the command.
  //
public:
  // = Initialization and termination code
  TAO_Notify_Worker_Task (void);
  virtual ~TAO_Notify_Worker_Task ();
  // Constructor.

  virtual int init_task (TAO_Notify_AdminProperties* const admin_properties);
  // Init the task

  virtual void shutdown (CORBA::Environment& ACE_TRY_ENV);
  // shutdown this task.

  virtual int process_event (TAO_Notify_Command *mb, CORBA::Environment& ACE_TRY_ENV, ACE_Time_Value *tv = 0);
  // Process the command.
};

#include "ace/post.h"
#endif /* TAO_NOTIFY_WORKER_TASK_H */
