// client.cpp,v 1.1 2001/01/19 21:59:03 doccvs Exp

#include "SLevel1_TestC.h"

ACE_RCSID (SecurityLevel1, client, "client.cpp,v 1.1 2001/01/19 21:59:03 doccvs Exp")

const char *ior = "file://test.ior";

int
parse_args (int argc, char *argv[])
{
  ACE_Get_Opt get_opts (argc, argv, "k:");
  int c;

  while ((c = get_opts ()) != -1)
    switch (c)
      {
      case 'k':
        ior = get_opts.optarg;
        break;
      case '?':
      default:
        ACE_ERROR_RETURN ((LM_ERROR,
                           "usage:  %s "
                           "-k <ior> "
                           "\n",
                           argv [0]),
                          -1);
      }
  // Indicates sucessful parsing of the command line
  return 0;
}

int
main (int argc, char *argv [])
{
  ACE_TRY_NEW_ENV
    {
      CORBA::ORB_var orb =
        CORBA::ORB_init (argc, argv, "", ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (parse_args (argc, argv) != 0)
        return 1;

      CORBA::Object_var object =
        orb->string_to_object (ior, ACE_TRY_ENV);
      ACE_TRY_CHECK;

      SLevel1_Server_var server =
        SLevel1_Server::_narrow (object.in (), ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (CORBA::is_nil (server.in ()))
        {
          ACE_ERROR_RETURN ((LM_ERROR,
                             "Object reference <%s> is nil\n",
                             ior),
                            1);
        }

      CORBA::Boolean authorized = 
        server->authorize_level1 (ACE_TRY_ENV);
      ACE_TRY_CHECK;
      
      if (authorized == 0)
        ACE_DEBUG ((LM_DEBUG,
                    "AUTHORIZED\n"));
      else if (authorized == 1)
        ACE_DEBUG ((LM_DEBUG,
                    "DENIED: You Do NOT have enough privileges\n"));
        
      server->shutdown (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      orb->destroy (ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                           "Caught exception:");
      return 1;
    }
  ACE_ENDTRY;

  return 0;
}
      
