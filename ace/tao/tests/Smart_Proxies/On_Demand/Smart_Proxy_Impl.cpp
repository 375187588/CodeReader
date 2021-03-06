// Smart_Proxy_Impl.cpp,v 1.2 2000/03/31 07:23:38 kirthika Exp
#include "Smart_Proxy_Impl.h"

Smart_Test_Proxy::Smart_Test_Proxy (Test_ptr proxy)
  : TAO_Smart_Proxy_Base (proxy)
{
}

CORBA::Short 
Smart_Test_Proxy::method (CORBA::Short boo,
                          CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException,
                   Test::Oops))
{
  ACE_DEBUG ((LM_DEBUG,
              "Yahoo, I am smart\n"));
  
  CORBA::Short retval = 0;
  ACE_TRY 
    {
      retval = TAO_Test_Smart_Proxy_Base::method (boo,
                                                  ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCH (Test::Oops, reason)
    {
      ACE_PRINT_EXCEPTION (reason,
                           "User Exception");
      return -1;
    }
  ACE_ENDTRY;
  
  return retval;
}

