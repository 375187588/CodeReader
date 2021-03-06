//
// exceptlist_cs.cpp,v 1.5 2001/08/01 18:34:04 parsons Exp
//

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    exceptlist_cs.cpp
//
// = DESCRIPTION
//    Visitor generating code for the list of exceptions that an operation
//    raises.
//
// = AUTHOR
//    Aniruddha Gokhale
//
// ============================================================================

#include	"idl.h"
#include	"idl_extern.h"
#include	"be.h"

#include "be_visitor_operation.h"

ACE_RCSID(be_visitor_operation, exceptlist_cs, "exceptlist_cs.cpp,v 1.5 2001/08/01 18:34:04 parsons Exp")


// ****************************************************************************
// visitor to generate the exception list for operations
// ****************************************************************************

be_visitor_operation_exceptlist_cs::be_visitor_operation_exceptlist_cs (be_visitor_context
                                                            *ctx)
  : be_visitor_decl (ctx)
{
}

be_visitor_operation_exceptlist_cs::~be_visitor_operation_exceptlist_cs (void)
{
}

int
be_visitor_operation_exceptlist_cs::visit_operation (be_operation *node)
{
  TAO_OutStream *os = this->ctx_->stream ();

  // Don't do anything if the exception list is empty.
  if (node->exceptions ())
    {
      os->indent ();
      *os << "static TAO_Exception_Data " << "_tao_" << node->flat_name ()
          << "_exceptiondata [] = " << be_nl;
      *os << "{" << be_idt_nl;

      // Initialize an iterator to iterate thru the exception list.
      UTL_ExceptlistActiveIterator ei (node->exceptions ());

      AST_Decl *d = 0;

      // Continue until each element is visited.
      while (!ei.is_done ())
        {
          d = ei.item ();

          *os << "{" << be_idt_nl
              << "\"" << d->repoID () << "\"," << be_nl;
          // Allocator method.
          *os << d->name () << "::_alloc" << be_uidt_nl
              << "}";

          ei.next ();

          if (!ei.is_done ())
            {
              *os << "," << be_nl;
            }

        }

      *os << be_uidt_nl << "};\n\n";
    }

  return 0;
}
