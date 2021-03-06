// -*- C++ -*-

//==========================================================================
/**
 * @file SHMIOP_Endpoint.h
 *
 * SHMIOP_Endpoint.h,v 1.4 2001/07/09 09:07:36 othman Exp
 *
 * SHMIOP implementation of PP Framework Endpoint interface.
 *
 *
 * @author Marina Spivak <marina@cs.wustl.edu>
 */
//==========================================================================

#ifndef TAO_SHMIOP_ENDPOINT_H
#define TAO_SHMIOP_ENDPOINT_H
#include "ace/pre.h"

#include "tao/Endpoint.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#if defined (TAO_HAS_SHMIOP) && (TAO_HAS_SHMIOP != 0)

#include "strategies_export.h"

#include "tao/ORB.h"

#include "ace/INET_Addr.h"
#include "ace/MEM_Addr.h"



/**
 * @class TAO_SHMIOP_Endpoint
 *
 * @brief TAO_SHMIOP_Endpoint
 *
 * SHMIOP-specific implementation of PP Framework Endpoint interface.
 */
class TAO_Strategies_Export TAO_SHMIOP_Endpoint : public TAO_Endpoint
{
public:

  friend class TAO_SHMIOP_Profile;

  // = Initialization and termination methods.

  /// Default constructor.
  TAO_SHMIOP_Endpoint (void);

  /// Constructor.  This is the most efficient constructor since it
  /// does not require any address resolution processing.
  TAO_SHMIOP_Endpoint (const char *host,
                       CORBA::UShort port,
                       const ACE_INET_Addr &addr);

  /// Constructor.
  TAO_SHMIOP_Endpoint (const ACE_MEM_Addr &addr,
                       int use_dotted_decimal_addresses);

  /// Constructor. -- More of a extension of the previous one. One of
  /// them need to go. We will decide about that as time goes by.
  TAO_SHMIOP_Endpoint (const ACE_INET_Addr &addr,
                       int use_dotted_decimal_addresses);

  /// Constructor.  This constructor is used when decoding endpoints.
  TAO_SHMIOP_Endpoint (const char *host,
                       CORBA::UShort port,
                       CORBA::Short priority);

  /// Destructor.
  ~TAO_SHMIOP_Endpoint (void);

  // = Implementation of abstract TAO_Endpoint methods.  See
  // Endpoint.h for their documentation.

  /// Return a copy of <this>
  virtual TAO_Endpoint *next (void);
  virtual int addr_to_string (char *buffer, size_t length);
  virtual void reset_hint (void);
  virtual TAO_Endpoint *duplicate (void);

  /// Return true if this endpoint is equivalent to <other_endpoint>.  Two
  /// endpoints are equivalent iff their port and host are the same.
  CORBA::Boolean is_equivalent (const TAO_Endpoint *other_endpoint);

  /// Return a hash value for this object.
  CORBA::ULong hash (void);

  // = SHMIOP_Endpoint-specific methods.

  /// Return a reference to the <object_addr>.
  const ACE_INET_Addr &object_addr (void) const;

  /// Return a pointer to the host string.  This object maintains
  /// ownership of this string.
  const char *host (void) const;

  /// Copy the string <h> into <host_> and return the resulting pointer.
  /// This object maintains ownership of this string.
  const char *host (const char *h);

  /// Return the port number.
  CORBA::UShort port (void) const;

  /// Set the port number.
  CORBA::UShort port (CORBA::UShort p);

private:
  /// Helper method for setting INET_Addr.
  int set (const ACE_INET_Addr &addr,
           int use_dotted_decimal_addresses);

  /// String representing the host name.
  CORBA::String_var host_;

  /// TCP port number.
  CORBA::UShort port_;

  /// Cached instance of <ACE_INET_Addr> for use in making
  /// invocations, etc.
  ACE_INET_Addr object_addr_;

  /// SHMIOP Endpoints can be stringed into a list.  Return the next
  /// endpoint in the list, if any.
  TAO_SHMIOP_Endpoint *next_;
};

#if defined (__ACE_INLINE__)
# include "SHMIOP_Endpoint.i"
#endif /* __ACE_INLINE__ */

#endif /* TAO_HAS_SHMIOP && TAO_HAS_SHMIOP != 0 */

#include "ace/post.h"
#endif  /* TAO_IIOP_PROFILE_H */
