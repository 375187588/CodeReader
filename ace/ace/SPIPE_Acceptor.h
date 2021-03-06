/* -*- C++ -*- */

//=============================================================================
/**
 *  @file    SPIPE_Acceptor.h
 *
 *  SPIPE_Acceptor.h,v 4.15 2001/09/28 13:52:50 schmidt Exp
 *
 *  @author Doug Schmidt and Prashant Jain
 */
//=============================================================================


#ifndef ACE_SPIPE_ACCEPTOR_H
#define ACE_SPIPE_ACCEPTOR_H
#include "ace/pre.h"

#include "ace/SPIPE_Stream.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#if defined (ACE_WIN32)
#include "ace/Synch.h"
#endif /* ACE_WIN32 */

/**
 * @class ACE_SPIPE_Acceptor
 *
 * @brief Defines the format and interface for the listener side of the
 * ACE_SPIPE_Stream.
 */
class ACE_Export ACE_SPIPE_Acceptor : public ACE_SPIPE
{
public:
  // = Initialization and termination methods.
  /// Default constructor.
  ACE_SPIPE_Acceptor (void);

  /// Initiate a passive-mode STREAM pipe listener.
  ACE_SPIPE_Acceptor (const ACE_SPIPE_Addr &local_sap,
                      int reuse_addr = 1,
                      int perms = ACE_DEFAULT_FILE_PERMS);

  /// Initiate a passive-mode STREAM pipe listener.
  int open (const ACE_SPIPE_Addr &local_sap,
            int reuse_addr = 1,
            int perms = ACE_DEFAULT_FILE_PERMS);

  /// Close down the passive-mode STREAM pipe listener.
  int close (void);

  /// Remove the underlying mounted pipe from the file system.
  int remove (void);

  // = Passive connection acceptance method.
  /**
   * Accept a new data transfer connection.  A <timeout> of 0 means
   * block forever, a <timeout> of {0, 0} means poll.  <restart> == 1
   * means "restart if interrupted."
   */
  int accept (ACE_SPIPE_Stream &ipc_sap_spipe,
              ACE_SPIPE_Addr *remote_addr = 0,
              ACE_Time_Value *timeout = 0,
              int restart = 1,
              int reset_new_handle = 0);

  // = Meta-type info
  typedef ACE_SPIPE_Addr PEER_ADDR;
  typedef ACE_SPIPE_Stream PEER_STREAM;

  /// Dump the state of an object.
  void dump (void) const;

  /// Declare the dynamic allocation hooks.
  ACE_ALLOC_HOOK_DECLARE;

private:
  /// Create a new instance of an SPIPE.
  int create_new_instance (int perms = 0);

#if (defined (ACE_WIN32) && defined (ACE_HAS_WINNT4) && (ACE_HAS_WINNT4 != 0))
  ACE_OVERLAPPED overlapped_;
  ACE_Manual_Event event_;
  int already_connected_;
#endif /* ACE_WIN32 */

};

#include "ace/post.h"
#endif /* ACE_SPIPE_ACCEPTOR_H */
