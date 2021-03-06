// EC_Supplier_Filter.cpp,v 1.4 2000/02/01 19:33:04 coryan Exp

#include "EC_Supplier_Filter.h"
#include "EC_ProxySupplier.h"
#include "EC_QOS_Info.h"

#if ! defined (__ACE_INLINE__)
#include "EC_Supplier_Filter.i"
#endif /* __ACE_INLINE__ */

ACE_RCSID(Event, EC_Supplier_Filter, "EC_Supplier_Filter.cpp,v 1.4 2000/02/01 19:33:04 coryan Exp")

TAO_EC_Supplier_Filter::~TAO_EC_Supplier_Filter (void)
{
}

// ****************************************************************

void
TAO_EC_Filter_Worker::work (TAO_EC_ProxyPushSupplier *supplier,
                            CORBA::Environment &ACE_TRY_ENV)
{
  TAO_EC_QOS_Info qos_info = this->event_info_;
  supplier->filter (this->event_, qos_info, ACE_TRY_ENV);
}
