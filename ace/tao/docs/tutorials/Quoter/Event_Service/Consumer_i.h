//
// Consumer_i.h,v 1.2 2000/04/19 17:58:35 coryan Exp
//

#ifndef TAO_TUTORIALS_QUOTER_EVENT_SERVICE_CONSUMER_I_H
#define TAO_TUTORIALS_QUOTER_EVENT_SERVICE_CONSUMER_I_H

#include <orbsvcs/CosEventCommS.h>
#include <orbsvcs/CosEventChanneAdminC.h>

class Stock_Consumer : public POA_CosEventComm::PushConsumer {
public:
  Stock_Consumer ();

  void connect (CosEventChanneAdmin::ConsumerAdmin_ptr consumer_admin);

  void push (const CORBA::Any& data, CORBA::Environment &);
  void disconnect_push_consumer (CORBA::Environment &);

private:
};

#endif /* TAO_TUTORIALS_QUOTER_EVENT_SERVICE_CONSUMER_I_H */
