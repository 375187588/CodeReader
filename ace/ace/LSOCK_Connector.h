/* -*- C++ -*- */

//=============================================================================
/**
 *  @file    LSOCK_Connector.h
 *
 *  LSOCK_Connector.h,v 4.11 2001/03/07 12:32:16 schmidt Exp
 *
 *  @author Doug Schmidt <schmidt@cs.wustl.edu>
 */
//=============================================================================

#ifndef ACE_LOCAL_SOCK_CONNECTOR_H
#define ACE_LOCAL_SOCK_CONNECTOR_H
#include "ace/pre.h"

#include "ace/SOCK_Connector.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/LSOCK_Stream.h"
#include "ace/UNIX_Addr.h"

#if !defined (ACE_LACKS_UNIX_DOMAIN_SOCKETS)

/**
 * @class ACE_LSOCK_Connector
 *
 * @brief Defines the format and interface for the connector side of
 * the <ACE_LSOCK_Stream>.
 */
class ACE_Export ACE_LSOCK_Connector : public ACE_SOCK_Connector
{
public:
  // = Initialization methods.
  /// Default constructor.
  ACE_LSOCK_Connector (void);

  /**
   * Actively connect and produce a <new_stream> if things go well.
   * The <remote_sap> is the address that we are trying to connect
   * with.  The <timeout> is the amount of time to wait to connect.
   * If it's 0 then we block indefinitely.  If *timeout == {0, 0} then
   * the connection is done using non-blocking mode.  In this case, if
   * the connection can't be made immediately the value of -1 is
   * returned with <errno == EWOULDBLOCK>.  If *timeout > {0, 0} then
   * this is the maximum amount of time to wait before timing out.  If the
   * time expires before the connection is made <errno == ETIME>.  The
   * <local_sap> is the value of local address to bind to.  If it's
   * the default value of <ACE_Addr::sap_any> then the user is letting
   * the OS do the binding.  If <reuse_addr> == 1 then the
   * <local_addr> is reused, even if it hasn't been cleanedup yet.
   */
  ACE_LSOCK_Connector (ACE_LSOCK_Stream &new_stream,
                       const ACE_UNIX_Addr &remote_sap,
                       ACE_Time_Value *timeout = 0,
                       const ACE_Addr &local_sap = ACE_Addr::sap_any,
                       int reuse_addr = 0,
                       int flags = 0,
                       int perms = 0,
                       int protocol_family = PF_UNIX,
                       int protocol = 0);

  /**
   * Actively connect and produce a <new_stream> if things go well.
   * The <remote_sap> is the address that we are trying to connect
   * with.  The <timeout> is the amount of time to wait to connect.
   * If it's 0 then we block indefinitely.  If *timeout == {0, 0} then
   * the connection is done using non-blocking mode.  In this case, if
   * the connection can't be made immediately the value of -1 is
   * returned with <errno == EWOULDBLOCK>.  If *timeout > {0, 0} then
   * this is the maximum amount of time to wait before timing out.  If the
   * time expires before the connection is made <errno == ETIME>.  The
   * <local_sap> is the value of local address to bind to.  If it's
   * the default value of <ACE_Addr::sap_any> then the user is letting
   * the OS do the binding.  If <reuse_addr> == 1 then the
   * <local_addr> is reused, even if it hasn't been cleanedup yet.
   */
  int connect (ACE_LSOCK_Stream &new_stream,
               const ACE_UNIX_Addr &remote_sap,
               ACE_Time_Value *timeout = 0,
               const ACE_Addr &local_sap = ACE_Addr::sap_any,
               int reuse_addr = 0,
               int flags = 0,
               int perms = 0,
               int protcol_family = PF_UNIX,
               int protocol = 0);

  // = Meta-type info
  typedef ACE_UNIX_Addr PEER_ADDR;
  typedef ACE_LSOCK_Stream PEER_STREAM;

  /// Dump the state of an object.
  void dump (void) const;

  /// Declare the dynamic allocation hooks.
  ACE_ALLOC_HOOK_DECLARE;
};

#if !defined (ACE_LACKS_INLINE_FUNCTIONS)
#include "ace/LSOCK_Connector.i"
#endif

#endif /* ACE_LACKS_UNIX_DOMAIN_SOCKETS */
#include "ace/post.h"
#endif /* ACE_LOCAL_SOCK_CONNECTOR_H */
