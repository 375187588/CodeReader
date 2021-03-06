// This may look like C, but it's really -*- C++ -*-

//=============================================================================
/**
 *  @file     default_server.h
 *
 *  default_server.h,v 1.47 2001/07/11 21:43:51 oci Exp
 *
 *  @author  Chris Cleeland
 */
//=============================================================================


#ifndef TAO_DEFAULT_SERVER_FACTORY_H
#define TAO_DEFAULT_SERVER_FACTORY_H
#include "ace/pre.h"

#include "tao/Server_Strategy_Factory.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/Service_Config.h"

/**
 * @class TAO_Default_Server_Strategy_Factory
 *
 * @brief This is the default strategy factory for CORBA servers.  It
 * allows developers to choose strategies via argument flags.
 * This design gives substantial freedom for experimentation.
 *
 */
class TAO_Export TAO_Default_Server_Strategy_Factory : public TAO_Server_Strategy_Factory
{


public:
  // = Initialization and termination methods.
  TAO_Default_Server_Strategy_Factory (void);
  virtual ~TAO_Default_Server_Strategy_Factory (void);

  // = Service Configurator hooks.
  virtual int init (int argc, char *argv[]);

  // = The TAO_Server_Strategy_Factory methods, please read the
  //   documentation in "tao/Server_Strategy_Factory.h"
  virtual int open (TAO_ORB_Core*);
  virtual int enable_poa_locking (void);
  virtual int activate_server_connections (void);
  virtual int thread_per_connection_timeout (ACE_Time_Value &timeout);
  virtual int server_connection_thread_flags (void);
  virtual int server_connection_thread_count (void);

  /// Parse the arguments, check the documentation in
  /// $TAO_ROOT/docs/Options.html for details
  int parse_args (int argc, char *argv[]);

protected:
  void tokenize (char *flag_string);

  void report_option_value_error (const char* option_name,
                                  const char* option_value);

protected:
  /// Should the server connection handlers run in their own thread?
  int activate_server_connections_;

  /// Default thread flags passed to thr_create().
  u_long thread_flags_;

  enum Lock_Type
  {
    TAO_NULL_LOCK,
    TAO_THREAD_LOCK
  };

  /// The type of lock to be returned by <create_poa_lock()>.
  Lock_Type poa_lock_type_;

  /// The timeout flag and value for the thread-per-connection model
  int thread_per_connection_use_timeout_;
  ACE_Time_Value thread_per_connection_timeout_;
};

#if defined (__ACE_INLINE__)
# include "tao/default_server.i"
#endif /* __ACE_INLINE__ */

ACE_STATIC_SVC_DECLARE_EXPORT (TAO, TAO_Default_Server_Strategy_Factory)
ACE_FACTORY_DECLARE (TAO, TAO_Default_Server_Strategy_Factory)

#include "ace/post.h"
#endif /* TAO_DEFAULT_SERVER_FACTORY_H */
