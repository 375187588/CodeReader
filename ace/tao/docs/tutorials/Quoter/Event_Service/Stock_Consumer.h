//
// Stock_Consumer.h,v 1.3 2000/04/19 17:58:35 coryan Exp
//

#ifndef TAO_TUTORIALS_QUOTER_EVENT_SERVICE_STOCK_CONSUMER_H
#define TAO_TUTORIALS_QUOTER_EVENT_SERVICE_STOCK_CONSUMER_H

#include <orbsvcs/CosEventCommS.h>
#include <orbsvcs/CosEventChannelAdminC.h>

class Stock_Consumer : public POA_CosEventComm::PushConsumer {
public:
  Stock_Consumer ();

  void connect (CosEventChannelAdmin::EventChannel_ptr event_channel);
  // Connect to the event channel, using <consumer_admin>

  void disconnect ();
  // Disconnect from the event channel.

  void push (const CORBA::Any& data, CORBA::Environment &)
    throw (CORBA::SystemException);
  void disconnect_push_consumer (CORBA::Environment &)
    throw (CORBA::SystemException);

private:
  CosEventChannelAdmin::ProxyPushSupplier_var supplier_proxy_;
  // The supplier proxy.
};

#endif /* TAO_TUTORIALS_QUOTER_EVENT_SERVICE_STOCK_CONSUMER_H */
