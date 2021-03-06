// -*- C++ -*-

//=============================================================================
/**
 * @file server.cpp
 *
 * server.cpp,v 1.3 2001/08/30 22:27:43 othman Exp
 *
 * @author Ossama Othman <ossama@uci.edu>
 */
//=============================================================================


#include "ace/Service_Config.h"
#include "ace/Thread_Manager.h"

int
main (int, char *[])
{
  // Process a Service Configurator directive that will cause the test
  // server module to be dynamically loaded.
  //
  // This is done to prevent the server binary from being forced to
  // explicitly link to the test server module library.  Hence, the
  // server binary is completely decoupled from the test server
  // module (and the ORB!).
  //
  // In the process of doing this, the Test CORBA object will be
  // activated, and the ORB will be run.
  if (ACE_Service_Config::process_directive ("dynamic Server_Module Service_Object * Test_Server_Module:_make_Test_Server_Module() \"\"") != 0)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "%p\n",
                         "ERROR: Server unable to process the "
                         "Service Configurator directive"),
                        -1);
    }

  ACE_DEBUG ((LM_INFO,
              "SERVER: CORBA-portion of the test dynamically loaded.\n"));

  // Wait for all threads to complete.
  ACE_Thread_Manager::instance ()->wait ();

  ACE_DEBUG ((LM_INFO,
              "SERVER:  Terminated successfully.\n"));

  return 0;
}
