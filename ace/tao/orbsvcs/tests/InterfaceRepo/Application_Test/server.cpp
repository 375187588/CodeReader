// -*- C++ -*-
// server.cpp,v 1.4 2001/03/08 16:30:56 parsons Exp

#include "test_i.h"

ACE_RCSID(Application_Test, server, "server.cpp,v 1.4 2001/03/08 16:30:56 parsons Exp")

static const char *ior_output_file = "iorfile";

static int
write_ior_to_file (const char *ior)
{
  FILE *output_file = ACE_OS::fopen (ior_output_file, "w");

  if (output_file == 0)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "Cannot open output files for writing IOR: %s\n",
                         ior_output_file),
                        -1);
    }

  int result = ACE_OS::fprintf (output_file,
                                "%s",
                                ior);
  if (result < 0)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "ACE_OS::fprintf failed while writing %s to %s\n",
                         ior,
                         ior_output_file),
                        -1);
    }

  ACE_OS::fclose (output_file);

  return 0;
}

int
main (int argc, char *argv[])
{
	ACE_TRY_NEW_ENV
	  {
      CORBA::ORB_var orb = CORBA::ORB_init (argc,
                                            argv,
                                            "",
                                            ACE_TRY_ENV);
      ACE_TRY_CHECK;

      CORBA::Object_var poa_object =
        orb->resolve_initial_references ("RootPOA",
                                         ACE_TRY_ENV);
      ACE_TRY_CHECK;

      PortableServer::POA_var root_poa =
        PortableServer::POA::_narrow (poa_object.in (),
                                      ACE_TRY_ENV);
      ACE_TRY_CHECK;

      PortableServer::POAManager_var poa_manager =
        root_poa->the_POAManager (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      poa_manager->activate (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      inventory_i servant_impl;

      warehouse::inventory_var servant =
        servant_impl._this (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      CORBA::String_var ior =
        orb->object_to_string (servant.in (),
                               ACE_TRY_ENV);
      ACE_TRY_CHECK;

      int write_result = write_ior_to_file (ior.in ());

      if (write_result != 0)
        {
          ACE_ERROR_RETURN ((LM_ERROR,
                             "%p\n",
                             "write_ior_to_file"),
                            -1);
        }

      ACE_DEBUG ((LM_DEBUG,
                  "IOR is: <%s>\n",
                  ior.in ()));

      orb->run (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      root_poa->destroy (1,
                         1,
                         ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                           "server exception:");
      return 1;
    }
  ACE_ENDTRY;

  return 0;
}
