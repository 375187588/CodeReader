
//
// valuetype_obv_ch.cpp,v 1.5 2001/05/16 16:32:30 parsons Exp
//

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    valuetype_obv__ch.cpp
//
// = DESCRIPTION
//    Visitor generating code for Valuetypes in the client header
//    OBV_ class
//    (see C++ mapping OMG 20.17)
//
// = AUTHOR
//    Torsten Kuepper  <kuepper2@lfa.uni-wuppertal.de>,
//    based on interface_ch.cpp from Aniruddha Gokhale
//
// ============================================================================

#include        "idl.h"
#include        "idl_extern.h"
#include        "be.h"

#include "be_visitor_valuetype.h"

ACE_RCSID(be_visitor_valuetype_obv_ch, valuetype_obv_ch, "valuetype_obv_ch.cpp,v 1.5 2001/05/16 16:32:30 parsons Exp")


// ******************************************************
// Valuetype visitor for client header
// ******************************************************

be_visitor_valuetype_obv_ch::be_visitor_valuetype_obv_ch (be_visitor_context *ctx)
  : be_visitor_valuetype (ctx)
{
}

be_visitor_valuetype_obv_ch::~be_visitor_valuetype_obv_ch (void)
{
}


// OBV_ class must be in OBV_ namespace.
int
be_visitor_valuetype_obv_ch::visit_valuetype (be_valuetype *node)
{
  // Only visit non-abstract non-imported valuetype.
  if (node->is_abstract_valuetype () || node->imported ())
    {
      return 0;
    }

  TAO_OutStream *os = this->ctx_->stream ();

  // OBV_ class maps only to a typedef if we are optimizing accessors.
  if (node->opt_accessor ())
    {
      *os << "typedef " << node->full_name () << " ";

      if (!node->is_nested ())
        {
          *os << "OBV_";
        }

      *os << node->local_name () << ";" << be_nl;
    }
  else
    {
      // STEP 1: Generate the class name and the class name we inherit.
      os->gen_ifdef_macro (node->flat_name (), "_OBV");

      *os << "// OBV_ class" << be_nl;
      *os << "class ";

      if (!node->is_nested())
        {
          *os << "OBV_";
        }

      *os << node->local_name () << be_idt_nl
          << ": public virtual "
          << node->full_name () << be_uidt_nl;

      // STEP 2: Generate the body ==

      *os << "{" << be_nl;

      this->begin_public ();

      // Generate code for the OBV_ class definition.
      if (this->visit_valuetype_scope (node) == -1)
        {
          ACE_ERROR_RETURN ((LM_ERROR,
                             "(%N:%l) be_visitor_valuetype_obv_ch::"
                             "visit_valuetype - "
                             "codegen for scope failed\n"), 
                            -1);
        }

      // Map fields to private data.
      if (!node->opt_accessor ())
        {
          *os << be_uidt_nl << "protected:" << be_idt_nl;
          *os << "virtual CORBA::Boolean _tao_marshal__"
              <<    node->flat_name () << " (TAO_OutputCDR &);" << be_nl;
          *os << "virtual CORBA::Boolean _tao_unmarshal__"
              <<    node->flat_name () << " (TAO_InputCDR &);" << be_nl;
          *os << "CORBA::Boolean "
              << "_tao_marshal_state (TAO_OutputCDR &);" << be_nl
              << "CORBA::Boolean "
              << "_tao_unmarshal_state (TAO_InputCDR &);"
              << be_uidt_nl << be_nl;
          *os << "private:" << be_idt_nl;

          this->gen_pd (node);
        }

      *os << be_uidt_nl;
      *os << "};" << be_nl;

      os->gen_endif ();
    }

  return 0;
}


int
be_visitor_valuetype_obv_ch::visit_field (be_field *node)
{
  be_valuetype *vt = be_valuetype::narrow_from_scope (node->defined_in ());

  if (!vt)
    {
      return -1;
    }

  // Only in OBV_ class, if we are not optimizing accessors (and modifiers).
  if (!vt->opt_accessor ())
    {
      be_visitor_context* ctx = new be_visitor_context (*this->ctx_);
      ctx->state (TAO_CodeGen::TAO_FIELD_OBV_CH);
      be_visitor_valuetype_field_ch *visitor =
        new be_visitor_valuetype_field_ch (ctx);

      if (!visitor)
        {
          ACE_ERROR_RETURN ((LM_ERROR,
                             "be_visitor_valuetype_obv_ch::"
                             "visit_field - bad visitor\n"),
                            -1);
        }

      visitor->setenclosings ("virtual ",";");

      if (node->accept (visitor) == -1)
        {
          delete visitor;
          ACE_ERROR_RETURN ((LM_ERROR,
                             "(%N:%l) be_visitor_valuetype_obv_ch::"
                            "visit_field - codegen failed\n"),
                            -1);
        }

      delete visitor;
    }

  return 0;
}

void
be_visitor_valuetype_obv_ch::begin_public (void)
{
  TAO_OutStream *os = this->ctx_->stream ();
  *os << "public:" << be_idt_nl;
}

void
be_visitor_valuetype_obv_ch::begin_private (void)
{
  TAO_OutStream *os = this->ctx_->stream ();
  *os << be_uidt_nl;
  *os << "protected:" << be_idt_nl;
}
