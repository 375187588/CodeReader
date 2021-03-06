// Counting_Supplier.cpp,v 1.3 2001/02/02 02:31:52 fhunleth Exp

#include "Counting_Supplier.h"

ACE_RCSID(CEC_Tests, CEC_Count_Supplier, "Counting_Supplier.cpp,v 1.3 2001/02/02 02:31:52 fhunleth Exp")

CEC_Counting_Supplier::CEC_Counting_Supplier (void)
  :  event_count (0),
     disconnect_count (0)
{
}

void
CEC_Counting_Supplier::connect (
    CosEventChannelAdmin::SupplierAdmin_ptr supplier_admin,
    CORBA::Environment &ACE_TRY_ENV)
{
  CosEventComm::PushSupplier_var supplier =
    this->_this (ACE_TRY_ENV);
  ACE_CHECK;

  if (CORBA::is_nil (this->consumer_proxy_.in ()))
    {
      this->consumer_proxy_ =
        supplier_admin->obtain_push_consumer (ACE_TRY_ENV);
      ACE_CHECK;
    }

  this->consumer_proxy_->connect_push_supplier (supplier.in (),
                                                ACE_TRY_ENV);
  ACE_CHECK;
}

void
CEC_Counting_Supplier::disconnect (CORBA::Environment &ACE_TRY_ENV)
{
  if (!CORBA::is_nil (this->consumer_proxy_.in ()))
    {
      this->consumer_proxy_->disconnect_push_consumer (ACE_TRY_ENV);
      ACE_CHECK;
    }

  PortableServer::POA_var supplier_poa =
    this->_default_POA (ACE_TRY_ENV);
  ACE_CHECK;
  PortableServer::ObjectId_var supplier_id =
    supplier_poa->servant_to_id (this, ACE_TRY_ENV);
  ACE_CHECK;
  supplier_poa->deactivate_object (supplier_id.in (), ACE_TRY_ENV);
  ACE_CHECK;

  this->consumer_proxy_ =
    CosEventChannelAdmin::ProxyPushConsumer::_nil ();
}

void
CEC_Counting_Supplier::push (const CORBA::Any&,
                CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  if (CORBA::is_nil (this->consumer_proxy_.in ()))
    return;

  CORBA::Any event;
  event <<= CORBA::Long(0);

  this->consumer_proxy_->push (event, ACE_TRY_ENV);
  ACE_CHECK;
  this->event_count++;
}

void
CEC_Counting_Supplier::disconnect_push_supplier (CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  this->disconnect_count++;
  this->consumer_proxy_ =
    CosEventChannelAdmin::ProxyPushConsumer::_nil ();
}

// ****************************************************************

CEC_Counting_Supplier_Task::
    CEC_Counting_Supplier_Task (CEC_Counting_Supplier *s,
                                int milliseconds)
  :  supplier_ (s),
     stop_flag_ (0),
     push_count_ (0),
     milliseconds_ (milliseconds)
{
}

int
CEC_Counting_Supplier_Task::svc ()
{
  ACE_TRY_NEW_ENV
    {
      this->run (ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      return -1;
    }
  ACE_ENDTRY;
  return 0;
}

void
CEC_Counting_Supplier_Task::stop (void)
{
  ACE_GUARD (TAO_SYNCH_MUTEX, ace_mon, this->lock_);
  this->stop_flag_ = 1;
}

CORBA::ULong
CEC_Counting_Supplier_Task::push_count (void)
{
  return this->push_count_;
}

void
CEC_Counting_Supplier_Task::run (CORBA::Environment &ACE_TRY_ENV)
{
  CORBA::Any event;
  event <<= CORBA::Long(0);

  int stop = 0;
  do {
    this->supplier_->push (event, ACE_TRY_ENV);
    ACE_CHECK;

    if (this->milliseconds_ != 0)
      {
        ACE_Time_Value tv (0, 1000 * this->milliseconds_);
        ACE_OS::sleep (tv);
      }
    else
      {
        // Sleep for a short time to avoid spinning... kind of klugy
        ACE_OS::sleep (0);
      }

    ACE_GUARD (TAO_SYNCH_MUTEX, ace_mon, this->lock_);

    this->push_count_++;

    stop = this->stop_flag_;
  } while (stop == 0);
}

// ****************************************************************

CEC_Pull_Counting_Supplier::CEC_Pull_Counting_Supplier (void)
  :  event_count (0),
     disconnect_count (0)
{
}

void
CEC_Pull_Counting_Supplier::connect (
    CosEventChannelAdmin::SupplierAdmin_ptr supplier_admin,
    CORBA::Environment &ACE_TRY_ENV)
{
  CosEventComm::PullSupplier_var supplier =
    this->_this (ACE_TRY_ENV);
  ACE_CHECK;

  if (CORBA::is_nil (this->consumer_proxy_.in ()))
    {
      this->consumer_proxy_ =
        supplier_admin->obtain_pull_consumer (ACE_TRY_ENV);
      ACE_CHECK;
    }

  this->consumer_proxy_->connect_pull_supplier (supplier.in (),
                                                ACE_TRY_ENV);
  ACE_CHECK;
}

void
CEC_Pull_Counting_Supplier::disconnect (CORBA::Environment &ACE_TRY_ENV)
{
  if (!CORBA::is_nil (this->consumer_proxy_.in ()))
    {
      this->consumer_proxy_->disconnect_pull_consumer (ACE_TRY_ENV);
      ACE_CHECK;
    }

  PortableServer::POA_var supplier_poa =
    this->_default_POA (ACE_TRY_ENV);
  ACE_CHECK;
  PortableServer::ObjectId_var supplier_id =
    supplier_poa->servant_to_id (this, ACE_TRY_ENV);
  ACE_CHECK;
  supplier_poa->deactivate_object (supplier_id.in (), ACE_TRY_ENV);
  ACE_CHECK;

  this->consumer_proxy_ =
    CosEventChannelAdmin::ProxyPullConsumer::_nil ();
}

CORBA::Any*
CEC_Pull_Counting_Supplier::pull (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException,CosEventComm::Disconnected))
{
  if (CORBA::is_nil (this->consumer_proxy_.in ()))
    ACE_THROW_RETURN (CosEventComm::Disconnected (), 0);

  if (this->event_count % 2)
    {
      // Sleep for 1 second, to simulate blocking calls.
      ACE_OS::sleep (1);
    }

  this->event_count++;
  CORBA::Any event;
  event <<= CORBA::Long(0);

  return new CORBA::Any (event);
}

CORBA::Any*
CEC_Pull_Counting_Supplier::try_pull (CORBA::Boolean_out has_event,
                                      CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException,CosEventComm::Disconnected))
{
  if (CORBA::is_nil (this->consumer_proxy_.in ()))
    ACE_THROW_RETURN (CosEventComm::Disconnected (), 0);

  if (this->event_count % 2)
    {
      // No event
      has_event = 0;
    }
  else
    {
      // We have an event
      has_event = 1;
      this->event_count++;
   }

  CORBA::Any event;
  event <<= CORBA::Long(0);

  return new CORBA::Any (event);
}

void
CEC_Pull_Counting_Supplier::disconnect_pull_supplier (CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  this->disconnect_count++;
  this->consumer_proxy_ =
    CosEventChannelAdmin::ProxyPullConsumer::_nil ();
}



#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)

#elif defined(ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)

#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */
