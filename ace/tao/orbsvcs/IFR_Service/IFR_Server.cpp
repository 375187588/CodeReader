/* -*- C++ -*- */
// IFR_Server.cpp,v 1.2 2001/03/28 19:55:31 parsons Exp

#include "IFR_Service.h"

ACE_RCSID(IFR_Service, IFR_Server, "IFR_Server.cpp,v 1.2 2001/03/28 19:55:31 parsons Exp")

int
main (int argc, char *argv[])
{
  IFR_Service server;

  ACE_DEBUG ((LM_DEBUG, "TAO Interface Repository\n"));

  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {
      int status = server.init (argc, argv, ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (status == -1)
        {
          return 1;
        }
      else
        {
          server.run (ACE_TRY_ENV);
          ACE_TRY_CHECK;

          status = server.fini (ACE_TRY_ENV);
          ACE_TRY_CHECK;

          if (status == -1)
            {
              return 1;
            }
        }
    }
  ACE_CATCH (CORBA::SystemException, sysex)
    {
      ACE_PRINT_EXCEPTION (sysex, "System Exception");
      return -1;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Unknown Exception");
      return -1;
    }
  ACE_ENDTRY;
  return 0;
}
