// Identity_Server.cpp,v 1.7 2001/06/13 04:03:29 kitty Exp
// ============================================================================
//
// = LIBRARY
//    TAO/examples/Load_Balancing
//
// = FILENAME
//    Identity_Server.cpp
//
// = AUTHOR
//    Marina Spivak <marina@cs.wustl.edu>
//
// ============================================================================

#include "Identity_Server.h"
#include "Identity_i.h"
#include "tao/debug.h"
#include "ace/Get_Opt.h"

Identity_Server::Identity_Server (void)
  : group_factory_ior_ (0),
    random_objects_ (5),
    rr_objects_ (5)
{
}

int
Identity_Server::parse_args (int argc, char *argv[])
{
  ACE_Get_Opt get_opts (argc, argv, "di:a:o:");
  int c;

  while ((c = get_opts ()) != -1)
    switch (c)
      {
      case 'd':  // debug flag.
        TAO_debug_level++;
        break;
      case 'i': // ior of the <Object_Group_Factory> object.
        this->group_factory_ior_ = get_opts.optarg;
        break;
      case 'a': // number of objects to create/register with the random group.
        random_objects_ = ACE_OS::atoi (get_opts.optarg);
        break;
      case 'o': // number of objects to create/register with round
                //robin group.
        rr_objects_ = ACE_OS::atoi (get_opts.optarg);
        break;
      case '?':
      default:
        ACE_ERROR_RETURN ((LM_ERROR,
                           "usage:  %s"
                           " [-d]"
                           " [-i] <Object_Group_Factory_ior>"
                           " [-a] <number_of_objects_for_random_group>"
                           " [-o] <number_of_objects_for_rr_group>"
                           "\n",
                           argv [0]),
                          -1);
      }

  // Indicates successful parsing of command line.
  return 0;
}

int
Identity_Server::init (int argc,
                       char* argv[])
{
  int result;

  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {
      result = this->orb_manager_.init (argc,
                                        argv,
                                        ACE_TRY_ENV);
      ACE_TRY_CHECK;
      if (result == -1)
        return result;

      // Check the non-ORB arguments.
      result = this->parse_args (argc, argv);
      if (result < 0)
        return result;

      // Contact the <Object_Group_Factory> to create 2
      // <Object_Group>s, one random and one rr.
      CORBA::ORB_var orb = orb_manager_.orb ();
      CORBA::Object_var obj =
        orb->string_to_object (this->group_factory_ior_,
                               ACE_TRY_ENV);
      ACE_TRY_CHECK;
      Load_Balancer::Object_Group_Factory_var factory =
        Load_Balancer::Object_Group_Factory::_narrow (obj.in (),
                                                      ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (CORBA::is_nil (factory.in ()))
        ACE_ERROR_RETURN ((LM_ERROR,
                           "Identity_Server::init: "
                           "problems using the factory ior\n"),
                          -1);

      ACE_DEBUG ((LM_DEBUG,
                  "Identity_Server: Requesting new Random Object "
                  "Group with id <Identity, Random>\n"));

      Load_Balancer::Object_Group_var random_group =
        factory->make_random ("Identity, Random",
                              ACE_TRY_ENV);
      ACE_TRY_CHECK;

      ACE_DEBUG ((LM_DEBUG,
                  "Identity_Server: Requesting new Round Robin "
                  "Object Group with id <Identity, Round Robin>\n"));

      Load_Balancer::Object_Group_var rr_group =
        factory->make_round_robin ("Identity, Round Robin",
                                   ACE_TRY_ENV);
      ACE_TRY_CHECK;

      // Create the requested number of <Identity> objects, and
      // register them with the random and round robin
      // <Object_Group>s.

      ACE_DEBUG ((LM_DEBUG,
                  "Identity_Server: Registering %d object(s) "
                  "with <Identity, Random> Object Group\n",
                    random_objects_));
      create_objects (random_objects_,
                      random_group.in (),
                      ACE_TRY_ENV);
      ACE_TRY_CHECK;

      ACE_DEBUG ((LM_DEBUG,
                  "Identity_Server: Registering %d object(s) "
                  "with <Identity, Round Robin> Object Group\n",
                    random_objects_));
      create_objects (rr_objects_,
                      rr_group.in (),
                      ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Identity_Server::init");
      return -1;
    }
  ACE_ENDTRY;
  ACE_CHECK_RETURN (-1);

  return 0;
}

void
Identity_Server::create_objects (size_t number_of_objects,
                                 Load_Balancer::Object_Group_ptr group,
                                 CORBA::Environment &ACE_TRY_ENV)
{
  // Create the specified number of servants, and register each one
  // with the provided <Object_Group>.
  for (size_t i = 0; i < number_of_objects; ++i)
    {
      // Create an id for this servant.
      char id[BUFSIZ];
      ACE_OS::sprintf (id,
                       "Identity object " ACE_SIZE_T_FORMAT_SPECIFIER,
                       i);

      // Create and activate a servant.
      Identity_i * identity_servant;
      ACE_NEW_THROW_EX (identity_servant,
                        Identity_i (id),
                        CORBA::NO_MEMORY ());
      ACE_CHECK;
      PortableServer::ServantBase_var s = identity_servant;
      orb_manager_.activate (identity_servant,
                             ACE_TRY_ENV);
      ACE_CHECK;

      Load_Balancer::Member member;
      member.id = CORBA::string_dup (id);
      member.obj = identity_servant->_this (ACE_TRY_ENV);
      ACE_CHECK;

      // Bind the servant in the <Object_Group>.
      group->bind (member, ACE_TRY_ENV);
      ACE_CHECK;
    }
}

int
Identity_Server::run (CORBA::Environment &ACE_TRY_ENV)
{
  ACE_DEBUG ((LM_DEBUG,
              "Identity_Server: Initialized \n"));

  int result;

  result = this->orb_manager_.run (ACE_TRY_ENV);
  ACE_CHECK_RETURN (-1);

  return result;
}

Identity_Server::~Identity_Server (void)
{
}

int
main (int argc, char *argv[])
{
  int result = 0;
  Identity_Server server;

  if (server.init (argc, argv) == -1)
    return 1;

  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {
      result = server.run (ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Identity_Server");
      return 1;
    }
  ACE_ENDTRY;
  ACE_CHECK_RETURN (1);

  if (result == -1)
    return 1;
  else
    return 0;
}
