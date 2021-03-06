/* -*- c++ -*- */
//
// cdr_op_ci.h,v 1.2 2000/01/07 17:56:21 parsons Exp
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
//    Concrete visitor for the base "BE_Union_Branch" node
//    This generates code for structure members in the client header.
//
// = AUTHOR
//    Aniruddha Gokhale
//
// ============================================================================

#ifndef _BE_VISITOR_UNION_BRANCH_CDR_OP_CI_H_
#define _BE_VISITOR_UNION_BRANCH_CDR_OP_CI_H_

class be_visitor_union_branch_cdr_op_ci : public be_visitor_decl
{
  //
  // = TITLE
  //    be_visitor_union_branch_cdr_op_ci
  //
  // = DESCRIPTION
  //   This is a concrete visitor for the be_union_branch node for the client header.
  //
public:
  be_visitor_union_branch_cdr_op_ci (be_visitor_context *ctx);
  // constructor

  ~be_visitor_union_branch_cdr_op_ci (void);
  // destructor

  virtual int visit_union_branch (be_union_branch *node);
  // visit the union_branch node

  // =visit operations on all possible data types that a union_branch can be

  virtual int visit_array (be_array *node);
  // visit array type

  virtual int visit_enum (be_enum *node);
  // visit enum type

  virtual int visit_interface (be_interface *node);
  // visit interface type

  virtual int visit_interface_fwd (be_interface_fwd *node);
  // visit interface forward type

  virtual int visit_predefined_type (be_predefined_type *node);
  // visit predefined type

  virtual int visit_sequence (be_sequence *node);
  // visit sequence type

  virtual int visit_string (be_string *node);
  // visit string type

  virtual int visit_structure (be_structure *node);
  // visit structure type

  virtual int visit_typedef (be_typedef *node);
  // visit typedefed type

  virtual int visit_union (be_union *node);
  // visit union type

  virtual int explicit_default (void);
  // extra code generation for an explicit default case
};

#endif /*  _BE_VISITOR_UNION_BRANCH_CDR_OP_CI_H_ */
