// UIOP_Acceptor.cpp,v 1.14 2001/09/18 00:05:59 irfan Exp

// ============================================================================
//
// = LIBRARY
//     TAO
//
// = FILENAME
//      UIOP_Acceptor.cpp
//
// = DESCRIPTION
//
// = AUTHOR
//     Fred Kuhns <fredk@cs.wustl.edu> and
//     Ossama Othman <othman@cs.wustl.edu>
//
// ============================================================================

#include "UIOP_Acceptor.h"

#if TAO_HAS_UIOP == 1

#include "UIOP_Profile.h"
#include "tao/MProfile.h"
#include "tao/ORB_Core.h"
#include "tao/Server_Strategy_Factory.h"
#include "tao/debug.h"
#include "tao/Protocols_Hooks.h"

ACE_RCSID(Strategies, UIOP_Acceptor, "UIOP_Acceptor.cpp,v 1.14 2001/09/18 00:05:59 irfan Exp")

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)

template class ACE_Acceptor<TAO_UIOP_Connection_Handler, ACE_LSOCK_ACCEPTOR>;
template class ACE_Strategy_Acceptor<TAO_UIOP_Connection_Handler, ACE_LSOCK_ACCEPTOR>;
template class ACE_Accept_Strategy<TAO_UIOP_Connection_Handler, ACE_LSOCK_ACCEPTOR>;
template class ACE_Creation_Strategy<TAO_UIOP_Connection_Handler>;
template class ACE_Concurrency_Strategy<TAO_UIOP_Connection_Handler>;
template class ACE_Scheduling_Strategy<TAO_UIOP_Connection_Handler>;
template class TAO_Creation_Strategy<TAO_UIOP_Connection_Handler>;
template class TAO_Concurrency_Strategy<TAO_UIOP_Connection_Handler>;
template class TAO_Accept_Strategy<TAO_UIOP_Connection_Handler, ACE_LSOCK_ACCEPTOR>;

#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)

#pragma instantiate ACE_Acceptor<TAO_UIOP_Connection_Handler, ACE_LSOCK_ACCEPTOR>
#pragma instantiate ACE_Strategy_Acceptor<TAO_UIOP_Connection_Handler, ACE_LSOCK_ACCEPTOR>
#pragma instantiate ACE_Accept_Strategy<TAO_UIOP_Connection_Handler, ACE_LSOCK_ACCEPTOR>
#pragma instantiate ACE_Creation_Strategy<TAO_UIOP_Connection_Handler>
#pragma instantiate ACE_Concurrency_Strategy<TAO_UIOP_Connection_Handler>
#pragma instantiate ACE_Scheduling_Strategy<TAO_UIOP_Connection_Handler>
#pragma instantiate TAO_Creation_Strategy<TAO_UIOP_Connection_Handler>
#pragma instantiate TAO_Concurrency_Strategy<TAO_UIOP_Connection_Handler>
#pragma instantiate TAO_Accept_Strategy<TAO_UIOP_Connection_Handler, ACE_LSOCK_ACCEPTOR>

#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */


TAO_UIOP_Acceptor::TAO_UIOP_Acceptor (CORBA::Boolean flag)
  : TAO_Acceptor (TAO_TAG_UIOP_PROFILE),
    base_acceptor_ (),
    creation_strategy_ (0),
    concurrency_strategy_ (0),
    accept_strategy_ (0),
    version_ (TAO_DEF_GIOP_MAJOR, TAO_DEF_GIOP_MINOR),
    orb_core_ (0),
    unlink_on_close_ (1),
    lite_flag_ (flag)
{
}

TAO_UIOP_Acceptor::~TAO_UIOP_Acceptor (void)
{
  // Make sure we are closed before we start destroying the
  // strategies.
  this->close ();

  delete this->creation_strategy_;
  delete this->concurrency_strategy_;
  delete this->accept_strategy_;
}

