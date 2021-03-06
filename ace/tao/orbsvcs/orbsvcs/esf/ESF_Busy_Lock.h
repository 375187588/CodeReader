/* -*- C++ -*- */
/**
 *  @file   ESF_Busy_Lock.h
 *
 *  ESF_Busy_Lock.h,v 1.3 2000/10/31 03:11:12 coryan Exp
 *
 *  @author Carlos O'Ryan (coryan@cs.wustl.edu)
 *
 *  http://doc.ece.uci.edu/~coryan/EC/index.html
 */

#ifndef TAO_ESF_BUSY_LOCK_H
#define TAO_ESF_BUSY_LOCK_H

#include "ace/OS.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

/// Adapt classes that implement the "busy lock" protocol, to conform
/// to the ACE Lock interface.
/**
 * The ACE Lock interface allows us to use any mutex-like object with
 * the ACE synchronization components (such as guards, Lock_Adapter,
 * etc.). 
 * One of the synchronization protocols used in the event services
 * uses the following protocol:
 * <UL>
 * <LI> To acquire the lock the @param busy method of the object is
 *      invoked.
 * <LI> To release the lock the @param idle method of the object is
 *      invoked.
 * <LI> Any changes performed while the lock is held are delayed until
 *      all the locks are released, i.e. the last call to @param idle
 *      executes the changes.
 * </UL>
 */
template<class Adaptee>
class TAO_ESF_Busy_Lock_Adapter
{
public:
  /// Constructor
  TAO_ESF_Busy_Lock_Adapter (Adaptee* adaptee);

  // = The ACE_Lock methods, please check $ACE_ROOT/ace/Synch.h for
  // details.

  int remove (void);
  int acquire (void);
  int tryacquire (void);
  int release (void);
  int acquire_read (void);
  int acquire_write (void);
  int tryacquire_read (void);
  int tryacquire_write (void);

private:
  Adaptee* adaptee_;
};

#if defined (__ACE_INLINE__)
#include "ESF_Busy_Lock.i"
#endif /* __ACE_INLINE__ */

#if defined (ACE_TEMPLATES_REQUIRE_SOURCE)
#include "ESF_Busy_Lock.cpp"
#endif /* ACE_TEMPLATES_REQUIRE_SOURCE */

#if defined (ACE_TEMPLATES_REQUIRE_PRAGMA)
#pragma implementation ("ESF_Busy_Lock.cpp")
#endif /* ACE_TEMPLATES_REQUIRE_PRAGMA */

#endif /* TAO_ESF_BUSY_LOCK_H */
