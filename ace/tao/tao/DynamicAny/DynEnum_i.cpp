/* -*- C++ -*- */
// DynEnum_i.cpp,v 1.9 2001/06/12 23:07:33 parsons Exp

#include "DynEnum_i.h"
#include "DynAnyFactory.h"

ACE_RCSID(DynamicAny, DynEnum_i, "DynEnum_i.cpp,v 1.9 2001/06/12 23:07:33 parsons Exp")

// Constructors and destructor

TAO_DynEnum_i::TAO_DynEnum_i (void)
{
}

TAO_DynEnum_i::~TAO_DynEnum_i (void)
{
}

void
TAO_DynEnum_i::init_common (void)
{
  this->ref_to_component_ = 0;
  this->container_is_destroying_ = 0;
  this->has_components_ = 0;
  this->destroyed_ = 0;
  this->current_position_ = -1;
  this->component_count_ = 0;
}

void
TAO_DynEnum_i::init (const CORBA_Any &any,
                     CORBA::Environment &ACE_TRY_ENV)
{
  CORBA::TypeCode_var tc = any.type ();

  CORBA::TCKind kind =
    TAO_DynAnyFactory::unalias (tc.in (),
                                ACE_TRY_ENV);
  ACE_CHECK;

  if (kind != CORBA::tk_enum)
    {
      ACE_THROW (DynamicAny::DynAnyFactory::InconsistentTypeCode ());
    }

  this->type_ = tc;

  ACE_Message_Block *mb = any._tao_get_cdr ();

  TAO_InputCDR cdr (mb,
                    any._tao_byte_order ());

  cdr.read_ulong (this->value_);

  this->init_common ();
}

void
TAO_DynEnum_i::init (CORBA_TypeCode_ptr tc,
                     CORBA::Environment &ACE_TRY_ENV)
{
  CORBA::TCKind kind = TAO_DynAnyFactory::unalias (tc,
                                                   ACE_TRY_ENV);
  ACE_CHECK;

  if (kind != CORBA::tk_enum)
    {
      ACE_THROW (DynamicAny::DynAnyFactory::InconsistentTypeCode ());
    }

  this->type_ = CORBA::TypeCode::_duplicate (tc);

  this->value_ = 0;

  this->init_common ();
}

// ****************************************************************

TAO_DynEnum_i *
TAO_DynEnum_i::_narrow (CORBA::Object_ptr obj,
                        CORBA::Environment &)
{
  if (CORBA::is_nil (obj))
    {
      return 0;
    }

  return ACE_reinterpret_cast (
             TAO_DynEnum_i*,
             obj->_tao_QueryInterface (
                      ACE_reinterpret_cast (
                          ptr_arith_t,
                          &TAO_DynEnum_i::_narrow
                        )
                    )
           );
}

void*
TAO_DynEnum_i::_tao_QueryInterface (ptr_arith_t type)
{
  ptr_arith_t mytype =
    ACE_reinterpret_cast (ptr_arith_t,
                          &TAO_DynEnum_i::_narrow);
  if (type == mytype)
    {
      this->_add_ref ();
      return this;
    }

  return 
    this->ACE_NESTED_CLASS (DynamicAny, DynEnum::_tao_QueryInterface) (type);
}

// ****************************************************************

char *
TAO_DynEnum_i::get_as_string (CORBA::Environment& ACE_TRY_ENV)
  ACE_THROW_SPEC ((
      CORBA::SystemException
    ))
{
  const char *retval = this->type_.in ()->member_name (this->value_,
                                                       ACE_TRY_ENV);
  ACE_CHECK_RETURN (0);

  return CORBA::string_dup (retval);
}

