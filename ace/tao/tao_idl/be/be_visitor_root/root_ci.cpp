//
// root_ci.cpp,v 1.3 2000/08/23 16:58:47 parsons Exp
//

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    root_ci.cpp
//
// = DESCRIPTION
//    Visitor generating code for the Root in the client inline
//
// = AUTHOR
//    Aniruddha Gokhale
//
// ============================================================================

#include	"idl.h"
#include	"idl_extern.h"
#include	"be.h"

#include "be_visitor_root.h"

ACE_RCSID(be_visitor_root, root_ci, "root_ci.cpp,v 1.3 2000/08/23 16:58:47 parsons Exp")


// *********************************
// Root visitor for client inline
// *********************************

be_visitor_root_ci::be_visitor_root_ci (be_visitor_context *ctx)
  : be_visitor_root (ctx)
{
}

be_visitor_root_ci::~be_visitor_root_ci (void)
{
}

int
be_visitor_root_ci::init (void)
{
  // first open the client-side inline file for writing
  if (tao_cg->start_client_inline (be_global->be_get_client_inline_fname ())
        == -1)
    {
      ACE_ERROR ((LM_ERROR,
                  "(%N:%l) be_visitor_root_ci - "
                  "Error opening client inline file\n"));
      return -1;
    }

  this->ctx_->stream (tao_cg->client_inline ());
  return 0;
}
