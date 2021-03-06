// Concurrency_Utils.cpp,v 1.4 1999/06/30 22:50:24 nanbor Exp

// ============================================================================
//
// = LIBRARY
//    TAO/orbsvcs/Concurrency_Service
//
// = FILENAME
//    Concurrency_Utils.cpp
//
// = AUTHOR
//    Torben Worm <tworm@cs.wustl.edu>
//
// ============================================================================

#include "ace/streams.h"
#include "orbsvcs/CosConcurrencyControlC.h"
#include "tao/corba.h"
#include "Concurrency_Utils.h"

ACE_RCSID(Concurrency, Concurrency_Utils, "Concurrency_Utils.cpp,v 1.4 1999/06/30 22:50:24 nanbor Exp")

// Default constructor

TAO_Concurrency_Server::TAO_Concurrency_Server (void)
{
}

// Constructor which takes an ORB and POA.

TAO_Concurrency_Server::TAO_Concurrency_Server (CORBA::ORB_var &orb,
						PortableServer::POA_var &poa)
{
  this->init (orb, poa);
}

// Function to initialize the concurrency server object under the
// passed orb and poa.

int
TAO_Concurrency_Server::init (CORBA::ORB_var &orb,
			      PortableServer::POA_var &poa)
{
  ACE_TRY_NEW_ENV
    {
      // @@ Huh?!?

      // Get the naming context ptr to NameService.
      //      ACE_TRY_CHECK;

      PortableServer::ObjectId_var id =
	PortableServer::string_to_ObjectId ("ConcurrencyService");

      poa->activate_object_with_id (id.in (),
                                    &lock_set_factory_,
                                    ACE_TRY_ENV);
      ACE_TRY_CHECK;

      // Stringify the objref we'll be implementing, and print it to
      // stdout.  Someone will take that string and give it to a
      // client.  Then release the object.
      CORBA::Object_var obj =
	poa->id_to_reference (id.in (),
                              ACE_TRY_ENV);
      ACE_TRY_CHECK;

      CORBA::String_var str =
	orb->object_to_string (obj.in (),
			       ACE_TRY_ENV);
      ACE_TRY_CHECK;

      ACE_DEBUG ((LM_DEBUG,
                  "listening as object <%s>\n",
                  str.in ()));
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                           "Concurrency Service");
    }
  ACE_ENDTRY;
  return 0;
}

// Get the lock set factory.

CC_LockSetFactory *
TAO_Concurrency_Server::GetLockSetFactory(void)
{
  return &this->lock_set_factory_;
}

// Destructor.

TAO_Concurrency_Server::~TAO_Concurrency_Server (void)
{
}
