// -*- C++ -*-
//
// TypeCodeFactoryC.h,v 1.3 2001/08/21 19:00:28 parsons Exp

// ****  Code generated by the The ACE ORB (TAO) IDL Compiler ****
// TAO and the TAO IDL Compiler have been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// and
//       Distributed Object Computing Laboratory
//       University of California at Irvine
//       Irvine, CA
//       USA
//       http://doc.ece.uci.edu/
//
// Information about TAO is available at:
//     http://www.cs.wustl.edu/~schmidt/TAO.html

#ifndef _TAO_IDL_TYPECODEFACTORYC_H_
#define _TAO_IDL_TYPECODEFACTORYC_H_

#ifndef TAO_TYPECODEFACTORY_SAFE_INCLUDE
#error "You should not include TypeCodeFactoryC.h directly, use TCF_Loader.h"
#endif /* !TAO_TYPECODEFACTORY_SAFE_INCLUDE */

#include "ace/pre.h"
#include "typecodefactory_export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "tao/Object.h"

#if defined (TAO_EXPORT_MACRO)
#undef TAO_EXPORT_MACRO
#endif
#define TAO_EXPORT_MACRO TAO_TypeCodeFactory_Export

#if defined (TAO_EXPORT_NESTED_CLASSES)
#  if defined (TAO_EXPORT_NESTED_MACRO)
#    undef TAO_EXPORT_NESTED_MACRO
#  endif /* defined (TAO_EXPORT_NESTED_MACRO) */
#  define TAO_EXPORT_NESTED_MACRO TAO_TypeCodeFactory_Export
#endif /* TAO_EXPORT_NESTED_CLASSES */

#if defined(_MSC_VER)
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif /* _MSC_VER >= 1200 */
#pragma warning(disable:4250)
#endif /* _MSC_VER */

#if defined (__BORLANDC__)
#pragma option push -w-rvl -w-rch -w-ccc -w-inl
#endif /* __BORLANDC__ */


#if !defined (_CORBA_TYPECODEFACTORY___PTR_CH_)
#define _CORBA_TYPECODEFACTORY___PTR_CH_

class CORBA_TypeCodeFactory;
typedef CORBA_TypeCodeFactory *CORBA_TypeCodeFactory_ptr;

#endif /* end #if !defined */


#if !defined (_CORBA_TYPECODEFACTORY___VAR_CH_)
#define _CORBA_TYPECODEFACTORY___VAR_CH_

class TAO_TypeCodeFactory_Export CORBA_TypeCodeFactory_var : public TAO_Base_var
{
public:
  CORBA_TypeCodeFactory_var (void); // default constructor
  CORBA_TypeCodeFactory_var (CORBA_TypeCodeFactory_ptr p) : ptr_ (p) {} 
  CORBA_TypeCodeFactory_var (const CORBA_TypeCodeFactory_var &); // copy constructor
  ~CORBA_TypeCodeFactory_var (void); // destructor
  
  CORBA_TypeCodeFactory_var &operator= (CORBA_TypeCodeFactory_ptr);
  CORBA_TypeCodeFactory_var &operator= (const CORBA_TypeCodeFactory_var &);
  CORBA_TypeCodeFactory_ptr operator-> (void) const;
  
  operator const CORBA_TypeCodeFactory_ptr &() const;
  operator CORBA_TypeCodeFactory_ptr &();
  // in, inout, out, _retn 
  CORBA_TypeCodeFactory_ptr in (void) const;
  CORBA_TypeCodeFactory_ptr &inout (void);
  CORBA_TypeCodeFactory_ptr &out (void);
  CORBA_TypeCodeFactory_ptr _retn (void);
  CORBA_TypeCodeFactory_ptr ptr (void) const;
  
  // Hooks used by template sequence and object manager classes
  // for non-defined forward declared interfaces.
  static CORBA_TypeCodeFactory_ptr tao_duplicate (CORBA_TypeCodeFactory_ptr);
  static void tao_release (CORBA_TypeCodeFactory_ptr);
  static CORBA_TypeCodeFactory_ptr tao_nil (void);
  static CORBA_TypeCodeFactory_ptr tao_narrow (CORBA::Object *, CORBA::Environment &);
  static CORBA::Object * tao_upcast (void *);

private:
  CORBA_TypeCodeFactory_ptr ptr_;
  // Unimplemented - prevents widening assignment.
  CORBA_TypeCodeFactory_var (const TAO_Base_var &rhs);
  CORBA_TypeCodeFactory_var &operator= (const TAO_Base_var &rhs);
};


