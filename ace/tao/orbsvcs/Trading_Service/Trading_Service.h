// Trading_Service.h,v 1.8 2000/09/01 05:05:49 coryan Exp

// ========================================================================
//
// = BINARY
//    trader
//
// = FILENAME
//    Trading_Service.h
//
// = AUTHOR
//    Seth Widoff <sbw1@cs.wustl.edu>
//
// =======================================================================

#ifndef _TRADING_SERVICE_H
#define _TRADING_SERVICE_H

#include "tao/PortableServer/ORB_Manager.h"
#include "ace/Auto_Ptr.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "orbsvcs/IOR_Multicast.h"
#include "orbsvcs/Trader/Trader.h"
#include "orbsvcs/Trader/Service_Type_Repository.h"
#include "orbsvcs/Trader/Trading_Loader.h"

class Trading_Service;

class Trading_Shutdown : public ACE_Event_Handler
{
  // = TITLE
  //   A class that shutsdown a Trading Service instance.
public:
  Trading_Shutdown (Trading_Service& trader);
  // Constructor.

  virtual int handle_signal (int,
                             siginfo_t *,
                             ucontext_t *);
  // Signal handler.

protected:
  Trading_Service &trader_;
  ACE_Sig_Handler shutdown_;
};

class Trading_Service
{
  // = TITLE
  //   A class that initializes a Trading Service instance.
public:

  Trading_Service (void);
  // Default constructor.

  ~Trading_Service (void);
  // Destructor

  int init (int argc,
            char *argv[],
            CORBA::Environment &ACE_TRY_ENV);
  // Initialize the Trading Service with arguments.

  int run (CORBA::Environment &ACE_TRY_ENV);
  // Run the Trading Service.

  int shutdown (void);

protected:

  auto_ptr<TAO_Trader_Factory::TAO_TRADER> trader_;
  // Pointer to the linked trader.

  TAO_Trading_Loader trading_loader_;
  // Instance of TAO_Trading_Laoder
};

#endif /* _TRADING_SERVICE_H */
