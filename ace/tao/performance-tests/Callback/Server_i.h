// Server_i.h,v 1.3 2001/05/20 17:38:48 fhunleth Exp

#ifndef TAO_SERVER_I_H
#define TAO_SERVER_I_H

#include "callbackS.h"

/// Implement the Test::Server interface
class Server_i : public POA_Test::Server
{
public:
  /// Constructor.
  Server_i (void);

  /// Return 1 when the shutdown method has been invoked.
  int done (void);

  /// Implement the CORBA methods
  //@{
  void set_callback (Test::Callback_ptr callback,
                     CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException));

  void request (Test::TimeStamp,
                const Test::Payload &,
                CORBA::Environment &)
    ACE_THROW_SPEC ((CORBA::SystemException));

  void shutdown (CORBA::Environment&)
    ACE_THROW_SPEC ((CORBA::SystemException));

  //@}

private:
  /// A flag to terminate the event loop
  int done_;

  /// The callback object
  Test::Callback_var callback_;
};

#if defined(__ACE_INLINE__)
#include "Server_i.inl"
#endif /* __ACE_INLINE__ */

#endif /* TAO_SERVER_I_H */
