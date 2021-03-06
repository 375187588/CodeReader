// -*- C++ -*-

//=============================================================================
/**
 *  @file    ORB.h
 *
 *  ORB.h,v 1.203 2001/09/18 00:05:43 irfan Exp
 *
 *  Header file for CORBA's ORB type.
 *
 *  @author  Copyright 1994-1995 by Sun Microsystems Inc.
 *  @author Douglas C. Schmidt <schmidt@uci.edu>
 */
//=============================================================================

#ifndef TAO_ORB_H
#define TAO_ORB_H

#include "ace/pre.h"

#include "corbafwd.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "Exception.h"
#include "Services.h"
#include "CORBA_String.h"

// IRIX needs this for the throw specs
#include "PolicyC.h"

typedef enum
{
  TAO_SERVICEID_NAMESERVICE,
  TAO_SERVICEID_TRADINGSERVICE,
  TAO_SERVICEID_IMPLREPOSERVICE,
  TAO_SERVICEID_INTERFACEREPOSERVICE,
  TAO_SERVICEID_MCASTSERVER
} TAO_Service_ID;

/// Forward declarations.
class TAO_MProfile;
struct TAO_Dispatch_Context;
class TAO_Client_Strategy_Factory;
class TAO_Server_Strategy_Factory;
class TAO_InputCDR;
class TAO_OutputCDR;
class TAO_Stub;

class TAO_Acceptor_Filter;

#ifdef TAO_HAS_VALUETYPE
class TAO_ValueFactory_Map;
#endif /* TAO_HAS_VALUETYPE */

// ****************************************************************

/**
 * @class CORBA_ORB
 *
 * @brief ORB pseudo-objref.
 *
 * The "ORB" pseudo-object is used in bootstrapping, such as to
 * create object references from strings.  This class is intended
 * to be inherited by others, which will provide some more of the
 * CORBA support.  Implementations of this "CORBA::ORB" class must
 * know how to create stringify/destringify their objrefs, as well
 * as how to marshal and unmarshal them.
 */
class TAO_Export CORBA_ORB
{
public:

  // ORB_Core has special privileges
  friend class TAO_ORB_Core;
  friend TAO_Export TAO_ORB_Core *TAO_ORB_Core_instance (void);

  class TAO_Export InvalidName : public CORBA_UserException
  {
  public:
    InvalidName (void);
    InvalidName (const InvalidName &);
    ~InvalidName (void);
    InvalidName &operator= (const InvalidName &);

    virtual void _raise (void);

    virtual void _tao_encode (TAO_OutputCDR &cdr,
                              CORBA::Environment &) const;
    virtual void _tao_decode (TAO_InputCDR &cdr,
                              CORBA::Environment &);

    /// = TAO extension
    static InvalidName* _downcast (CORBA_Exception *ex);
    static CORBA::Exception *_alloc (void);
  };
  static CORBA::TypeCode_ptr _tc_InvalidName;

  typedef char *ObjectId;
  typedef CORBA::String_var ObjectId_var;
  typedef CORBA::String_out ObjectId_out;
  static CORBA::TypeCode_ptr _tc_ObjectId;

  typedef CORBA_ORB_ObjectIdList ObjectIdList;
  typedef CORBA_ORB_ObjectIdList_var ObjectIdList_var;
  typedef CORBA_ORB_ObjectIdList_out ObjectIdList_out;
  typedef CORBA_ORB_ObjectIdList *ObjectIdList_ptr;
  static CORBA::TypeCode_ptr _tc_ObjectIdList;

  /// Return a duplicate of <{orb}>.  When work with this duplicate is
  /// complete, it should be freed up using <CORBA::release()>.
  static CORBA::ORB_ptr _duplicate (CORBA::ORB_ptr orb);

  /// Returns a pointer to a nil ORB, i.e., an non-existent ORB.  This
  /// can be used for initialization or in comparisons.
  static CORBA::ORB_ptr _nil (void);

