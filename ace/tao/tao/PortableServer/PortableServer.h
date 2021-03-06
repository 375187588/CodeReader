/* -*- C++ -*- */

// PortableServer.h,v 1.5 2001/06/12 18:58:21 fhunleth Exp

// =========================================================================
//
// = LIBRARY
//    TAO
//
// = FILENAME
//    Portableserver.h
//
// = AUTHOR
//    Carlos O'Ryan <coryan@uci.edu>
//
// =========================================================================

#ifndef TAO_PORTABLESERVER_H
#define TAO_PORTABLESERVER_H
#include "ace/pre.h"

#include "portableserver_export.h"
#include "tao/corbafwd.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

class TAO_PortableServer_Export TAO_POA_Initializer
{
public:
  static int init (void);
  // Used to force the initialization of the ORB code.
};

#if defined(ACE_HAS_BROKEN_STATIC_CONSTRUCTORS)

typedef int (*TAO_Module_Initializer) (void);

static TAO_Module_Initializer
TAO_Requires_POA_Initializer = &TAO_POA_Initializer::init;

#else

static int
TAO_Requires_POA_Initializer = TAO_POA_Initializer::init ();

#endif /* ACE_HAS_BROKEN_STATIC_CONSTRUCTORS */

#define TAO_PORTABLESERVER_SAFE_INCLUDE
#include "PortableServerC.h"
#undef TAO_PORTABLESERVER_SAFE_INCLUDE

#include "ace/post.h"
#endif /* TAO_PORTABLESERVER_H */
