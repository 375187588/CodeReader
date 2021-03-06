//
// Roundtrip_Handler.cpp,v 1.1 2001/05/09 22:38:19 coryan Exp
//
#include "Roundtrip_Handler.h"

ACE_RCSID(AMI_Latency, Roundtrip, "Roundtrip_Handler.cpp,v 1.1 2001/05/09 22:38:19 coryan Exp")

Roundtrip_Handler::Roundtrip_Handler (int expected_callbacks)
  : pending_callbacks_ (expected_callbacks)
{
}

int
Roundtrip_Handler::pending_callbacks (void) const
{
  return this->pending_callbacks_;
}

void
Roundtrip_Handler::dump_results (ACE_UINT32 gsf)
{
  this->latency_stats_.dump_results ("AMI Latency", gsf);
}

void
Roundtrip_Handler::test_method (Test::Timestamp send_time,
                                CORBA::Environment &)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  this->pending_callbacks_--;

  ACE_hrtime_t now = ACE_OS::gethrtime ();
  this->latency_stats_.sample (now - send_time);
}

void
Roundtrip_Handler::test_method_excep (Test::AMI_RoundtripExceptionHolder *holder,
                                      CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  ACE_TRY
    {
      this->pending_callbacks_--;
      holder->raise_test_method (ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "test_method:");
    }
  ACE_ENDTRY;
}

void
Roundtrip_Handler::shutdown (CORBA::Environment &)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
}

void
Roundtrip_Handler::shutdown_excep (Test::AMI_RoundtripExceptionHolder *holder,
                                   CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  ACE_TRY
    {
      holder->raise_shutdown (ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "shutdown:");
    }
  ACE_ENDTRY;
}