  /**
   * Turn a string-ified object reference back into an object pointer.
   * Typically these strings are created using <object_to_string()>,
   * but not necessarily locally.
   */
  CORBA::Object_ptr string_to_object (const char *str,
                                      CORBA_Environment &ACE_TRY_ENV =
                                          TAO_default_environment ());

  /**
   * Turn an object reference into a string.  Each type of ORB,
   * e.g. an IIOP ORB, must implement this.  This can be used by
   * servers to publish their whereabouts to clients.  The output of
   * this is typically eventually given to <string_to_object()> as an
   * argument.
   */
  char * object_to_string (CORBA::Object_ptr obj,
                           CORBA_Environment &ACE_TRY_ENV =
                               TAO_default_environment ());


#ifdef TAO_HAS_VALUETYPE
  // Value factory operations  (CORBA 2.3 ptc/98-10-05 Ch. 4.2 p.4-7)
  CORBA::ValueFactory_ptr register_value_factory (
         const char *repository_id,
         CORBA::ValueFactory_ptr factory,
         CORBA_Environment &ACE_TRY_ENV =
             TAO_default_environment () );
  void unregister_value_factory (const char * repository_id,
                                 CORBA_Environment &ACE_TRY_ENV =
                                     TAO_default_environment () );
  CORBA::ValueFactory_ptr lookup_value_factory (
         const char *repository_id,
         CORBA_Environment &ACE_TRY_ENV =
             TAO_default_environment () );
#endif /* TAO_HAS_VALUETYPE */

#if (TAO_HAS_MINIMUM_CORBA == 0)

  // Typedefs for CORBA_ORB_RequestSeq,
  // which is an argument of send_multiple_requests_*().
  // See Request.{h,i,cpp} for definitions.
  typedef CORBA_ORB_RequestSeq RequestSeq;
  typedef CORBA_ORB_RequestSeq_var RequestSeq_var;
  typedef CORBA_ORB_RequestSeq_out RequestSeq_out;

  void create_list (CORBA::Long count,
                    CORBA::NVList_ptr &new_list,
                    CORBA_Environment &ACE_TRY_ENV =
                        TAO_default_environment ());

  void create_named_value (CORBA::NamedValue_ptr &nmval,
                           CORBA_Environment &ACE_TRY_ENV =
                               TAO_default_environment ());

  void create_exception_list (CORBA::ExceptionList_ptr &exclist,
                              CORBA_Environment &ACE_TRY_ENV =
                                  TAO_default_environment ());

  void create_environment (CORBA::Environment_ptr &new_env,
                           CORBA_Environment &ACE_TRY_ENV =
                           TAO_default_environment ());

  // The following are not implemented and just throw
  // CORBA::NO_IMPLEMENT.

  void create_context_list (CORBA::ContextList_ptr &ctxtlist,
                            CORBA_Environment &ACE_TRY_ENV =
                            TAO_default_environment ());

  void get_default_context (CORBA::Context_ptr &ctx,
                            CORBA_Environment &ACE_TRY_ENV =
                            TAO_default_environment ());

  CORBA::Boolean get_service_information (CORBA::ServiceType service_type,
                                          CORBA::ServiceInformation_out service_information,
                                          CORBA::Environment &ACE_TRY_ENV =
                                          TAO_default_environment ());

  void send_multiple_requests_oneway (const CORBA_ORB_RequestSeq &req ,
                                      CORBA_Environment &ACE_TRY_ENV =
                                      TAO_default_environment ());

  void send_multiple_requests_deferred (const CORBA_ORB_RequestSeq &req,
                                        CORBA_Environment &ACE_TRY_ENV =
                                        TAO_default_environment ());

  void get_next_response (CORBA_Request_ptr &req,
                          CORBA_Environment &ACE_TRY_ENV =
                          TAO_default_environment ());

  CORBA::Boolean poll_next_response (CORBA_Environment &ACE_TRY_ENV =
                                     TAO_default_environment ());

