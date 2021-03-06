//
// ctor_assign.cpp,v 1.8 2000/09/29 16:19:16 parsons Exp
//

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    ctor_assign.cpp
//
// = DESCRIPTION
//    Visitor generating code for the special CTOR and assignment operator for
//    Exceptions.
//
// = AUTHOR
//    Aniruddha Gokhale
//
// ============================================================================

#include "idl.h"
#include "idl_extern.h"
#include "be.h"
#include "be_visitor_exception.h"

ACE_RCSID(be_visitor_exception, ctor_assign, "ctor_assign.cpp,v 1.8 2000/09/29 16:19:16 parsons Exp")


// ************************************************************************
// Used for the body of the assignment operator and the copy constructor.
// ************************************************************************

be_visitor_exception_ctor_assign::be_visitor_exception_ctor_assign (
    be_visitor_context *ctx
  )
  : be_visitor_scope (ctx)
{
}

be_visitor_exception_ctor_assign::~be_visitor_exception_ctor_assign (void)
{
}

int 
be_visitor_exception_ctor_assign::visit_exception (be_exception *node)
{
  // Save the argument node.
  this->ctx_->node (node);

  if (this->visit_scope (node) == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "be_visitor_exception_ctor_assign::"
                         "visit_exception - "
                         "codegen for scope failed\n"),
                        -1);
    }

  return 0;
}

int 
be_visitor_exception_ctor_assign::visit_field (be_field *node)
{
  // Save the argument node.
  this->ctx_->node (node);

  // Retrieve the type.
  be_type *bt = be_type::narrow_from_decl (node->field_type ());

  if (!bt)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "be_visitor_exception_ctor_assign::"
                         "visit_field - "
                         "Bad field type\n"),
                        -1);
    }

  // Different types have different mappings when used as in/out or
  // inout parameters. Let this visitor deal with the type.

  if (bt->accept (this) == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "be_visitor_exception_ctor_assign::"
                         "visit_field - "
                         "cannot accept visitor\n"),
                        -1);
    }

  return 0;
}

int 
be_visitor_exception_ctor_assign::visit_array (be_array *node)
{
  TAO_OutStream *os = this->ctx_->stream ();
  be_decl *bd = this->ctx_->node ();

  os->indent ();

  if (ACE_OS::strcmp (bd->flat_name (), node->flat_name ()) != 0)
    {
      // We are typedef'd.
      *os << node->name ();
    }
  else
    {
      // We are anonymous.
      *os << "_" << bd->local_name ();
    }

  if (this->ctx_->exception ())
    {
      // Constructor from member args.
      *os << "_copy (this->" << bd->local_name ()
          << ", _tao_" << bd->local_name () << ");\n";
    }
  else
    {
      // Copy constructor and assignment operator.
      *os << "_copy (this->" << bd->local_name ()
          << ", _tao_excp." << bd->local_name () << ");\n";
    }

  return 0;
}

int 
be_visitor_exception_ctor_assign::visit_enum (be_enum *)
{
  TAO_OutStream *os = this->ctx_->stream ();
  be_decl *bd = this->ctx_->node ();

  os->indent ();

  if (this->ctx_->exception ()) // Special constructor.
    {
      *os << "this->" << bd->local_name () << " = _tao_" 
          << bd->local_name () << ";\n";
    }
  else
    {
      *os << "this->" << bd->local_name () << " = _tao_excp." 
          << bd->local_name () << ";\n";
    }

  return 0;
}

int 
be_visitor_exception_ctor_assign::visit_interface (be_interface *node)
{
  TAO_OutStream *os = this->ctx_->stream ();
  be_decl *bd = this->ctx_->node ();

  os->indent ();

  if (this->ctx_->exception ()) // Special constructor.
    {
      *os << "this->" << bd->local_name () << " = " << node->name ()
          << "::_duplicate (_tao_" << bd->local_name () << ");\n";
    }
  else
    {
      *os << "this->" << bd->local_name () << " = " << node->name ()
          << "::_duplicate (_tao_excp." << bd->local_name () << ".in ());\n";
    }

  return 0;
}

int be_visitor_exception_ctor_assign::visit_interface_fwd (
    be_interface_fwd *node
  )
{
  TAO_OutStream *os = this->ctx_->stream ();
  be_decl *bd = this->ctx_->node ();

  os->indent ();

  if (this->ctx_->exception ()) // Special constructor.
    {
      *os << "this->" << bd->local_name () << " = " << node->name ()
          << "::_duplicate (_tao_" << bd->local_name () << ");\n";
    }
  else
    {
      *os << "this->" << bd->local_name () << " = " << node->name ()
          << "::_duplicate (_tao_excp." << bd->local_name () << ".in ());\n";
    }
  return 0;
}

