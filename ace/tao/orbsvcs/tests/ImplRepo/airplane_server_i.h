// -*- C++ -*-

//=============================================================================
/**
 *  @file    airplane_server_i.h
 *
 *  airplane_server_i.h,v 1.9 2000/11/10 20:51:20 brunsch Exp
 *
 *  Server that sets up the ORB and handles the registration and execution
 *  of the Paper Airplane Server.
 *
 *
 *  @author Darrell Brunsch <brunsch@cs.wustl.edu>
 */
//=============================================================================


#if !defined (AIRPLANE_SERVER_I_H)
#define AIRPLANE_SERVER_I_H

#include "tao/corba.h"
#include "airplane_i.h"

/**
 * @class Airplane_Server_i
 *
 * @brief Paper Airplane Server Implementation Class
 *
 * Sets up everything necessary to get the Paper Airplane Server 
 * running.
 */
class Airplane_Server_i
{
public:
  // = Initialization and termination methods.
  /// Default constructor
  Airplane_Server_i (void);

  /// Destructor
  ~Airplane_Server_i (void);

  /// Initialize the Server state - parsing arguments and waiting
  int init (int argc, char **argv, CORBA::Environment &ACE_TRY_ENV);

  /// Run the orb 
  int run (CORBA::Environment &ACE_TRY_ENV);

private:
  /// Parses the commandline arguments.
  int parse_args (void);

  /// Number of command line arguments.
  int argc_;

  /// The command line arguments.
  char **argv_;

  /// The ORB.
  CORBA::ORB_var orb_;

  /// The POA for the Airplane Server.
  PortableServer::POA_var airplane_poa_;

  /// The POA manager.
  PortableServer::POAManager_var poa_manager_;

  /// The Paper Airplane Server Implementation.  
  Airplane_i *server_impl_;

  /// File where the IOR of the server object is stored.
  FILE *ior_output_file_;
};

#endif /* AIRPLANE_SERVER_I_H */
