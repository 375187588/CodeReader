/* -*- C++ -*- */
// Supplier.h,v 1.1 2000/02/25 23:12:28 coryan Exp
//
// ============================================================================
//
// = LIBRARY
//   ORBSVCS COS Event Channel examples
//
// = FILENAME
//   Supplier
//
// = AUTHOR
//   Carlos O'Ryan (coryan@cs.wustl.edu)
//
// ============================================================================

#ifndef SUPPLIER_H
#define SUPPLIER_H

#include "orbsvcs/CosEventCommS.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

class Supplier : public POA_CosEventComm::PushSupplier
{
  // = TITLE
  //   Simple supplier object
  //
  // = DESCRIPTION
  //   This class is a supplier of events.
  //
public:
  Supplier (void);
  // Constructor

  int run (int argc, char* argv[]);
  // Run the test

  // = The CosEventComm::PushSupplier methods

  virtual void disconnect_push_supplier (CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException));
  // The skeleton methods.

private:
};

#endif /* SUPPLIER_H */
