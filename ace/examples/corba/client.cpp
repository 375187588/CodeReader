// client.cpp,v 4.3 1998/07/31 22:55:09 gonzo Exp

#include "Test.hh"

ACE_RCSID(CORBA, client, "client.cpp,v 4.3 1998/07/31 22:55:09 gonzo Exp")

int
main (int argc, char *argv[])
{
  char *host = argc == 2 ? argv[1] : ACE_DEFAULT_SERVER_HOST;

  Test_var my_test;

  TRY {
    my_test = Test::_bind ("", host, IT_X);
    my_test->method (5);
  } CATCHANY {
    cerr << IT_X << endl;
    return -1;
  } ENDTRY;

  ACE_DEBUG ((LM_DEBUG, "everything works!\n"));

  // Memory for my_test is automatically released by destructor of
  // smart pointer.
  return 0;
}