#endif /* end #if !defined */


#if !defined (_CORBA_TYPECODEFACTORY___OUT_CH_)
#define _CORBA_TYPECODEFACTORY___OUT_CH_

class TAO_TypeCodeFactory_Export CORBA_TypeCodeFactory_out
{
public:
  CORBA_TypeCodeFactory_out (CORBA_TypeCodeFactory_ptr &);
  CORBA_TypeCodeFactory_out (CORBA_TypeCodeFactory_var &);
  CORBA_TypeCodeFactory_out (const CORBA_TypeCodeFactory_out &);
  CORBA_TypeCodeFactory_out &operator= (const CORBA_TypeCodeFactory_out &);
  CORBA_TypeCodeFactory_out &operator= (const CORBA_TypeCodeFactory_var &);
  CORBA_TypeCodeFactory_out &operator= (CORBA_TypeCodeFactory_ptr);
  operator CORBA_TypeCodeFactory_ptr &();
  CORBA_TypeCodeFactory_ptr &ptr (void);
  CORBA_TypeCodeFactory_ptr operator-> (void);

private:
  CORBA_TypeCodeFactory_ptr &ptr_;
};


#endif /* end #if !defined */


#if !defined (_CORBA_TYPECODEFACTORY_CH_)
#define _CORBA_TYPECODEFACTORY_CH_

class TAO_TypeCodeFactory_Export CORBA_TypeCodeFactory : public virtual CORBA_Object
{
public:
#if !defined(__GNUC__) || !defined (ACE_HAS_GNUG_PRE_2_8)
  typedef CORBA_TypeCodeFactory_ptr _ptr_type;
  typedef CORBA_TypeCodeFactory_var _var_type;
#endif /* ! __GNUC__ || g++ >= 2.8 */

  static int _tao_class_id;

  // the static operations
  static CORBA_TypeCodeFactory_ptr _duplicate (CORBA_TypeCodeFactory_ptr obj);
  static CORBA_TypeCodeFactory_ptr _narrow (
      CORBA::Object_ptr obj,
      CORBA::Environment &ACE_TRY_ENV = 
        TAO_default_environment ()
    );
  static CORBA_TypeCodeFactory_ptr _unchecked_narrow (
      CORBA::Object_ptr obj,
      CORBA::Environment &ACE_TRY_ENV = 
        TAO_default_environment ()
    );
  static CORBA_TypeCodeFactory_ptr _nil (void)
    {
      return (CORBA_TypeCodeFactory_ptr)0;
    }

