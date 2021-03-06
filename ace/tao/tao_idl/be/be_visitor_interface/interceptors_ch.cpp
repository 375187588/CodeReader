//
// interceptors_ch.cpp,v 1.7 2001/04/03 18:05:54 coryan Exp
//
// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    interceptors_ch.cpp
//
// = DESCRIPTION
//    This provides code generation for interceptor classes for an
//    interface in the client header.
//
// = AUTHOR
//    Kirthika Parameswaran  <kirthika@cs.wustl.edu>
//
// ============================================================================

#include        "idl.h"
#include        "idl_extern.h"
#include        "be.h"

#include "be_visitor_interface.h"

ACE_RCSID(be_visitor_interface, interceptors_ch, "interceptors_ch.cpp,v 1.7 2001/04/03 18:05:54 coryan Exp")


// ************************************************************
//  interceptor class in header
// ************************************************************


be_visitor_interface_interceptors_ch::be_visitor_interface_interceptors_ch
(be_visitor_context *ctx)
  : be_visitor_interface (ctx)
{
}

be_visitor_interface_interceptors_ch::~be_visitor_interface_interceptors_ch (void)
{
}

int be_visitor_interface_interceptors_ch::visit_interface (be_interface *)
{
  return 0;
}
