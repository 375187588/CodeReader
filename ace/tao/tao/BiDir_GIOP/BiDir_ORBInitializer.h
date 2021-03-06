// -*- C++ -*-
//
// ===================================================================
/**
 *  @file BiDir_ORBInitializer.h
 *
 *  BiDir_ORBInitializer.h,v 1.2 2001/03/30 19:52:13 bala Exp
 *
 *  @author Balachandran Natarajan <bala@cs.wustl.edu>
 */
// ===================================================================
#ifndef TAO_BIDIR_ORB_INITIALIZER_H
#define TAO_BIDIR_ORB_INITIALIZER_H
#include "ace/pre.h"

#include "bidirgiop_export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


#include "tao/PortableInterceptorC.h"
#include "tao/LocalObject.h"
#include "tao/corbafwd.h"


// This is to remove "inherits via dominance" warnings from MSVC.
// MSVC is being a little too paranoid.
#if defined(_MSC_VER)
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif /* _MSC_VER >= 1200 */
#pragma warning(disable:4250)
#endif /* _MSC_VER */

/// Messaging ORB initializer.
class TAO_BiDirGIOP_Export TAO_BiDir_ORBInitializer :
  public virtual PortableInterceptor::ORBInitializer,
  public virtual TAO_Local_RefCounted_Object
{
public:

  virtual void pre_init (PortableInterceptor::ORBInitInfo_ptr info
                         TAO_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual void post_init (PortableInterceptor::ORBInitInfo_ptr info
                          TAO_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException));

private:

  ///< Register Messaging policy factories.
  void register_policy_factories (
         PortableInterceptor::ORBInitInfo_ptr info
         TAO_ENV_ARG_DECL);

};

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma warning(pop)
#endif /* _MSC_VER */



#include "ace/post.h"

#endif /* TAO_BIDIR_ORB_INITIALIZER_H */