int
TAO_UIOP_Acceptor::create_profile (const TAO_ObjectKey &object_key,
                                   TAO_MProfile &mprofile,
                                   CORBA::Short priority)
{
  // Check if multiple endpoints should be put in one profile or
  // if they should be spread across multiple profiles.
  if (priority == TAO_INVALID_PRIORITY)
    return this->create_new_profile (object_key,
                                     mprofile,
                                     priority);
  else
    return this->create_shared_profile (object_key,
                                        mprofile,
                                        priority);

}

int
TAO_UIOP_Acceptor::create_new_profile (const TAO_ObjectKey &object_key,
                                       TAO_MProfile &mprofile,
                                       CORBA::Short priority)
{
  ACE_UNIX_Addr addr;

  if (this->base_acceptor_.acceptor ().get_local_addr (addr) == -1)
    return 0;

  int count = mprofile.profile_count ();
  if ((mprofile.size () - count) < 1
      && mprofile.grow (count + 1) == -1)
    return -1;

  TAO_UIOP_Profile *pfile = 0;
  ACE_NEW_RETURN (pfile,
                  TAO_UIOP_Profile (addr,
                                    object_key,
                                    this->version_,
                                    this->orb_core_),
                  -1);
  pfile->endpoint ()->priority (priority);

  if (mprofile.give_profile (pfile) == -1)
    {
      pfile->_decr_refcnt ();
      pfile = 0;
      return -1;
    }

  // Do not add any tagged components to the profile if configured
  // by the user not to do so, or if an UIOP 1.0 endpoint is being
  // created (IIOP 1.0 did not support tagged components, so we follow
  // the same convention for UIOP).
  if (this->orb_core_->orb_params ()->std_profile_components () == 0
      || (this->version_.major == 1 && this->version_.minor == 0))
    return 0;

  pfile->tagged_components ().set_orb_type (TAO_ORB_TYPE);

  CONV_FRAME::CodeSetComponentInfo code_set_info;
  code_set_info.ForCharData.native_code_set  = TAO_DEFAULT_CHAR_CODESET_ID;
  code_set_info.ForWcharData.native_code_set = TAO_DEFAULT_WCHAR_CODESET_ID;
  pfile->tagged_components ().set_code_sets (code_set_info);

  return 0;
}

int
TAO_UIOP_Acceptor::create_shared_profile (const TAO_ObjectKey &object_key,
                                          TAO_MProfile &mprofile,
                                          CORBA::Short priority)
{
  TAO_Profile *pfile = 0;
  TAO_UIOP_Profile *uiop_profile = 0;

  // First see if <mprofile> already contains a UIOP profile.
  for (TAO_PHandle i = 0; i != mprofile.profile_count (); ++i)
    {
      pfile = mprofile.get_profile (i);
      if (pfile->tag () == TAO_TAG_UIOP_PROFILE)
      {
        uiop_profile = ACE_dynamic_cast (TAO_UIOP_Profile *,
                                         pfile);
        break;
      }
    }

  if (uiop_profile == 0)
    {
      // If <mprofile> doesn't contain UIOP_Profile, we need to create
      // one.
      return create_new_profile (object_key,
                                 mprofile,
                                 priority);
    }
  else
    {
      // A UIOP_Profile already exists - just add our endpoint to it.
      ACE_UNIX_Addr addr;

      if (this->base_acceptor_.acceptor ().get_local_addr (addr) == -1)
        return 0;

      TAO_UIOP_Endpoint *endpoint = 0;
      ACE_NEW_RETURN (endpoint,
                      TAO_UIOP_Endpoint (addr),
                      -1);
      endpoint->priority (priority);
      uiop_profile->add_endpoint (endpoint);

      return 0;
    }
}

