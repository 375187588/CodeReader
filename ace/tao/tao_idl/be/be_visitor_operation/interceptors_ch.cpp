//
// interceptors_ch.cpp,v 1.14 2001/04/03 18:05:54 coryan Exp
//

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    operation_interceptors_ch.cpp
//
// = DESCRIPTION
//    Visitor generating code for Operation node in the client header.
//
// = AUTHOR
//    Kirthika Parameswaran  <kirthika@cs.wustl.edu>
//
// ============================================================================

#include        "idl.h"
#include        "idl_extern.h"
#include        "be.h"

#include "be_visitor_operation.h"

ACE_RCSID(be_visitor_operation, operation_interceptors_ch, "interceptors_ch.cpp,v 1.14 2001/04/03 18:05:54 coryan Exp")


  // ******************************************************
  // primary visitor for "operation" in client header
  // ******************************************************

be_visitor_operation_interceptors_ch::be_visitor_operation_interceptors_ch (
    be_visitor_context *ctx
  )
  : be_visitor_operation (ctx)
{
}

be_visitor_operation_interceptors_ch::~be_visitor_operation_interceptors_ch (
    void
  )
{
}

int
be_visitor_operation_interceptors_ch::visit_operation (be_operation *)
{
  return 0;
}
