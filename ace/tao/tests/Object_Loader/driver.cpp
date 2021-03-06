//
// driver.cpp,v 1.3 2000/09/14 23:41:05 doccvs Exp
//

#include "TestC.h"
#include "tao/PortableServer/PortableServer.h"

int
main (int, char *[])
{
  int niterations = 10;
  int norbs = 10;

  ACE_TRY_NEW_ENV
    {
      for (int i = 0; i != niterations; ++i)
        {
          for (int j = 0; j != norbs; ++j)
            {
              char buf[16];
              ACE_OS::sprintf (buf, "ORB_%4.4d", j);

              int argc = 0;
              CORBA::ORB_var orb =
                CORBA::ORB_init (argc, 0, buf, ACE_TRY_ENV);
              ACE_TRY_CHECK;

              CORBA::Object_var object =
                orb->string_to_object ("DLL:Test_Object",
                                       ACE_TRY_ENV);
              ACE_TRY_CHECK;

              Test_var test =
                Test::_narrow (object.in (), ACE_TRY_ENV);
              ACE_TRY_CHECK;

              CORBA::Long count =
                test->instance_count (ACE_TRY_ENV);
              ACE_TRY_CHECK;

              if (count != norbs*i + j + 1)
                {
                  ACE_DEBUG ((LM_DEBUG,
                              "Incorrect number of objects "
                              "(%d != %d)\n",
                              count, norbs * i + j + 1));
                }
              test->destroy (ACE_TRY_ENV);
              ACE_TRY_CHECK;
            }
        }

      for (int j = 0; j != norbs; ++j)
        {
          char buf[16];
          ACE_OS::sprintf (buf, "ORB_%4.4d", j);

          int argc = 0;
          CORBA::ORB_var orb =
            CORBA::ORB_init (argc, 0, buf, ACE_TRY_ENV);
          ACE_TRY_CHECK;

          CORBA::Object_var obj =
            orb->resolve_initial_references ("RootPOA",
                                             ACE_TRY_ENV);
          ACE_TRY_CHECK;

          PortableServer::POA_var poa =
            PortableServer::POA::_narrow (obj.in (), ACE_TRY_ENV);
          ACE_TRY_CHECK;

          poa->destroy (1, 1, ACE_TRY_ENV);
          ACE_TRY_CHECK;

          orb->destroy (ACE_TRY_ENV);
          ACE_TRY_CHECK;
        }
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                           "main()");
      return 1;
    }
  ACE_ENDTRY;
  return 0;
}