int
TAO_UIOP_Acceptor::is_collocated (const TAO_Endpoint *endpoint)
{
  const TAO_UIOP_Endpoint *endp =
    ACE_dynamic_cast (const TAO_UIOP_Endpoint *, endpoint);

  // Make sure the dynamically cast pointer is valid.
  if (endp == 0)
    return 0;

  // For UNIX Files this is relatively cheap.
  ACE_UNIX_Addr address;
  if (this->base_acceptor_.acceptor ().get_local_addr (address) == -1)
    return 0;

  return endp->object_addr () == address;
}

int
TAO_UIOP_Acceptor::close (void)
{
  if (this->unlink_on_close_)
    {
      ACE_UNIX_Addr addr;

      if (this->base_acceptor_.acceptor ().get_local_addr (addr) == 0)
        (void) ACE_OS::unlink (addr.get_path_name ());

      this->unlink_on_close_ = 0;
    }

  return this->base_acceptor_.close ();
}

int
TAO_UIOP_Acceptor::open (TAO_ORB_Core *orb_core,
                         ACE_Reactor *reactor,
                         int major,
                         int minor,
                         const char *address,
                         const char *options)
{
  this->orb_core_ = orb_core;

  if (this->init_uiop_properties () != 0)
    return -1;

  if (address == 0)
    return -1;

  if (major >= 0 && minor >= 0)
    this->version_.set_version (ACE_static_cast (CORBA::Octet,
                                                 major),
                                ACE_static_cast (CORBA::Octet,
                                                 minor));
  // Parse options
  if (this->parse_options (options) == -1)
    return -1;
  else
    return this->open_i (address,
                         reactor);
}

int
TAO_UIOP_Acceptor::open_default (TAO_ORB_Core *orb_core,
                                 ACE_Reactor *reactor,
                                 int major,
                                 int minor,
                                 const char *options)
{
  this->orb_core_ = orb_core;

  if (this->init_uiop_properties () != 0)
    return -1;

  if (major >=0 && minor >= 0)
    this->version_.set_version (ACE_static_cast (CORBA::Octet,
                                                 major),
                                ACE_static_cast (CORBA::Octet,
                                                 minor));

  // Parse options
  if (this->parse_options (options) == -1)
    return -1;

  ACE_Auto_String_Free tempname (ACE_OS::tempnam (0,
                                                  "TAO"));

  if (tempname.get () == 0)
    return -1;

  return this->open_i (tempname.get (),
                       reactor);
}

int
TAO_UIOP_Acceptor::open_i (const char *rendezvous,
                           ACE_Reactor *reactor)
{
  ACE_NEW_RETURN (this->creation_strategy_,
                  TAO_UIOP_CREATION_STRATEGY (this->orb_core_,
                                              &(this->uiop_properties_),
                                              this->lite_flag_),
                  -1);

  ACE_NEW_RETURN (this->concurrency_strategy_,
                  TAO_UIOP_CONCURRENCY_STRATEGY (this->orb_core_),
                  -1);

  ACE_NEW_RETURN (this->accept_strategy_,
                  TAO_UIOP_ACCEPT_STRATEGY (this->orb_core_),
                  -1);

  ACE_UNIX_Addr addr;

  this->rendezvous_point (addr, rendezvous);

  if (this->base_acceptor_.open (addr,
                                 reactor,
                                 this->creation_strategy_,
                                 this->accept_strategy_,
                                 this->concurrency_strategy_) == -1)
    {
      // Don't unlink an existing rendezvous point since it may be in
      // use by another UIOP server/client.
      if (errno == EADDRINUSE)
        this->unlink_on_close_ = 0;

      return -1;
    }

  (void) this->base_acceptor_.acceptor().enable (ACE_CLOEXEC);
  // This avoids having child processes acquire the listen socket thereby
  // denying the server the opportunity to restart on a well-known endpoint.
  // This does not affect the aberrent behavior on Win32 platforms.

  // @@ If Profile creation is slow we may need to cache the
  //    rendezvous point here

  if (TAO_debug_level > 5)
    ACE_DEBUG ((LM_DEBUG,
                "\nTAO (%P|%t) UIOP_Acceptor::open_i - "
                "listening on: <%s>\n",
                addr.get_path_name ()));
  return 0;
}

