// client.cpp,v 1.2 2001/05/11 00:02:17 coryan Exp

#include "TestC.h"

#include "tao/DynamicInterface/Request.h"

#include "tao/Strategies/advanced_resource.h"

#include "ace/Get_Opt.h"
#include "ace/Sched_Params.h"
#include "ace/High_Res_Timer.h"
#include "ace/Sched_Params.h"
#include "ace/Stats.h"
#include "ace/Sample_History.h"

ACE_RCSID(Deferred_Latency, client, "client.cpp,v 1.2 2001/05/11 00:02:17 coryan Exp")

const char *ior = "file://test.ior";
int niterations = 1000;
int burst = 10;
int do_shutdown = 1;
int do_dump_history = 0;

int
parse_args (int argc, char *argv[])
{
  ACE_Get_Opt get_opts (argc, argv, "hxk:i:b:");
  int c;

  while ((c = get_opts ()) != -1)
    switch (c)
      {
      case 'h':
        do_dump_history = 1;
        break;

      case 'x':
        do_shutdown = 0;
        break;

      case 'k':
        ior = get_opts.optarg;
        break;

      case 'i':
        niterations = ACE_OS::atoi (get_opts.optarg);
        break;

      case 'b':
        burst = ACE_OS::atoi (get_opts.optarg);
        break;

      case '?':
      default:
        ACE_ERROR_RETURN ((LM_ERROR,
                           "usage:  %s "
                           "-k <ior> "
                           "-i <niterations> "
                           "-b <burst> "
                           "-x (disable shutdown) "
                           "-h (dump history) "
                           "\n",
                           argv [0]),
                          -1);
      }
  // Indicates sucessful parsing of the command line
  return 0;
}

int
main (int argc, char *argv[])
{
  int priority =
    (ACE_Sched_Params::priority_min (ACE_SCHED_FIFO)
     + ACE_Sched_Params::priority_max (ACE_SCHED_FIFO)) / 2;
  // Enable FIFO scheduling, e.g., RT scheduling class on Solaris.

  if (ACE_OS::sched_params (ACE_Sched_Params (ACE_SCHED_FIFO,
                                              priority,
                                              ACE_SCOPE_PROCESS)) != 0)
    {
      if (ACE_OS::last_error () == EPERM)
        {
          ACE_DEBUG ((LM_DEBUG,
                      "client (%P|%t): user is not superuser, "
                      "test runs in time-shared class\n"));
        }
      else
        ACE_ERROR ((LM_ERROR,
                    "client (%P|%t): sched_params failed\n"));
    }

  ACE_TRY_NEW_ENV
    {
      CORBA::ORB_var orb =
        CORBA::ORB_init (argc, argv, "", ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (parse_args (argc, argv) != 0)
        return 1;

      CORBA::Object_var object =
        orb->string_to_object (ior, ACE_TRY_ENV);
      ACE_TRY_CHECK;

      Test::Roundtrip_var roundtrip =
        Test::Roundtrip::_narrow (object.in (), ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (CORBA::is_nil (roundtrip.in ()))
        {
          ACE_ERROR_RETURN ((LM_ERROR,
                             "Nil Test::Roundtrip reference <%s>\n",
                             ior),
                            1);
        }

      for (int j = 0; j < 100; ++j)
        {
          ACE_hrtime_t start = 0;
          (void) roundtrip->test_method (start, ACE_TRY_ENV);
          ACE_TRY_CHECK;
        }

      ACE_Sample_History history (niterations);

      ACE_hrtime_t test_start = ACE_OS::gethrtime ();

      CORBA::Request_var *request;
      ACE_NEW_RETURN (request, CORBA::Request_var[burst], 1);

      for (int i = 0; i < niterations; ++i)
        {
          int j;

          for (j = 0; j != burst; ++j)
            {
              CORBA::ULongLong start = ACE_OS::gethrtime ();

              request[j] =
                roundtrip->_request ("test_method",
                                     ACE_TRY_ENV);
              ACE_TRY_CHECK;

              request[j]->add_in_arg () <<= start;
              request[j]->set_return_type (CORBA::_tc_ulonglong);

              request[j]->send_deferred (ACE_TRY_ENV);
              ACE_TRY_CHECK;
            }

          for (j = 0; j != burst; ++j)
            {
              request[j]->get_response (ACE_TRY_ENV);
              ACE_TRY_CHECK;

              CORBA::ULongLong retval;
              if ((request[j]->return_value () >>= retval) == 1)
                {
                  ACE_hrtime_t now = ACE_OS::gethrtime ();
                  history.sample (now - retval);
                }
            }
        }
      delete[] request;

      ACE_hrtime_t test_end = ACE_OS::gethrtime ();

      ACE_DEBUG ((LM_DEBUG, "test finished\n"));

      ACE_DEBUG ((LM_DEBUG, "High resolution timer calibration...."));
      ACE_UINT32 gsf = ACE_High_Res_Timer::global_scale_factor ();
      ACE_DEBUG ((LM_DEBUG, "done\n"));

      if (do_dump_history)
        {
          history.dump_samples ("HISTORY", gsf);
        }

      ACE_Basic_Stats stats;
      history.collect_basic_stats (stats);
      stats.dump_results ("Total", gsf);

      ACE_Throughput_Stats::dump_throughput ("Total", gsf,
                                             test_end - test_start,
                                             stats.samples_count ());

      if (do_shutdown)
        {
          roundtrip->shutdown (ACE_TRY_ENV);
          ACE_TRY_CHECK;
        }
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                           "Caught exception:");
      return 1;
    }
  ACE_ENDTRY;

  return 0;
}
