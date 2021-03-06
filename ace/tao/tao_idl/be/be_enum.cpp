// be_enum.cpp,v 1.28 2000/10/16 19:23:47 parsons Exp

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    be_enum.cpp
//
// = DESCRIPTION
//    Extension of class AST_Enum that provides additional means for C++
//    mapping.
//
// = AUTHOR
//    Copyright 1994-1995 by Sun Microsystems, Inc.
//    and
//    Aniruddha Gokhale
//
// ============================================================================

#include	"idl.h"
#include	"idl_extern.h"
#include	"be.h"

ACE_RCSID(be, be_enum, "be_enum.cpp,v 1.28 2000/10/16 19:23:47 parsons Exp")

be_enum::be_enum (void)
{
  this->size_type (be_decl::FIXED);
}

be_enum::be_enum (UTL_ScopedName *n,
                  UTL_StrList *p,
                  idl_bool local,
                  idl_bool abstract)
  : AST_Enum (n, 
              p, 
              local, 
              abstract),
    AST_Decl (AST_Decl::NT_enum, 
              n, 
              p),
    UTL_Scope (AST_Decl::NT_enum),
    COMMON_Base (local, 
                 abstract)
{
  this->size_type (be_decl::FIXED);
}

void
be_enum::destroy (void)
{
  // Call the destroy methods of our base classes.
  be_scope::destroy ();
//  be_type::destroy ();
}

int
be_enum::accept (be_visitor *visitor)
{
  return visitor->visit_enum (this);
}

// Narrowing
IMPL_NARROW_METHODS3 (be_enum, AST_Enum, be_scope, be_type)
IMPL_NARROW_FROM_DECL (be_enum)
IMPL_NARROW_FROM_SCOPE (be_enum)
