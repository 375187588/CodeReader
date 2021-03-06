// Input_Handler.cpp,v 4.6 1998/09/12 19:10:44 schmidt Exp

#include "Input_Handler.h"
#include "Notification_Receiver_Handler.h"

ACE_RCSID(Consumer, Input_Handler, "Input_Handler.cpp,v 4.6 1998/09/12 19:10:44 schmidt Exp")

#if defined (ACE_HAS_ORBIX) && (ACE_HAS_ORBIX != 0)

Input_Handler::~Input_Handler (void)
{
  ACE_DEBUG ((LM_DEBUG,
              "closing down Input_Handler::~Input_Handler\n"));
  this->handle_close ();
}

int
Input_Handler::consumer_initiated_shutdown (void)
{
  return this->consumer_initiated_shutdown_;
}

void
Input_Handler::consumer_initiated_shutdown (int c)
{
  this->consumer_initiated_shutdown_ = c;
}

ACE_HANDLE
Input_Handler::get_handle (void) const
{
  return this->handle_;
}

int
Input_Handler::handle_close (ACE_HANDLE, ACE_Reactor_Mask)
{
  ACE_DEBUG ((LM_DEBUG, "closing down Consumer::Input_Handler\n"));

  Event_Comm::Notification_Receiver *receiver = this->receiver_handler_->receiver ();
  Event_Comm::Notifier *notifier = this->receiver_handler_->notifier ();

  if (this->consumer_initiated_shutdown ())
    {
      // Only try to unsubscribe if the Consumer initiated the
      // shutdown.  Otherwise, the Supplier initiated it and it has
      // probably gone away by now!
      TRY 
        {
          // Gracefully shutdown the Receiver by removing it from the
          // Notifier's internal map.

          notifier->unsubscribe (receiver, "", IT_X);
        } 
      CATCHANY 
        {
          cerr << IT_X << endl;
        } 
      ENDTRY;
    }

  // Don't execute a callback here otherwise we'll recurse
  // indefinitely!
  if (ACE_Reactor::instance ()->remove_handler 
      (this,
       ACE_Event_Handler::READ_MASK | ACE_Event_Handler::DONT_CALL) == -1)
    ACE_ERROR ((LM_ERROR,
                "%p\n",
                "remove_handler"));

  // *Must* be allocated dyanmically!
  ::operator delete (this);
  return 0;
}

Input_Handler::Input_Handler (Notification_Receiver_Handler *ch,
			      ACE_HANDLE handle)
  : receiver_handler_ (ch),
    handle_ (handle),
    consumer_initiated_shutdown_ (0)
{
  if (ACE_Reactor::instance ()->register_handler 
      (this,
       ACE_Event_Handler::READ_MASK) == -1)
    ACE_ERROR ((LM_ERROR,
                "Input_Handler::Input_Handler\n"));
}

int
Input_Handler::handle_input (ACE_HANDLE h)
{
  char buf[BUFSIZ];

  // Read up to BUFSIZ worth of data from ACE_HANDLE h.
  ssize_t n = ACE_OS::read (h, buf, sizeof buf - 1);

  if (n > 0)
    {
      // Null terminate the buffer, replacing the '\n' with '\0'.
      if (buf[n - 1] == '\n' || buf[n - 1] == EOF)
	buf[n - 1] = '\0';
      else
	buf[n] = '\0';
      ACE_DEBUG ((LM_DEBUG,
                  "notifying for event %s\n",
                  buf));
    }
  else
    {
      ACE_OS::strcpy (buf, "quit");
      ACE_DEBUG ((LM_DEBUG,
                  "shutting down Input_Handler\n"));
    }

  Event_Comm::Notifier *notifier =
    this->receiver_handler_->notifier ();

  ACE_ASSERT (notifier != 0);

  if (ACE_OS::strcmp (buf, "quit") == 0)
    {
      // Consumer wants to shutdown.
      this->consumer_initiated_shutdown (1);

      // Tell the main event loop to shutdown. 
      ACE_Reactor::end_event_loop();
    }
  else
    {
      TRY 
        {
          Event_Comm::Notification notification;
	
          notification.tag_ = ACE_OS::strdup (buf);

          notifier->send_notification (notification, IT_X);
        }
      CATCHANY 
        {
          cerr << "Unexpected exception " << IT_X << endl;
        } ENDTRY;
    }

  /* NOTREACHED */
  return 0;
}
#endif /* ACE_HAS_ORBIX */