int be_visitor_exception_ctor_assign::visit_predefined_type (
    be_predefined_type *node
  )
{
  TAO_OutStream *os = this->ctx_->stream ();
  be_decl *bd = this->ctx_->node ();

  os->indent ();

  // Check if the type is an any.
  if (node->pt () == AST_PredefinedType::PT_any)
    {
      if (this->ctx_->exception ()) // Special constructor.
        {
          *os << "this->" << bd->local_name () << " = _tao_"
              << bd->local_name () << ";\n";
        }
      else
        {
          *os << "this->" << bd->local_name () << " = _tao_excp."
              << bd->local_name () << ";\n";
        }
    }
  else if (node->pt () == AST_PredefinedType::PT_pseudo)
    {
      if (this->ctx_->exception ()) // Special constructor.
        {
          *os << "this->" << bd->local_name () << " = "
              << node->name () << "::_duplicate (_tao_"
              << bd->local_name () << ");\n";
        }
      else
        {
          *os << "this->" << bd->local_name () << " = "
              << node->name () << "::_duplicate (_tao_excp."
              << bd->local_name () << ".in ());\n";
        }
    }
  else // Simple predefined types.
    {
      if (this->ctx_->exception ()) // Special constructor.
        {
          *os << "this->" << bd->local_name () << " = _tao_"
              << bd->local_name () << ";\n";
        }
      else
        {
          *os << "this->" << bd->local_name () << " = _tao_excp."
              << bd->local_name () << ";\n";
        }
    }

  return 0;
}

int be_visitor_exception_ctor_assign::visit_sequence (be_sequence *)
{
  TAO_OutStream *os = this->ctx_->stream ();
  be_decl *bd = this->ctx_->node ();

  os->indent ();

  if (this->ctx_->exception ()) // Special constructor.
    {
      *os << "this->" << bd->local_name () << " = _tao_" << bd->local_name ()
          << ";\n";
    }
  else
    {
      *os << "this->" << bd->local_name () << " = _tao_excp." 
          << bd->local_name () << ";\n";
    }

  return 0;
}

int be_visitor_exception_ctor_assign::visit_string (be_string *node)
{
  TAO_OutStream *os = this->ctx_->stream ();
  be_decl *bd = this->ctx_->node ();

  os->indent ();

  if (this->ctx_->exception ()) // Special constructor.
    {
      if (node->width () == (long) sizeof (char))
        {
          *os << "this->" << bd->local_name () 
              << " = CORBA::string_dup (_tao_"
              << bd->local_name () << ");\n";
        }
      else
        {
          *os << "this->" << bd->local_name () 
              << " = CORBA::wstring_dup (_tao_"
              << bd->local_name () << ");\n";
        }
    }
  else
    {
      if (node->width () == (long) sizeof (char))
        {
          *os << "this->" << bd->local_name ()
              << " = CORBA::string_dup (_tao_excp." 
              << bd->local_name () << ".in ());\n";
        }
      else
        {
          *os << "this->" << bd->local_name ()
              << " = CORBA::wstring_dup (_tao_excp." 
              << bd->local_name () << ".in ());\n";
        }
    }

  return 0;
}

int be_visitor_exception_ctor_assign::visit_structure (be_structure *)
{
  TAO_OutStream *os = this->ctx_->stream ();
  be_decl *bd = this->ctx_->node ();

  os->indent ();

  if (this->ctx_->exception ()) // Special constructor.
    {
      *os << "this->" << bd->local_name () << " = _tao_" << bd->local_name ()
          << ";\n";
    }
  else
    {
      *os << "this->" << bd->local_name () << " = _tao_excp." 
          << bd->local_name () << ";\n";
    }

  return 0;
}

int be_visitor_exception_ctor_assign::visit_union (be_union *)
{
  TAO_OutStream *os = this->ctx_->stream ();
  be_decl *bd = this->ctx_->node ();

  os->indent ();

  if (this->ctx_->exception ()) // Special constructor.
    {
      *os << "this->" << bd->local_name () << " = _tao_" << bd->local_name ()
          << ";\n";
    }
  else
    {
      *os << "this->" << bd->local_name () << " = _tao_excp." 
          << bd->local_name () << ";\n";
    }

  return 0;
}

int be_visitor_exception_ctor_assign::visit_typedef (be_typedef *node)
{
  this->ctx_->alias (node);

  if (node->primitive_base_type ()->accept (this) == -1)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         "be_visitor_exception_ctor_assign::"
                         "visit_typedef - "
                         "accept on primitive type failed\n"),
                        -1);
    }

  this->ctx_->alias (0);
  return 0;
}
