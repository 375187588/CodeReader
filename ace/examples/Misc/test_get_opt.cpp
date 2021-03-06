// test_get_opt.cpp,v 4.4 2000/05/26 18:08:44 othman Exp

// Test the ACE_Get_Opt class.

#include "ace/Get_Opt.h"
#include "ace/Log_Msg.h"

ACE_RCSID(Misc, test_get_opt, "test_get_opt.cpp,v 4.4 2000/05/26 18:08:44 othman Exp")

int
main (int argc, char *argv[])
{
  ACE_Get_Opt get_opt (argc, argv, "ab:cd:ef:gh:");
  int c;

  while ((c = get_opt ()) != EOF)
    switch (c)
      {
      case 'a':
	ACE_DEBUG ((LM_DEBUG, "got a\n"));
	break;
      case 'b':
	ACE_DEBUG ((LM_DEBUG, "got b with arg %s\n", get_opt.optarg));
	break;
      case 'c':
	ACE_DEBUG ((LM_DEBUG, "got c\n"));
	break;
      case 'd':
	ACE_DEBUG ((LM_DEBUG, "got d with arg %s\n", get_opt.optarg));
	break;
      case 'e':
	ACE_DEBUG ((LM_DEBUG, "got e\n"));
	break;
      case 'f':
	ACE_DEBUG ((LM_DEBUG, "got f with arg %s\n", get_opt.optarg));
	break;
      case 'g':
	ACE_DEBUG ((LM_DEBUG, "got g\n"));
	break;
      case 'h':
	ACE_DEBUG ((LM_DEBUG, "got h with arg %s\n", get_opt.optarg));
	break;
      default:
	ACE_DEBUG ((LM_DEBUG, "got %c, which is unrecognized!\n", c));
	break;
      }

  for (int i = get_opt.optind; i < argc; i++)
    ACE_DEBUG ((LM_DEBUG, "optind = %d, argv[optind] = %s\n", 
		i, argv[i]));

  return 0;
}