void
TAO_DynEnum_i::set_as_string (const char *value_as_string,
                              CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((
      CORBA::SystemException,
      DynamicAny::DynAny::InvalidValue
    ))
{
  CORBA::ULong count = this->type_.in ()->member_count (ACE_TRY_ENV);
  ACE_CHECK;

  CORBA::ULong i;
  const char *temp = 0;

  for (i = 0; i < count; ++i)
    {
      temp = this->type_.in ()->member_name (i,
                                             ACE_TRY_ENV);
      ACE_CHECK;

      if (!ACE_OS::strcmp (value_as_string,
                           temp))
        {
          break;
        }
    }

  if (i < count)
    {
      this->value_ = i;
    }
  else
    {
      ACE_THROW (DynamicAny::DynAny::InvalidValue ());
    }
}

CORBA::ULong
TAO_DynEnum_i::get_as_ulong (CORBA::Environment &)
  ACE_THROW_SPEC ((
      CORBA::SystemException
    ))
{
  return this->value_;
}

void
TAO_DynEnum_i::set_as_ulong (CORBA::ULong value_as_ulong,
                             CORBA::Environment& ACE_TRY_ENV)
  ACE_THROW_SPEC ((
      CORBA::SystemException,
      DynamicAny::DynAny::InvalidValue
    ))
{
  CORBA::ULong max = this->type_.in ()->member_count (ACE_TRY_ENV);
  ACE_CHECK;

  if (value_as_ulong < max)
    {
      this->value_ = value_as_ulong;
    }
  else
    {
      ACE_THROW (DynamicAny::DynAny::InvalidValue ());
    }
}

// ****************************************************************

void
TAO_DynEnum_i::from_any (const CORBA_Any& any,
                         CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((
      CORBA::SystemException,
      DynamicAny::DynAny::TypeMismatch,
      DynamicAny::DynAny::InvalidValue
    ))
{
  CORBA::TypeCode_var tc = any.type ();
  CORBA::TCKind kind = TAO_DynAnyFactory::unalias (tc.in (),
                                                   ACE_TRY_ENV);
  ACE_CHECK;

  if (kind == CORBA::tk_enum)
    {
      // Get the CDR stream of the argument.
      ACE_Message_Block* mb = any._tao_get_cdr ();

      TAO_InputCDR cdr (mb,
                        any._tao_byte_order ());

      cdr.read_ulong (this->value_);
    }
  else
    {
      ACE_THROW (DynamicAny::DynAny::TypeMismatch ());
    }
}

CORBA::Any_ptr
TAO_DynEnum_i::to_any (CORBA::Environment& ACE_TRY_ENV)
  ACE_THROW_SPEC ((
      CORBA::SystemException
    ))
{
  TAO_OutputCDR out_cdr;

  out_cdr.write_ulong (this->value_);

  CORBA_Any *retval;
  ACE_NEW_THROW_EX (retval,
                    CORBA_Any (this->type_.in (),
                               0,
                               TAO_ENCAP_BYTE_ORDER,
                               out_cdr.begin ()),
                    CORBA::NO_MEMORY ());
  ACE_CHECK_RETURN (0);
  return retval;
}

CORBA::Boolean
TAO_DynEnum_i::equal (DynamicAny::DynAny_ptr rhs,
                      CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((
      CORBA::SystemException
    ))
{
  CORBA::TypeCode_var tc = rhs->type (ACE_TRY_ENV);
  ACE_CHECK_RETURN (0);

  CORBA::Boolean equivalent = tc->equivalent (this->type_.in (),
                                              ACE_TRY_ENV);
  ACE_CHECK_RETURN (0);

  if (!equivalent)
    {
      return 0;
    }

  CORBA_Any_ptr any = rhs->to_any (ACE_TRY_ENV);
  ACE_CHECK_RETURN (0);

  ACE_Message_Block *mb = any->_tao_get_cdr ();

  TAO_InputCDR cdr (mb,
                    any->_tao_byte_order ());

  CORBA::ULong value;
  cdr.read_ulong (value);

  return value == this->value_;
}

void
TAO_DynEnum_i::destroy (CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((
      CORBA::SystemException
    ))
{
  if (this->destroyed_)
    {
      ACE_THROW (CORBA::OBJECT_NOT_EXIST ());
    }

  if (!this->ref_to_component_ || this->container_is_destroying_)
    {
      this->destroyed_ = 1;
    }
}

DynamicAny::DynAny_ptr
TAO_DynEnum_i::current_component (CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((
      CORBA::SystemException,
      DynamicAny::DynAny::TypeMismatch
    ))
{
  if (this->destroyed_)
    {
      ACE_THROW_RETURN (CORBA::OBJECT_NOT_EXIST (),
                        DynamicAny::DynAny::_nil ());
    }

  ACE_THROW_RETURN (DynamicAny::DynAny::TypeMismatch (),
                    DynamicAny::DynAny::_nil ());
}
