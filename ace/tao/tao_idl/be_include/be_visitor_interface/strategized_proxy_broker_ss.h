//strategized_proxy_broker_ss.h,v 1.1 2000/11/20 06:50:32 corsaro Exp
//
// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    strategized_proxy_broker_cs.h
//
// = DESCRIPTION
//     Concrete visitor for the Interface node. This
//     visitor generates the declaration for the strategized
//     ProxyBroker class.
//
// = AUTHOR
//     Angelo Corsaro <corsaro@cs.wustl.edu>
//
// ============================================================================

#ifndef BE_STRATEGIZED_PROXY_BROKER_SS_H_
#define BE_STRATEGIZED_PROXY_BROKER_SS_H_

class be_visitor_interface_strategized_proxy_broker_ss : public be_visitor_interface
{
  // = TITLE
  //   Generates the implementation  for the base proxy
  //   broker class.

public:
  // -- Ctor/Dtor Decl. --
  be_visitor_interface_strategized_proxy_broker_ss (be_visitor_context *ctx);

  virtual ~be_visitor_interface_strategized_proxy_broker_ss (void);

  virtual int visit_interface (be_interface *node);
  // visit an interface

};

#endif /* BE_STRATEGIZED_PROXY_BROKER_SS_H_ */