  /// The ORB TypeCode creation functions.

  CORBA::TypeCode_ptr create_struct_tc (
      const char *id,
      const char *name,
      const CORBA::StructMemberSeq &members,
      CORBA::Environment &ACE_TRY_ENV =
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((CORBA::SystemException));

  CORBA::TypeCode_ptr create_union_tc (
      const char *id,
      const char *name,
      CORBA::TypeCode_ptr discriminator_type,
      const CORBA::UnionMemberSeq &members,
      CORBA::Environment &ACE_TRY_ENV =
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((CORBA::SystemException));

  CORBA::TypeCode_ptr create_enum_tc (
      const char *id,
      const char *name,
      const CORBA::EnumMemberSeq &members,
      CORBA::Environment &ACE_TRY_ENV =
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((CORBA::SystemException));

  CORBA::TypeCode_ptr create_alias_tc (
      const char *id,
      const char *name,
      CORBA::TypeCode_ptr original_type,
      CORBA::Environment &ACE_TRY_ENV =
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((CORBA::SystemException));

  CORBA::TypeCode_ptr create_exception_tc (
      const char *id,
      const char *name,
      const CORBA::StructMemberSeq &members,
      CORBA::Environment &ACE_TRY_ENV =
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((CORBA::SystemException));

  CORBA::TypeCode_ptr create_interface_tc (
      const char *id,
      const char *name,
      CORBA::Environment &ACE_TRY_ENV =
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((CORBA::SystemException));

  CORBA::TypeCode_ptr create_string_tc (
      CORBA::ULong bound,
      CORBA::Environment &ACE_TRY_ENV =
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((CORBA::SystemException));

  CORBA::TypeCode_ptr create_wstring_tc (
      CORBA::ULong bound,
      CORBA::Environment &ACE_TRY_ENV =
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((CORBA::SystemException));

  CORBA::TypeCode_ptr create_fixed_tc (
      CORBA::UShort digits,
      CORBA::UShort scale,
      CORBA::Environment &ACE_TRY_ENV =
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((CORBA::SystemException));

  CORBA::TypeCode_ptr create_sequence_tc (
      CORBA::ULong bound,
      CORBA::TypeCode_ptr element_type,
      CORBA::Environment &ACE_TRY_ENV =
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((CORBA::SystemException));

  CORBA::TypeCode_ptr create_array_tc (
      CORBA::ULong length,
      CORBA::TypeCode_ptr element_type,
      CORBA::Environment &ACE_TRY_ENV =
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((CORBA::SystemException));

  CORBA::TypeCode_ptr create_value_tc (
      const char *id,
      const char *name,
      CORBA::ValueModifier type_modifier,
      CORBA::TypeCode_ptr concrete_base,
      const CORBA::ValueMemberSeq &members,
      CORBA::Environment &ACE_TRY_ENV =
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((CORBA::SystemException));

  CORBA::TypeCode_ptr create_value_box_tc (
      const char *id,
      const char *name,
      CORBA::TypeCode_ptr boxed_type,
      CORBA::Environment &ACE_TRY_ENV =
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((CORBA::SystemException));

  CORBA::TypeCode_ptr create_native_tc (
      const char *id,
      const char *name,
      CORBA::Environment &ACE_TRY_ENV =
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((CORBA::SystemException));

  CORBA::TypeCode_ptr create_recursive_tc (
      const char *id,
      CORBA::Environment &ACE_TRY_ENV =
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((CORBA::SystemException));

  CORBA::TypeCode_ptr create_abstract_interface_tc (
      const char *id,
      const char *name,
      CORBA::Environment &ACE_TRY_ENV =
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((CORBA::SystemException));


  CORBA::TypeCode_ptr create_local_interface_tc (
      const char *id,
      const char *ame,
      CORBA::Environment &ACE_TRY_ENV =
        TAO_default_environment ()
    )
    ACE_THROW_SPEC ((CORBA::SystemException));

#endif /* TAO_HAS_MINIMUM_CORBA */

  // = ORB event loop methods.

  /**
   * Instructs the ORB to initialize itself and run its event loop in
   * the current thread, not returning until the ORB has shut down.
   * If an error occurs during initialization or at run-time, a CORBA
   * system exception will be thrown.
   */
  void run (CORBA::Environment &ACE_TRY_ENV = TAO_default_environment ());

  /**
   * Instructs the ORB to initialize itself and run its event loop in
   * the current thread, not returning until the ORB has shut down or
   * the time value specified through <tv> has expired.  If an error
   * occurs during initialization or at run-time, a CORBA system
   * exception will be thrown.  <tv> is reduced by the amount of time
   * spent in this call.
   **/
  void run (ACE_Time_Value &tv,
            CORBA::Environment &ACE_TRY_ENV = TAO_default_environment ());

  /**
   * Instructs the ORB to initialize itself and run its event loop in
   * the current thread, not returning until the ORB has shut down or
   * the time value specified through <tv> has expired.  If an error
   * occurs during initialization or at run-time, a CORBA system
   * exception will be thrown.  <tv> is reduced by the amount of time
   * spent in this call.  If <tv> is 0, it means that the timeout is
   * infinite.  If <tv> is ACE_Time_Value::zero, it specifies to poll
   * and does not block.
   **/
  void run (ACE_Time_Value *tv,
            CORBA::Environment &ACE_TRY_ENV = TAO_default_environment ());

  /// Returns an indication of whether the ORB needs to perform some
  /// work.
  CORBA::Boolean work_pending (CORBA_Environment &ACE_TRY_ENV =
                               TAO_default_environment ());

  /// Returns an indication of whether the ORB needs to perform some work
  /// but will look for work pending for no more than the specified time.
  /// This is useful for implementing an event loop with an idle timeout.
  CORBA::Boolean work_pending (ACE_Time_Value &tv,
                               CORBA_Environment &ACE_TRY_ENV =
                               TAO_default_environment ());

  /**
   * This operation performs an implementation-defined unit of work.
   * Note that the default behavior is to block if the unit of work is
   * not present; this behavior can be modified by passing an
   * appropriate <ACE_Time_Value> as described in run().
   **/
  void perform_work (CORBA_Environment &ACE_TRY_ENV =
                     TAO_default_environment ());
  void perform_work (ACE_Time_Value &,
                     CORBA_Environment &ACE_TRY_ENV =
                     TAO_default_environment ());
  void perform_work (ACE_Time_Value *,
                     CORBA_Environment &ACE_TRY_ENV =
                     TAO_default_environment ());

  /**
   * This operation instructs the ORB to shut down. Shutting down the
   * ORB causes all Object Adapters to be shut down. If
   * <wait_for_completion> parameter is TRUE, this operation blocks
   * until all ORB processing (including request processing and object
   * deactivation or other operations associated with object adapters)
   * has completed.
   */
  void shutdown (CORBA::Boolean wait_for_completion = 0,
                 CORBA::Environment &ACE_TRY_ENV = TAO_default_environment ());

  /**
   * Explicitly destroy the ORB, releasing any resources.  Note that
   * TAO *cannot* implicitly release the resources even if you have
   * destroyed all the references to a particular ORB since
   * CORBA::ORB_init() is required to return the same pointer if
   * called with the same ORBid, only after ORB::destroy() is called
   * it may return a new one.
   *
   * The results of multi-threaded applications, trying to destroy ()
   * the ORB in one thread and trying to service a request in another
   * thread are not well defined. TAO does not support such cases.  */
  void destroy (CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ());

  CORBA_Object_ptr resolve_initial_references (const char *name,
                                               CORBA_Environment &ACE_TRY_ENV =
                                               TAO_default_environment ());

  /**
   * This method acts as a mini-bootstrapping Naming Service, which is
   * provided by the ORB for certain well-known object references.  TAO
   * supports the "NameService", "TradingService", "RootPOA", "ImplRepo",
   * and "POACurrent" via this method.  The <timeout> value bounds the
   * amount of time the ORB blocks waiting to resolve the service.
   * This is most useful for bootstrapping remote services, such as
   * the "NameService" or "TradingService", that are commonly resolved
   * via multicast.  By default, the value is 0, which means "use the
   * <TAO_DEFAULT_SERVICE_RESOLUTION_TIMEOUT> timeout period".  Note
   * that by using a default value for the <timeout> parameter, TAO
   * will remains compliant with the CORBA
   * <resolve_initial_references> specification.
   */
  CORBA_Object_ptr resolve_initial_references (const char *name,
                                               ACE_Time_Value *timeout,
                                               CORBA_Environment &ACE_TRY_ENV =
                                               TAO_default_environment ());

  /// Returns a sequence of ObjectIds that lists which objects have
  /// references available via the initial references mechanism.
  CORBA_ORB_ObjectIdList_ptr list_initial_services (
              CORBA_Environment &ACE_TRY_ENV = TAO_default_environment ());

  CORBA::Policy_ptr create_policy (CORBA::PolicyType type,
                                   const CORBA::Any& val,
                                   CORBA_Environment &ACE_TRY_ENV =
                                       TAO_default_environment ());

  // ----------------------------------------------------------------
  // = TAO-specific extensions to the CORBA specification.
  // ----------------------------------------------------------------

  /// Resolve the POA.
  CORBA_Object_ptr resolve_root_poa (CORBA_Environment &ACE_TRY_ENV);

  /// Initialize the ORB globals correctly, i.e., only when they
  /// haven't been initialized yet.
  static void init_orb_globals (CORBA_Environment &ACE_TRY_ENV =
                                    TAO_default_environment ());

  // The function used by tao to handle the "unexpected" exceptions,
  // It raises CORBA::UNKNOWN.
  static void _tao_unexpected_exception (void);

  // Reference counting...
  CORBA::ULong _incr_refcnt (void);
  CORBA::ULong _decr_refcnt (void);

  /// Set the IOR flag.
  /// Get the IOR flag.
  void _use_omg_ior_format (CORBA::Boolean ior);
  CORBA::Boolean _use_omg_ior_format (void);

  /// Set collocation optimization status.
  /// Get collocation optimization status.
  void _optimize_collocation_objects (CORBA::Boolean opt);
  CORBA::Boolean _optimize_collocation_objects (void) const;

  /// Get the ORB core.
  TAO_ORB_Core *orb_core (void) const;

  /**
   * TAO specific extension to get and set the client ID. The client
   * id can be set by the application which would be used by the FT
   * service. As there are no specific interfaces defined in the spec,
   * we have this prorpietary extensions
   */
  const ACE_CString &_tao_ft_client_id (void);
  void _tao_ft_client_id (const char *id);

#if !defined(__GNUC__) || __GNUC__ > 2 || __GNUC_MINOR__ >= 8
  typedef CORBA_ORB_ptr _ptr_type;
  typedef CORBA_ORB_var _var_type;
#endif /* __GNUC__ */
  // Useful for template programming.

protected:
  // We must be created via the <ORB_init> call.
  CORBA_ORB (TAO_ORB_Core *orb_core);
  ~CORBA_ORB (void);

  /// Resolve the POA current.
  CORBA_Object_ptr resolve_poa_current (CORBA_Environment &ACE_TRY_ENV);

  /// Resolve the Policy Manager for this ORB.
  CORBA_Object_ptr resolve_policy_manager (CORBA::Environment&);

  /// Resolve the Policy Current for this thread.
  CORBA_Object_ptr resolve_policy_current (CORBA::Environment&);

private:

  /// Resolve the given service based on the service ID.
  CORBA_Object_ptr resolve_service (MCAST_SERVICEID service_id,
                                    ACE_Time_Value *timeout,
                                    CORBA::Environment& ACE_TRY_ENV);

  /// Convert an OMG IOR into an object reference.
  CORBA::Object_ptr ior_string_to_object (const char* ior,
                                          CORBA::Environment &ACE_TRY_ENV);

  /// Convert an URL style IOR into an object reference.
  CORBA::Object_ptr url_ior_string_to_object (const char* ior,
                                              CORBA::Environment &ACE_TRY_ENV);

  /// Check if ORB has shutdown.  If it has, throw an exception.
  void check_shutdown (CORBA::Environment &ACE_TRY_ENV);

private:
  /// lock required for mutual exclusion between multiple threads.
  TAO_SYNCH_MUTEX lock_;

  /// Maintains a reference count of number of instantiations of the
  /// ORB.
  u_int refcount_;

  /// Count of the number of times that <ORB_init> has been called.
  static int orb_init_count_;
  // This must be protected by <ACE_Static_Object_Lock>.

  /// The ORB_Core that created us....
  TAO_ORB_Core *orb_core_;

#if defined (TAO_HAS_VALUETYPE)
  /// If non-0 then this is the Factory for OBV unmarshaling
  TAO_ValueFactory_Map *valuetype_factory_map_;
#endif /* TAO_HAS_VALUETYPE */

  /// Decides whether to use the URL notation or to use IOR notation.
  CORBA::Boolean use_omg_ior_format_;

  // = NON-PROVIDED METHODS
  CORBA_ORB (const CORBA_ORB &);
  CORBA_ORB &operator= (const CORBA_ORB &);
};

class TAO_Export CORBA_ORB_var
{
public:
  CORBA_ORB_var (void); // default constructor
  CORBA_ORB_var (CORBA::ORB_ptr);
  CORBA_ORB_var (const CORBA_ORB_var &); // copy constructor
  ~CORBA_ORB_var (void); // destructor

  CORBA_ORB_var &operator= (CORBA::ORB_ptr);
  CORBA_ORB_var &operator= (const CORBA_ORB_var &);
  CORBA::ORB_ptr operator-> (void) const;

  /// in, inout, out, _retn
  operator const CORBA::ORB_ptr &() const;
  operator CORBA::ORB_ptr &();
  CORBA::ORB_ptr in (void) const;
  CORBA::ORB_ptr &inout (void);
  CORBA::ORB_ptr &out (void);
  CORBA::ORB_ptr _retn (void);
  CORBA::ORB_ptr ptr (void) const;

private:
  CORBA::ORB_ptr ptr_;
};

class TAO_Export CORBA_ORB_out
{
public:
  CORBA_ORB_out (CORBA::ORB_ptr &);
  CORBA_ORB_out (CORBA_ORB_var &);
  CORBA_ORB_out (const CORBA_ORB_out &);
  CORBA_ORB_out &operator= (CORBA_ORB_out &);
  CORBA_ORB_out &operator= (const CORBA_ORB_var &);
  CORBA_ORB_out &operator= (CORBA::ORB_ptr);
  operator CORBA::ORB_ptr &();
  CORBA::ORB_ptr &ptr (void);
  CORBA::ORB_ptr operator-> (void);

private:
  CORBA::ORB_ptr &ptr_;
};

TAO_Export void
operator<<= (CORBA::Any &, const CORBA::ORB::InvalidName &);
TAO_Export void
operator<<= (CORBA::Any &, CORBA::ORB::InvalidName*);
TAO_Export CORBA::Boolean
operator>>= (const CORBA::Any &, CORBA::ORB::InvalidName *&);
TAO_Export CORBA::Boolean
operator<< (TAO_OutputCDR &, const CORBA::ORB::InvalidName &);
TAO_Export CORBA::Boolean
operator>> (TAO_InputCDR &, CORBA::ORB::InvalidName &);


#if defined (__ACE_INLINE__)
# include "tao/ORB.i"
#endif /* __ACE_INLINE__ */

#include "ace/post.h"
#endif /* TAO_ORB_H */
