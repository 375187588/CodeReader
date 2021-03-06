/* -*- C++ -*- */
// Event_Comm_i.h,v 4.4 1998/10/20 02:34:35 levine Exp

// ============================================================================
//
// = LIBRARY
//    EventComm
//
// = FILENAME
//    Event_Comm_i.h
//
// = DESCRIPTION
//    Class interface for the implementation of the distributed
//    event notification mechanism.
//
// = AUTHOR
//    Douglas C. Schmidt (schmidt@cs.wustl.edu)
//
// ============================================================================

#ifndef _EVENT_COMM_I_H
#define _EVENT_COMM_I_H

#include "Notification_Receiver_i.h"
#include "Notifier_i.h"

#if defined (ACE_HAS_ORBIX) && (ACE_HAS_ORBIX != 0)

// Tie the <Notification_Receiver> and <Notifier> implementation
// classes together with the IDL interface.

DEF_TIE_Event_Comm_Notification_Receiver (Notification_Receiver_i)
DEF_TIE_Event_Comm_Notifier (Notifier_i)

#endif /* ACE_HAS_ORBIX */
#endif /* _EVENT_COMM_I_H */
