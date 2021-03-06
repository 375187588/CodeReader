/* -*- c++ -*- */
//
// cdr_op_ci.h,v 1.1 1999/05/28 02:16:46 coryan Exp
//

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    cdr_op_ci.h
//
// = DESCRIPTION
//    Concrete visitor for the Typedef class
//    This provides the code generation for the CDR operators of the Typedef
//    class in the client stubs.
//
// = AUTHOR
//    Aniruddha Gokhale
//
// ============================================================================

#ifndef _BE_VISITOR_TYPEDEF_CDR_OP_CI_H_
#define _BE_VISITOR_TYPEDEF_CDR_OP_CI_H_

class be_visitor_typedef_cdr_op_ci : public be_visitor_typedef
{
  //
  // = TITLE
  //   be_visitor_typedef_cdr_op_ci
  //
  // = DESCRIPTION
  //   This is a concrete visitor for typedef that generates the CDR operator
  //   declarations and implementations
  //

public:
  be_visitor_typedef_cdr_op_ci (be_visitor_context *ctx);
  // constructor

  ~be_visitor_typedef_cdr_op_ci (void);
  // destructor

  virtual int visit_typedef (be_typedef *node);
  // visit typedef

  // =visit methods on all elements syntactically valid as types that can be
  // typedefed.

  virtual int visit_array (be_array *node);
  // visit a array

  virtual int visit_enum (be_enum *node);
  // visit an enum

  virtual int visit_sequence (be_sequence *node);
  // visit a sequence

  virtual int visit_structure (be_structure *node);
  // visit a structure

  virtual int visit_union (be_union *node);
  // visit a union

};

#endif /* _BE_VISITOR_TYPEDEF_CDR_OP_CI_H_*/
