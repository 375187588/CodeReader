//
// Oneway_Buffering.h,v 1.1 2001/04/12 19:25:54 coryan Exp
//

#ifndef ONEWAY_BUFFERING_H
#define ONEWAY_BUFFERING_H
#include "ace/pre.h"

#include "TestS.h"

#if defined (_MSC_VER)
# if (_MSC_VER >= 1200)
#  pragma warning(push)
# endif /* _MSC_VER >= 1200 */
# pragma warning (disable:4250)
#endif /* _MSC_VER */

/// Implement the Test::Oneway_Buffering interface
class Oneway_Buffering
  : public virtual POA_Test::Oneway_Buffering
  , public virtual PortableServer::RefCountServantBase
{
public:
  /// Constructor
  Oneway_Buffering (CORBA::ORB_ptr orb,
                    Test::Oneway_Buffering_Admin_ptr admin);

  // = The skeleton methods
  virtual void receive_data (const Test::Payload &the_payload,
                             CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual void flush (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual void sync (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual void shutdown (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));

private:
  /// Use an ORB reference to shutdown the application.
  CORBA::ORB_var orb_;

  /// Report request progress to this interface
  Test::Oneway_Buffering_Admin_var admin_;
};

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma warning(pop)
#endif /* _MSC_VER */

#include "ace/post.h"
#endif /* ONEWAY_BUFFERING_H */
