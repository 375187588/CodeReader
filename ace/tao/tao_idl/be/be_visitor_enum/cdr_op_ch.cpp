//
// cdr_op_ch.cpp,v 1.5 2000/08/23 16:58:46 parsons Exp
//

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    cdr_op_ch.cpp
//
// = DESCRIPTION
//    Visitor generating code for Enums for the CDR operators
//
// = AUTHOR
//    Aniruddha Gokhale
//
// ============================================================================

#include	"idl.h"
#include	"idl_extern.h"
#include	"be.h"

#include "be_visitor_enum.h"

ACE_RCSID(be_visitor_enum, cdr_op_ch, "cdr_op_ch.cpp,v 1.5 2000/08/23 16:58:46 parsons Exp")


// ***************************************************************************
// Enum visitor for generating Cdr operator declarations in the client header
// ***************************************************************************

be_visitor_enum_cdr_op_ch::be_visitor_enum_cdr_op_ch
(be_visitor_context *ctx)
  : be_visitor_scope (ctx)
{
}

be_visitor_enum_cdr_op_ch::~be_visitor_enum_cdr_op_ch (void)
{
}

int
be_visitor_enum_cdr_op_ch::visit_enum (be_enum *node)
{
  if (node->cli_hdr_cdr_op_gen () || node->imported ())
    return 0;

  TAO_OutStream *os = this->ctx_->stream ();


  // generate the CDR << and >> operators
  os->indent ();
  *os << be_global->stub_export_macro () << " CORBA::Boolean"
      << " operator<< (TAO_OutputCDR &, const " << node->name ()
      << " &); // " << be_nl;
  *os << be_global->stub_export_macro () << " CORBA::Boolean"
      << " operator>> (TAO_InputCDR &, "
      << node->name () << " &);\n";

  node->cli_hdr_cdr_op_gen (1);
  return 0;
}
