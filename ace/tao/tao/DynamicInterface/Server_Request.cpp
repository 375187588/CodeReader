// Server_Request.cpp,v 1.9 2001/05/09 21:29:29 parsons Exp

// Implementation of the Dynamic Server Skeleton Interface.

#include "Server_Request.h"

ACE_RCSID(DynamicInterface, Server_Request, "Server_Request.cpp,v 1.9 2001/05/09 21:29:29 parsons Exp")

#include "tao/NVList.h"
#include "tao/GIOP_Utils.h"
#include "tao/Marshal.h"

#if !defined (__ACE_INLINE__)
# include "Server_Request.inl"
#endif /* ! __ACE_INLINE__ */

// Reference counting for DSI ServerRequest object.

CORBA::ULong
CORBA_ServerRequest::_incr_refcnt (void)
{
  ACE_GUARD_RETURN (TAO_SYNCH_MUTEX,
                    ace_mon,
                    this->lock_,
                    0);

  return this->refcount_++;
}

CORBA::ULong
CORBA_ServerRequest::_decr_refcnt (void)
{
  {
    ACE_GUARD_RETURN (TAO_SYNCH_MUTEX,
                      ace_mon,
                      this->lock_,
                      0);

    this->refcount_--;

    if (this->refcount_ != 0)
      {
        return this->refcount_;
      }
  }

  delete this;
  return 0;
}

CORBA_ServerRequest::CORBA_ServerRequest (
    TAO_ServerRequest &orb_server_request
  )
  : lazy_evaluation_ (0),
    ctx_ (CORBA::Context::_nil ()),
    params_ (CORBA::NVList::_nil ()),
    retval_ (0),
    exception_ (0),
    refcount_ (1),
    orb_server_request_ (orb_server_request),
    sent_gateway_exception_ (0)
{
  this->orb_server_request_.is_dsi ();
}

CORBA_ServerRequest::~CORBA_ServerRequest (void)
{
  if (this->params_ != 0)
    {
      CORBA::release (this->params_);
    }

  delete this->retval_;
  delete this->exception_;
}

// Unmarshal in/inout params, and set up to marshal the appropriate
// inout/out/return values later on.
void
CORBA_ServerRequest::arguments (CORBA::NVList_ptr &list,
                                CORBA::Environment &ACE_TRY_ENV)
{
  // arguments() must be called before either of these.
  if (this->params_ != 0 || this->exception_ != 0)
    {
      ACE_THROW (CORBA::BAD_INV_ORDER (7, CORBA::COMPLETED_NO));
    }

  // Save params for later use when marshaling the reply.
  this->params_ = list;

  this->params_->_tao_incoming_cdr (this->orb_server_request_.incoming (),
                                    CORBA::ARG_IN | CORBA::ARG_INOUT,
                                    this->lazy_evaluation_,
                                    ACE_TRY_ENV);

  // Pass this alignment back to the TAO_ServerRequest.
  this->orb_server_request_.dsi_nvlist_align (
                                this->params_->_tao_target_alignment ()
                              );
}

// Store the result value.  There's either an exception, or a result,
// but not both of them.  Results can be reported (at most once)
// only after the parameter list has been provided (maybe empty).
void
CORBA_ServerRequest::set_result (const CORBA::Any &value,
                                 CORBA::Environment &ACE_TRY_ENV)
{
  // Setting a result when another result already exists or if an exception
  // exists or before the args have been processeed is an error.
  if (this->retval_ != 0 || this->exception_ != 0 || this->params_ == 0)
    {
      ACE_THROW (CORBA::BAD_INV_ORDER (8, CORBA::COMPLETED_NO));
    }

  ACE_NEW_THROW_EX (this->retval_,
                    CORBA::Any (value),
                    CORBA::NO_MEMORY ());
  ACE_CHECK;
}

  // NOTE: if "ACE_TRY_ENV" is set, there has been a system exception,
  // and it will take precedence over exceptions reported using the
  // set_exception() mechanism of the ServerRequest, which we assume
  // the application writer will use to report only user exceptions.
  // If both types of exception happen on the same invocation, the user
  // exception will be lost.

// Store the exception value.
void
CORBA_ServerRequest::set_exception (const CORBA::Any &value,
                                    CORBA::Environment &ACE_TRY_ENV)
{
  CORBA::TypeCode_var tc = value.type ();

  // set_exception() can be called at any time, but the Any arg MUST
  // contain an exception.
  if (tc->kind () != CORBA::tk_except)
    {
      ACE_THROW (CORBA::BAD_PARAM (21, CORBA::COMPLETED_MAYBE));
    }

  ACE_NEW_THROW_EX (this->exception_,
                    CORBA::Any (value),
                    CORBA::NO_MEMORY ());
  ACE_CHECK;

  this->orb_server_request_.exception_type (TAO_GIOP_USER_EXCEPTION);
}

// This method will be utilized by the DSI servant to marshal outgoing
// parameters.
void
CORBA_ServerRequest::dsi_marshal (CORBA::Environment &ACE_TRY_ENV)
{
  // There was a user exception, no need to marshal any parameters.
  if (this->sent_gateway_exception_)
    {
      return;
    }

  if (this->orb_server_request_.exception_type () == TAO_GIOP_NO_EXCEPTION)
    {
      // In DSI, we can't rely on the skeleton to do this.
      if (this->retval_ == 0 && this->params_ == 0)
        {
          this->orb_server_request_.argument_flag (0);
        }

      this->orb_server_request_.init_reply ();

      // Send the return value, if any.
      if (this->retval_ != 0)
        {
          this->retval_->_tao_encode (
                             this->orb_server_request_.outgoing (),
                             this->orb_server_request_.orb_core (),
                             ACE_TRY_ENV
                           );
          ACE_CHECK;
        }

      // Send the "inout" and "out" parameters.
      if (this->params_ != 0)
        {
          this->params_->_tao_encode (
                             this->orb_server_request_.outgoing (),
                             this->orb_server_request_.orb_core (),
                             CORBA::ARG_INOUT | CORBA::ARG_OUT,
                             ACE_TRY_ENV
                           );
          ACE_CHECK;
        }
    }
  else
    {
      // This defaults to 1, but just to be safe...
      this->orb_server_request_.argument_flag (1);

      // Write the reply header to the ORB request's outgoing CDR stream.
      this->orb_server_request_.init_reply ();

      this->exception_->_tao_encode (
                            this->orb_server_request_.outgoing (),
                            this->orb_server_request_.orb_core (),
                            ACE_TRY_ENV
                          );
      ACE_CHECK;
    }

  this->orb_server_request_.tao_send_reply ();
}

void
CORBA_ServerRequest::gateway_exception_reply (ACE_CString &raw_exception)
{
  // This defaults to 1, but just to be safe...
  this->orb_server_request_.argument_flag (1);

  // This reply path handles only user exceptions.
  this->orb_server_request_.exception_type (TAO_GIOP_USER_EXCEPTION);

  this->orb_server_request_.init_reply ();

  // We know nothing about this exception, so we marshal it as a block
  // of bytes. The outgoing stream's byte order has already been matched
  // to the original source of the reply.
  this->orb_server_request_.outgoing ().write_octet_array (
      ACE_reinterpret_cast (const CORBA::Octet *, raw_exception.fast_rep ()),
      raw_exception.length () + ACE_CDR::MAX_ALIGNMENT
    );

  // This will prevent the marshaling of any parameters into this reply.
  this->sent_gateway_exception_ = 1;

  this->orb_server_request_.tao_send_reply ();
}