void
TAO_UIOP_Acceptor::rendezvous_point (ACE_UNIX_Addr &addr,
                                     const char *rendezvous)
{
  // To guarantee portability, local IPC rendezvous points (including
  // the path and filename) should not be longer than 99 characters
  // long. Some platforms may support longer rendezvous points,
  // usually 108 characters including the null terminator, but
  // Posix.1g only requires that local IPC rendezvous point arrays
  // contain a maximum of at least 100 characters, including the null
  // terminator.  If an endpoint is longer than what the platform
  // supports then it will be truncated so that it fits, and a warning
  // will be issued.

  // Avoid using relative paths in your UIOP endpoints.  If possible,
  // use absolute paths instead.  Imagine that the server is given an
  // endpoint to create using -ORBEndpoint uiop://foobar.  A local IPC
  // rendezvous point called foobar will be created in the current
  // working directory.  If the client is not started in the directory
  // where the foobar rendezvous point exists then the client will not
  // be able to communicate with the server since its point of
  // communication, the rendezvous point, was not found. On the other
  // hand, if an absolute path was used, the client would know exactly
  // where to find the rendezvous point.  It is up to the user to make
  // sure that a given UIOP endpoint is accessible by both the server
  // and the client.

  addr.set (rendezvous);

  size_t length = ACE_OS::strlen (addr.get_path_name ());

  // Check if rendezvous point was truncated by ACE_UNIX_Addr since
  // most UNIX domain socket rendezvous points can only be less than
  // 108 characters long.
  if (length < ACE_OS::strlen (rendezvous))
    ACE_DEBUG ((LM_WARNING,
                "TAO (%P|%t) UIOP rendezvous point was truncated to <%s>\n"
                "since it was longer than %d characters long.\n",
                addr.get_path_name (),
                length));
}

CORBA::ULong
TAO_UIOP_Acceptor::endpoint_count (void)
{
  return 1;
}

int
TAO_UIOP_Acceptor::object_key (IOP::TaggedProfile &profile,
                               TAO_ObjectKey &object_key)
{
  // Create the decoding stream from the encapsulation in the buffer,
#if (TAO_NO_COPY_OCTET_SEQUENCES == 1)
  TAO_InputCDR cdr (profile.profile_data.mb ());
#else
  TAO_InputCDR cdr (ACE_reinterpret_cast(char*,profile.profile_data.get_buffer ()),
                    profile.profile_data.length ());
#endif /* TAO_NO_COPY_OCTET_SEQUENCES == 1 */

    CORBA::Octet major, minor;

  // Read the version. We just read it here. We don't*do any*
  // processing.
  if (!(cdr.read_octet (major)
        && cdr.read_octet (minor)))
  {
    if (TAO_debug_level > 0)
      {
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("TAO (%P|%t) IIOP_Profile::decode - v%d.%d\n"),
                    major,
                    minor));
      }
    return -1;
  }

  char *rendezvous = 0;

  // Get rendezvous_point
  if (cdr.read_string (rendezvous) == 0)
    {
      ACE_DEBUG ((LM_DEBUG, "error decoding UIOP rendezvous_point"));
      return -1;
    }

  // delete the rendezvous point. We don't do any processing.
  delete [] rendezvous;

  // ... and object key.
  if ((cdr >> object_key) == 0)
    return -1;

  return 1;
}

