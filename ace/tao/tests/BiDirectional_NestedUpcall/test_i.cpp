// test_i.cpp,v 1.9 2001/09/18 00:05:59 irfan Exp

#include "test_i.h"
#include "tao/ORB_Core.h"
#include "tao/debug.h"
#include "tao/Transport_Cache_Manager.h"
#include "tao/Thread_Lane_Resources.h"

#if !defined(__ACE_INLINE__)
#include "test_i.i"
#endif /* __ACE_INLINE__ */

ACE_RCSID(BiDirectional_NestedUpcall, test_i, "test_i.cpp,v 1.9 2001/09/18 00:05:59 irfan Exp")

void
Callback_i::shutdown (CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  ACE_DEBUG ((LM_DEBUG, "Performing clean shutdown\n"));
  this->orb_->shutdown (0, ACE_TRY_ENV);
}

void
Callback_i::callback_method (CORBA::Environment & /*ACE_TRY_ENV*/)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  if (TAO_debug_level > 0)
    ACE_DEBUG ((LM_DEBUG, "Callback method called \n"));
}


// ****************************************************************

CORBA::Long
Simple_Server_i::test_method (CORBA::Boolean do_callback,
                              CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  if (do_callback)
    {
      if (TAO_debug_level > 0)
      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("About to make a remote call in the Upcall \n")));

      for (int times = 0;
           times < this->no_iterations_;
           ++times)
        {
          this->callback_->callback_method (ACE_TRY_ENV);
          ACE_CHECK_RETURN (0);

          if (this->orb_->orb_core ()->lane_resources ().transport_cache ().current_size () > 1)
            {
              ACE_ERROR ((LM_ERROR,
                          "(%P|%t) The cache has grown, aborting ..\n"));

              ACE_OS::abort ();
            }
        }
    }

  return 0;
}

void
Simple_Server_i::callback_object (Callback_ptr callback,
                                  CORBA::Environment& )
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  // Store the callback object
  this->callback_ = Callback::_duplicate (callback);
}


void
Simple_Server_i::shutdown (CORBA::Environment& ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  this->orb_->shutdown (0, ACE_TRY_ENV);
}
