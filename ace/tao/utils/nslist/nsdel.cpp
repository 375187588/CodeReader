// nsdel.cpp,v 1.2 2000/06/05 21:28:57 othman Exp

// ================================================================
//
// = LIBRARY
//    utils
//
// = FILENAME
//    nsdel.cpp
//
// = DESCRIPTION
//    Naming Service del utility
//
// = AUTHOR
//     Carlos O'Ryan
//
// ================================================================

#include "orbsvcs/CosNamingC.h"

CORBA::ORB_var orb;
int showIOR = 0;
int showNSonly = 0;

int
main (int argc, char *argv[])
{
  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {
      CORBA::ORB_var orb =
        CORBA::ORB_init (argc, argv, "", ACE_TRY_ENV);
      ACE_TRY_CHECK;

      char *pname = argv[0];

      const char * name = 0;
      while (argc > 0)
        {
          if (strcmp(*argv, "--name") == 0)
            {
              if (argc == 1)
                {
                  ACE_DEBUG ((LM_DEBUG,
                              "Error: --name requires an argument\n"));
                  return 1;
                }
              argc--;
              argv++;
              name = *argv;
            }
          else if (strncmp(*argv, "--", 2) == 0)
            {
              ACE_DEBUG ((LM_DEBUG,
                          "Usage: %s [ --name <name> ]\n", pname));
              return 1;
            }
          argc--;
          argv++;
        }
      if (name == 0)
        {
          ACE_DEBUG ((LM_DEBUG,
                      "Usage: %s [ --name <name> ]\n", pname));
          return 1;
        }
          
      CORBA::Object_var nc_obj =
        orb->resolve_initial_references ("NameService", ACE_TRY_ENV);
      ACE_TRY_CHECK;

      CosNaming::NamingContext_var root_nc =
        CosNaming::NamingContext::_narrow (nc_obj.in (), ACE_TRY_ENV);
      ACE_TRY_CHECK;
      if (CORBA::is_nil (root_nc.in ()))
        {
          ACE_DEBUG ((LM_DEBUG,
                      "Error: nil naming context\n"));
          return 1;
        }

      CosNaming::Name the_name (1);
      the_name.length (1);
      the_name[0].id = CORBA::string_dup (name);
      root_nc->unbind (the_name, ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                           "Exception in nsdel");
      return 1;
    }
  ACE_ENDTRY;

  return 0;
}
