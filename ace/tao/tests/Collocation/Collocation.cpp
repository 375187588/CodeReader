// Collocation.cpp,v 1.3 2001/09/18 00:05:59 irfan Exp

#include "ace/streams.h"
#include "ace/Get_Opt.h"
#include "Collocation_Tester.h"
#include "tao/Strategies/advanced_resource.h"

ACE_RCSID(Collocation, main, "Collocation.cpp,v 1.3 2001/09/18 00:05:59 irfan Exp")

int main (int argc, char *argv[])
{
  ACE_TRY_NEW_ENV
    {
      Collocation_Test coll_test;

      coll_test.init (argc, argv, ACE_TRY_ENV);
      ACE_TRY_CHECK;

      coll_test.run (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      coll_test.shutdown (ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Uncaught exception: ");
    }
  ACE_ENDTRY;

  return 0;
}