  virtual CORBA::TypeCode_ptr create_struct_tc (
      const char * id,
      const char * name,
      const CORBA_StructMemberSeq & members,
      CORBA::Environment &ACE_TRY_ENV = 
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((
      CORBA::SystemException
    )) = 0;

  virtual CORBA::TypeCode_ptr create_union_tc (
      const char * id,
      const char * name,
      CORBA::TypeCode_ptr discriminator_type,
      const CORBA_UnionMemberSeq & members,
      CORBA::Environment &ACE_TRY_ENV = 
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((
      CORBA::SystemException
    )) = 0;

  virtual CORBA::TypeCode_ptr create_enum_tc (
      const char * id,
      const char * name,
      const CORBA_EnumMemberSeq & members,
      CORBA::Environment &ACE_TRY_ENV = 
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((
      CORBA::SystemException
    )) = 0;

  virtual CORBA::TypeCode_ptr create_alias_tc (
      const char * id,
      const char * name,
      CORBA::TypeCode_ptr original_type,
      CORBA::Environment &ACE_TRY_ENV = 
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((
      CORBA::SystemException
    )) = 0;

  virtual CORBA::TypeCode_ptr create_exception_tc (
      const char * id,
      const char * name,
      const CORBA_StructMemberSeq & members,
      CORBA::Environment &ACE_TRY_ENV = 
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((
      CORBA::SystemException
    )) = 0;

  virtual CORBA::TypeCode_ptr create_interface_tc (
      const char * id,
      const char * name,
      CORBA::Environment &ACE_TRY_ENV = 
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((
      CORBA::SystemException
    )) = 0;

  virtual CORBA::TypeCode_ptr create_string_tc (
      CORBA::ULong bound,
      CORBA::Environment &ACE_TRY_ENV = 
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((
      CORBA::SystemException
    )) = 0;

  virtual CORBA::TypeCode_ptr create_wstring_tc (
      CORBA::ULong bound,
      CORBA::Environment &ACE_TRY_ENV = 
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((
      CORBA::SystemException
    )) = 0;

  virtual CORBA::TypeCode_ptr create_fixed_tc (
      CORBA::UShort digits,
      CORBA::UShort scale,
      CORBA::Environment &ACE_TRY_ENV = 
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((
      CORBA::SystemException
    )) = 0;

  virtual CORBA::TypeCode_ptr create_sequence_tc (
      CORBA::ULong bound,
      CORBA::TypeCode_ptr element_type,
      CORBA::Environment &ACE_TRY_ENV = 
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((
      CORBA::SystemException
    )) = 0;

  virtual CORBA::TypeCode_ptr create_array_tc (
      CORBA::ULong length,
      CORBA::TypeCode_ptr element_type,
      CORBA::Environment &ACE_TRY_ENV = 
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((
      CORBA::SystemException
    )) = 0;

  virtual CORBA::TypeCode_ptr create_value_tc (
      const char * id,
      const char * name,
      CORBA::Short type_modifier,
      CORBA::TypeCode_ptr concrete_base,
      const CORBA_ValueMemberSeq & members,
      CORBA::Environment &ACE_TRY_ENV = 
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((
      CORBA::SystemException
    )) = 0;

  virtual CORBA::TypeCode_ptr create_value_box_tc (
      const char * id,
      const char * name,
      CORBA::TypeCode_ptr boxed_type,
      CORBA::Environment &ACE_TRY_ENV = 
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((
      CORBA::SystemException
    )) = 0;

  virtual CORBA::TypeCode_ptr create_native_tc (
      const char * id,
      const char * name,
      CORBA::Environment &ACE_TRY_ENV = 
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((
      CORBA::SystemException
    )) = 0;

  virtual CORBA::TypeCode_ptr create_recursive_tc (
      const char * id,
      CORBA::Environment &ACE_TRY_ENV = 
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((
      CORBA::SystemException
    )) = 0;

  virtual CORBA::TypeCode_ptr create_abstract_interface_tc (
      const char * id,
      const char * name,
      CORBA::Environment &ACE_TRY_ENV = 
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((
      CORBA::SystemException
    )) = 0;

  virtual CORBA::TypeCode_ptr create_local_interface_tc (
      const char * id,
      const char * name,
      CORBA::Environment &ACE_TRY_ENV = 
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((
      CORBA::SystemException
    )) = 0;

  virtual CORBA::TypeCode_ptr create_component_tc (
      const char * id,
      const char * name,
      CORBA::Environment &ACE_TRY_ENV = 
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((
      CORBA::SystemException
    )) = 0;

  virtual CORBA::TypeCode_ptr create_home_tc (
      const char * id,
      const char * name,
      CORBA::Environment &ACE_TRY_ENV = 
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((
      CORBA::SystemException
    )) = 0;

  virtual void *_tao_QueryInterface (ptr_arith_t type);
  
  virtual const char* _interface_repository_id (void) const;

protected:
  CORBA_TypeCodeFactory ();
  
  virtual ~CORBA_TypeCodeFactory (void);
private:
  CORBA_TypeCodeFactory (const CORBA_TypeCodeFactory &);
  void operator= (const CORBA_TypeCodeFactory &);
};


#endif /* end #if !defined */


#ifndef __ACE_INLINE__


#endif /* __ACE_INLINE__ */


#if defined (__ACE_INLINE__)
#include "TypeCodeFactoryC.inl"
#endif /* defined INLINE */

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma warning(pop)
#endif /* _MSC_VER */

#if defined (__BORLANDC__)
#pragma option pop
#endif /* __BORLANDC__ */

#include "ace/post.h"
#endif /* ifndef */
