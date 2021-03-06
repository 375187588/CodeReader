// Smart_Proxy_Impl.h,v 1.1 1999/11/22 22:03:33 kirthika Exp

#include "testC.h"

class Smart_Test_Factory : public virtual TAO_Test_Default_Proxy_Factory
{
public:

  Smart_Test_Factory (void);
  
  virtual Test_ptr create_proxy (Test_ptr proxy,
                                 CORBA::Environment &env = 
                                 TAO_default_environment ());
  // This method will create the smart_proxy.   
};

class Smart_Test_Proxy : public virtual TAO_Test_Smart_Proxy_Base 
{
public:
  Smart_Test_Proxy (Test_ptr proxy);

  virtual CORBA::Short method (CORBA::Short boo,
                               CORBA::Environment &ACE_TRY_ENV = 
                               TAO_default_environment ())
    ACE_THROW_SPEC ((CORBA::SystemException, 
                     Test::Oops));
  // "Smartify" the method call!

  // Don't need to add any extra functionality into <shutdown>, hence
  // we don't define it.
};
