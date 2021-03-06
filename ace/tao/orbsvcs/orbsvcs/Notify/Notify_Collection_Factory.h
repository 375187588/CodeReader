/* -*- C++ -*- */
// Notify_Collection_Factory.h,v 1.1 2000/07/19 02:40:06 pradeep Exp
//
// ============================================================================
//
// = LIBRARY
//   ORBSVCS Notification
//
// = FILENAME
//   Notify_Collection_Factory.h
//
// = DESCRIPTION
//   A factory fpr the collection types used by Notify.
//
// = AUTHOR
//   Pradeep Gore <pradeep@cs.wustl.edu>
//
// ============================================================================

#ifndef NOTIFY_COLLECTION_FACTORY_H
#define NOTIFY_COLLECTION_FACTORY_H

#include "ace/pre.h"
#include "ace/Service_Object.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "notify_export.h"
#include "Notify_Collection.h"

class TAO_Notify_Export TAO_Notify_Collection_Factory : public ACE_Service_Object
{
  // = TITLE
  //   TAO_Notify_Collection_Factory
  //
  // = DESCRIPTION
  //   Collection factory
  //
public:
  // = Methods to create listener collections.
  virtual TAO_Notify_EventListener_List* create_event_listener_list (CORBA::Environment &ACE_TRY_ENV) = 0;
  // Create the event listener list.

 virtual TAO_Notify_UpdateListener_List* create_update_listener_list (CORBA::Environment &ACE_TRY_ENV) = 0;
  // create update listener list.
};

#include "ace/post.h"

#endif /* NOTIFY_COLLECTION_FACTORY_H */