int
TAO_UIOP_Acceptor::parse_options (const char *str)
{
  if (str == 0)
    return 0;  // No options to parse.  Not a problem.

  // Use an option format similar to the one used for CGI scripts in
  // HTTP URLs.
  // e.g.:  option1=foo&option2=bar

  ACE_CString options (str);

  size_t len = options.length ();

  const char option_delimiter = '&';

  // Count the number of options.

  CORBA::ULong option_count = 1;
  // Number of endpoints in the string (initialized to 1).

  // Only check for endpoints after the protocol specification and
  // before the object key.
  for (size_t i = 0; i < len; ++i)
    if (options[i] == option_delimiter)
      option_count++;

  // The idea behind the following loop is to split the options into
  // (option, name) pairs.
  // For example,
  //    `option1=foo&option2=bar'
  // will be parsed into:
  //    `option1=foo'
  //    `option2=bar'

  int begin = 0;
  int end = -1;

  for (CORBA::ULong j = 0; j < option_count; ++j)
    {
      begin += end + 1;

      if (j < option_count - 1)
        end = options.find (option_delimiter, begin);
      else
        end = len - begin;  // Handle last endpoint differently

      if (end == begin)
        ACE_ERROR_RETURN ((LM_ERROR,
                           "TAO (%P|%t) Zero length UIOP option.\n"),
                          -1);
      else if (end != ACE_CString::npos)
        {
          ACE_CString opt =
            options.substring (begin, end);

          int slot = opt.find ("=");

          if (slot == ACE_static_cast (int, len - 1)
              || slot == ACE_CString::npos)
            ACE_ERROR_RETURN ((LM_ERROR,
                               "TAO (%P|%t) UIOP option <%s> is "
                               "missing a value.\n",
                               opt.c_str ()),
                              -1);

          ACE_CString name = opt.substring (0, slot);
          ACE_CString value = opt.substring (slot + 1);

          if (name.length () == 0)
            ACE_ERROR_RETURN ((LM_ERROR,
                               "TAO (%P|%t) Zero length UIOP "
                               "option name.\n"),
                              -1);

          if (name == "priority")
            {
              ACE_ERROR_RETURN ((LM_ERROR,
                                 ACE_TEXT ("TAO (%P|%t) Invalid IIOP endpoint format: ")
                                 ACE_TEXT ("endpoint priorities no longer supported. \n"),
                                 value.c_str ()),
                                -1);
            }
          else
            ACE_ERROR_RETURN ((LM_ERROR,
                               "TAO (%P|%t) Invalid UIOP option: <%s>\n",
                               name.c_str ()),
                              -1);
        }
    }
  return 0;
}

int
TAO_UIOP_Acceptor::init_uiop_properties (void)
{
  // @@ Currently (in the code below), we obtain protocol properties from
  // ORB-level ServerProtocol, even though the policy may
  // have been overridden on POA level.  That's because currently all
  // endpoints (acceptors) are global.  Once endpoints become per POA,
  // the code below will have to be changed to look at the POA-level
  // ServerProtocol policy first.

  // ServerProtocolProperties policy controls protocols configuration.
  // Look for protocol properties in the effective
  // ServerProtocolPolicy.
  ACE_DECLARE_NEW_CORBA_ENV;

  // Initialize the settings to the ORB defaults.  If RT CORBA is enabled,
  // it may override these.
  int send_buffer_size = this->orb_core_->orb_params ()->sock_sndbuf_size ();
  int recv_buffer_size = this->orb_core_->orb_params ()->sock_rcvbuf_size ();
  int no_delay = 0;

  TAO_Protocols_Hooks *tph = this->orb_core_->get_protocols_hooks (ACE_TRY_ENV);
  ACE_CHECK_RETURN (-1);

  if (tph != 0)
    {
      const char protocol [] = "uiop";
      const char *protocol_type = protocol;

      int hook_result =
        tph->call_server_protocols_hook (send_buffer_size,
                                         recv_buffer_size,
                                         no_delay,
                                         protocol_type);

      if(hook_result == -1)
        return -1;
    }

  // Extract and locally store properties of interest.
  this->uiop_properties_.send_buffer_size =
    send_buffer_size;
  this->uiop_properties_.recv_buffer_size =
   recv_buffer_size;

  return 0;
}

#endif  /* TAO_HAS_UIOP == 1 */
