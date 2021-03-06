// Foo_i.cpp,v 1.2 1999/06/15 22:55:41 irfan Exp

//===========================================================================
//
//
// = FILENAME
//     Foo_i.cpp
//
// = DESCRIPTION
//     This is a simple foo servant implementation
//
// = AUTHOR
//     Irfan Pyarali
//
//===========================================================================

#include "Foo_i.h"

ACE_RCSID(TIE, Foo_i, "Foo_i.cpp,v 1.2 1999/06/15 22:55:41 irfan Exp")

  // Constructor
  Tie_i::Tie_i (CORBA::Long value)
    : value_ (value)
{
}

// Return this->value
CORBA::Long
Tie_i::doit (CORBA::Environment &/*env*/)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  return this->value_;
}

// Constructor
A_i::A_i (CORBA::Long value,
          PortableServer::POA_ptr poa)
  : value_ (value),
    poa_ (PortableServer::POA::_duplicate (poa))
{
}

// Return this->value
CORBA::Long
A_i::doit (CORBA::Environment &/*env*/)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  return this->value_;
}

// Return the Default POA of this Servant
PortableServer::POA_ptr
A_i::_default_POA (CORBA::Environment &/*env*/)
{
  return PortableServer::POA::_duplicate (this->poa_.in ());
}

// Constructor
Outer_i::B_i::B_i (CORBA::Long value,
                   PortableServer::POA_ptr poa)
  : value_ (value),
    poa_ (PortableServer::POA::_duplicate (poa))
{
}

// Return this->value
CORBA::Long
Outer_i::B_i::doit (CORBA::Environment &/*env*/)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  return this->value_;
}

// Return the Default POA of this Servant
PortableServer::POA_ptr
Outer_i::B_i::_default_POA (CORBA::Environment &/*env*/)
{
  return PortableServer::POA::_duplicate (this->poa_.in ());
}

// Constructor
Outer_i::Inner_i::C_i::C_i (CORBA::Long value,
                            PortableServer::POA_ptr poa)
  : value_ (value),
    poa_ (PortableServer::POA::_duplicate (poa))
{
}

// Return this->value
CORBA::Long
Outer_i::Inner_i::C_i::doit (CORBA::Environment &/*env*/)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  return this->value_;
}

// Return the Default POA of this Servant
PortableServer::POA_ptr
Outer_i::Inner_i::C_i::_default_POA (CORBA::Environment &/*env*/)
{
  return PortableServer::POA::_duplicate (this->poa_.in ());
}
