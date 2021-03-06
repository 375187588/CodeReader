/* -*- C++ -*- */
//=============================================================================
/**
 *  @file   CEC_EventChannel.h
 *
 *  CEC_EventChannel.h,v 1.8 2001/09/18 17:52:23 coryan Exp
 *
 *  @author Carlos O'Ryan (coryan@cs.wustl.edu)
 *
 * A new implementation of the COS Event Channel.
 * This version does not rely on the RTEC in its implementation.
 *
 *
 */
//=============================================================================


#ifndef TAO_CEC_EVENTCHANNEL_H
#define TAO_CEC_EVENTCHANNEL_H
#include "ace/pre.h"

#include "CEC_Factory.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "orbsvcs/CosEventChannelAdminS.h"
#include "CEC_Defaults.h"
#include "event_export.h"

/**
 * @class TAO_CEC_EventChannel_Attributes
 *
 * @brief Defines the construction time attributes for the Event
 * Channel.
 *
 * The event channel implementation is controlled by two
 * mechanisms:
 * The CEC_Factory that provides the strategies for the EC
 * implementation.
 * The EC attributes that define constants and values required
 * by the EC construction.
 * This class encapsulates those constants and values, providing
 * an easy mechanism to extend the attributes without requiring
 * changes in the EC constructor.
 */
class TAO_Event_Export TAO_CEC_EventChannel_Attributes
{
public:
  /**
   * The basic constructor.
   * The attributes listed as arguments are *required* by the EC, and
   * no appropiate defaults are available for them.
   */
  TAO_CEC_EventChannel_Attributes (PortableServer::POA_ptr supplier_poa,
                                   PortableServer::POA_ptr consumer_poa);

  // Most fields are public, there is no need to protect them, in fact
  // the user should be able to set any values she wants.

  /// Can consumers or suppliers invoke connect_push_* multiple times?
  int consumer_reconnect;
  int supplier_reconnect;

  /**
   * It not zero the event channel will send disconnect callbacks when
   * a disconnect method is called on a Proxy.  In other words, if a
   * consumer calls disconnect_push_supplier() on its proxy the EC
   * will invoke disconnect_push_consumer() on the consumer.  A
   * similar thing is done for suppliers.
   * It is a matter of debate what the spec requires for the regular
   * event service.
   */
  int disconnect_callbacks;

  /// Flags for the Consumer Admin
  int busy_hwm;
  int max_write_delay;

private:
  /// Only the EC can read the private fields.
  friend class TAO_CEC_EventChannel;

  /// The POAs
  PortableServer::POA_ptr supplier_poa;
  PortableServer::POA_ptr consumer_poa;
};

/**
 * @class TAO_CEC_EventChannel
 *
 * @brief The CosEventChannelAdmin::EventChannel implementation.
 *
 * This class is the Mediator between all the classes in the EC
 * implementation, its main task is to redirect the messages to
 * the right components, to hold and manage the lifetime of the
 * long lived objects (Timer_Module, SupplierAdmin,
 * ConsumerAdmin and Dispatching) and to provide a simpler
 * interface to the CEC_Factory.
 */
class TAO_Event_Export TAO_CEC_EventChannel : public POA_CosEventChannelAdmin::EventChannel
{
public:
  /**
   * constructor
   * If <own_factory> is not 0 it assumes ownership of the factory.
   * If the factory is <nil> it uses the Service_Configurator to load
   * the Factory, if not found it uses TAO_CEC_Default_Resource_Factory
   */
  TAO_CEC_EventChannel (const TAO_CEC_EventChannel_Attributes& attributes,
                        TAO_CEC_Factory* factory = 0,
                        int own_factory = 0);

  /// destructor
  virtual ~TAO_CEC_EventChannel (void);

  /// Start the internal threads (if any), etc.
  /// After this call the EC can be used.
  virtual void activate (CORBA::Environment &env = TAO_default_environment ());

  /// Shutdown any internal threads, cleanup all the internal
  /// structures, flush all the messages, etc.
  virtual void shutdown (CORBA::Environment &env = TAO_default_environment ());

  /// Access the dispatching module....
  TAO_CEC_Dispatching* dispatching (void) const;

  /// Access the consumer admin implementation.
  TAO_CEC_ConsumerAdmin* consumer_admin (void) const;

  /// Access the supplier admin implementation.
  TAO_CEC_SupplierAdmin* supplier_admin (void) const;

  /// Access the consumer control strategy.
  TAO_CEC_ConsumerControl* consumer_control (void) const;

  /// Access the supplier control strategy.
  TAO_CEC_SupplierControl* supplier_control (void) const;

  // = The factory methods, they delegate on the CEC_Factory.
  /// Create and destroy a ProxyPushSupplier
  void create_proxy (TAO_CEC_ProxyPushSupplier*&);
  void destroy_proxy (TAO_CEC_ProxyPushSupplier*);

  /// Create and destroy a ProxyPullSupplier
  void create_proxy (TAO_CEC_ProxyPullSupplier*&);
  void destroy_proxy (TAO_CEC_ProxyPullSupplier*);

  /// Create and destroy a ProxyPushConsumer
  void create_proxy (TAO_CEC_ProxyPushConsumer*&);
  void destroy_proxy (TAO_CEC_ProxyPushConsumer*);

  /// Create and destroy a ProxyPushConsumer
  void create_proxy (TAO_CEC_ProxyPullConsumer*&);
  void destroy_proxy (TAO_CEC_ProxyPullConsumer*);

