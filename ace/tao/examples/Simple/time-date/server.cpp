// server.cpp,v 1.6 2000/05/30 05:43:33 othman Exp

// ============================================================================
//
// = LIBRARY
//    examples/Simple/time-date
//
// = FILENAME
//    server.cpp
//
// = DESCRIPTION
//   This directory contains an example that illustrates how the ACE
//   Service Configurator can dynamically configure an ORB and its
//   servants from a svc.conf file.
//
// = AUTHOR
//    Doug Schmidt <schmidt@cs.wustl.edu>
//
// ============================================================================

#include "ace/Service_Config.h"
#include "ace/Log_Msg.h"

ACE_RCSID(Misc, main, "server.cpp,v 1.6 2000/05/30 05:43:33 othman Exp")

int
main (int argc, ACE_TCHAR *argv[])
{
  if (ACE_Service_Config::open (argc, argv) == -1 
      && errno != ENOENT)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%p\n"),
                       ACE_TEXT ("open")),
                      1);

  // Run forever, performing the configured services until we
  // shutdown.
  ACE_Reactor::run_event_loop ();
  return 0;
}