  /// Create and destroy a the collections used to store
  /// Proxy*Suppliers
  void create_proxy_collection (TAO_CEC_ProxyPushSupplier_Collection*&);
  void destroy_proxy_collection (TAO_CEC_ProxyPushSupplier_Collection*);
  void create_proxy_collection (TAO_CEC_ProxyPullSupplier_Collection*&);
  void destroy_proxy_collection (TAO_CEC_ProxyPullSupplier_Collection*);

  /// Create and destroy a the collections used to store
  /// Proxy*Consumers
  void create_proxy_collection (TAO_CEC_ProxyPushConsumer_Collection*&);
  void destroy_proxy_collection (TAO_CEC_ProxyPushConsumer_Collection*);
  void create_proxy_collection (TAO_CEC_ProxyPullConsumer_Collection*&);
  void destroy_proxy_collection (TAO_CEC_ProxyPullConsumer_Collection*);

  /// Access the supplier and consumer POAs from the factory.
  PortableServer::POA_ptr supplier_poa (void);
  PortableServer::POA_ptr consumer_poa (void);

  /// Locking strategies for the ProxyPushConsumer and
  /// ProxyPushSupplier objects
  ACE_Lock* create_consumer_lock (void);
  void destroy_consumer_lock (ACE_Lock*);
  ACE_Lock* create_supplier_lock (void);
  void destroy_supplier_lock (ACE_Lock*);

  /// Used to inform the EC that a Consumer has connected or
  /// disconnected from it.
  virtual void connected (TAO_CEC_ProxyPushConsumer*,
                          CORBA::Environment&);
  virtual void reconnected (TAO_CEC_ProxyPushConsumer*,
                            CORBA::Environment&);
  virtual void disconnected (TAO_CEC_ProxyPushConsumer*,
                             CORBA::Environment&);
  virtual void connected (TAO_CEC_ProxyPullConsumer*,
                          CORBA::Environment&);
  virtual void reconnected (TAO_CEC_ProxyPullConsumer*,
                            CORBA::Environment&);
  virtual void disconnected (TAO_CEC_ProxyPullConsumer*,
                             CORBA::Environment&);

  /// Used to inform the EC that a Supplier has connected or
  /// disconnected from it.
  virtual void connected (TAO_CEC_ProxyPushSupplier*,
                          CORBA::Environment&);
  virtual void reconnected (TAO_CEC_ProxyPushSupplier*,
                            CORBA::Environment&);
  virtual void disconnected (TAO_CEC_ProxyPushSupplier*,
                             CORBA::Environment&);
  virtual void connected (TAO_CEC_ProxyPullSupplier*,
                          CORBA::Environment&);
  virtual void reconnected (TAO_CEC_ProxyPullSupplier*,
                            CORBA::Environment&);
  virtual void disconnected (TAO_CEC_ProxyPullSupplier*,
                             CORBA::Environment&);

  // Simple flags to control the EC behavior, set by the application
  // at construction time.

  /// Can the consumers reconnect to the EC?
  int consumer_reconnect (void) const;

  /// Can the suppliers reconnect to the EC?
  int supplier_reconnect (void) const;

  /// Should we send callback disconnect messages when a proxy is
  /// disconnected by the client
  int disconnect_callbacks (void) const;

  /// Control the concurrency of the delayed connect/disconnect
  /// operations.
  int busy_hwm (void) const;
  int max_write_delay (void) const;

  // = The CosEventChannelAdmin::EventChannel methods...
  /// The default implementation is:
  ///    this->consumer_admin ()->_this (env);
  virtual CosEventChannelAdmin::ConsumerAdmin_ptr
      for_consumers (CORBA::Environment& env)
        ACE_THROW_SPEC ((CORBA::SystemException));

  /// The default implementation is:
  ///    this->supplier_admin ()->_this (env);
  virtual CosEventChannelAdmin::SupplierAdmin_ptr
      for_suppliers (CORBA::Environment& env)
        ACE_THROW_SPEC ((CORBA::SystemException));

  /// Commit suicide.
  virtual void destroy (CORBA::Environment &env)
    ACE_THROW_SPEC ((CORBA::SystemException));

private:
  /// The POAs used to activate "supplier-side" and "consumer-side"
  /// objects.
  PortableServer::POA_var supplier_poa_;
  PortableServer::POA_var consumer_poa_;

  /**
   * This is the abstract factory that creates all the objects that
   * compose an event channel, the event channel simply acts as a
   * Mediator among them.
   */
  TAO_CEC_Factory *factory_;

  /// Flag that indicates if we own the factory.
  int own_factory_;

  /// The dispatching "module"
  TAO_CEC_Dispatching *dispatching_;

  /// The pulling strategy
  TAO_CEC_Pulling_Strategy *pulling_strategy_;

  /// The ConsumerAdmin implementation
  TAO_CEC_ConsumerAdmin *consumer_admin_;

  /// The SupplierAdmin implementation
  TAO_CEC_SupplierAdmin *supplier_admin_;

  /// Consumer/Supplier reconnection flags
  int consumer_reconnect_;
  int supplier_reconnect_;

  /// If not zero we send callbacks when a proxy is disconnected
  int disconnect_callbacks_;

  /// Control the level of concurrency in the supplier sets with
  /// delayed operations
  int busy_hwm_;
  int max_write_delay_;

  /// Strategies to disconnect misbehaving or destroyed consumers and
  /// suppliers
  TAO_CEC_ConsumerControl *consumer_control_;
  TAO_CEC_SupplierControl *supplier_control_;
};

#if defined (__ACE_INLINE__)
#include "CEC_EventChannel.i"
#endif /* __ACE_INLINE__ */

#include "ace/post.h"
#endif /* TAO_CEC_EVENT_CHANNEL_H */
