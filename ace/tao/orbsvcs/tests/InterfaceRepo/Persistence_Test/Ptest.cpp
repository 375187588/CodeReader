// -*- C++ -*-
// Ptest.cpp,v 1.8 2001/05/04 17:18:03 parsons Exp

#include "Ptest.h"
#include "ace/Get_Opt.h"

ACE_RCSID(Persistence_Test, Ptest, "Ptest.cpp,v 1.8 2001/05/04 17:18:03 parsons Exp")

Ptest::Ptest (void)
  : debug_ (0),
    query_ (0)
{
}

Ptest::~Ptest (void)
{
}

int
Ptest::init (int argc,
                    char *argv[])
{
  ACE_TRY_NEW_ENV
    {
      this->orb_ = CORBA::ORB_init (argc,
                                    argv,
                                    0,
                                    ACE_TRY_ENV);
      ACE_TRY_CHECK;

      int retval = this->parse_args (argc,
                                     argv);

      if (retval != 0)
        return retval;

      CORBA::Object_var object =
        this->orb_->resolve_initial_references ("InterfaceRepository",
                                                ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (CORBA::is_nil (object.in ()))
        {
          ACE_ERROR_RETURN ((
              LM_ERROR,
              "Null objref from resolve_initial_references\n"
            ),
            -1
          );
        }

      this->repo_ =
        CORBA::Repository::_narrow (object.in (),
                                    ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (CORBA::is_nil (this->repo_.in ()))
        {
          ACE_ERROR_RETURN ((LM_ERROR,
                             "CORBA::Repository::_narrow failed\n"),
                            -1);
        }
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                           "Ptest::init");
      return -1;
    }
  ACE_ENDTRY;

  return 0;
}

int
Ptest::run (void)
{
  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {
      if (this->query_ == 1)
        {
          this->query (ACE_TRY_ENV);
          ACE_TRY_CHECK;
        }
      else
        {
          this->populate (ACE_TRY_ENV);
          ACE_TRY_CHECK;
        }
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                           "Ptest::run");
      return -1;
    }
  ACE_ENDTRY;

  return 0;
}

int
Ptest::parse_args (int argc,
                   char *argv[])
{
  ACE_Get_Opt opts (argc, argv, "dq");
  int c;

  while ((c = opts ()) != -1)
    switch (c)
      {
      case 'd':   // debug flag
        this->debug_ = 1;
        break;
      case 'q':   // query toggle
        this->query_ = 1;
        break;
      case '?':
      default:
        ACE_ERROR_RETURN ((LM_ERROR,
                           "usage: %s"
                           " [-d]"
                           " [-q]"
                           "\n",
                           argv [0]),
                          -1);
      }

  return 0;
}

void
Ptest::populate (CORBA::Environment &ACE_TRY_ENV)
{
  ACE_DEBUG ((
      LM_DEBUG,
      ACE_TEXT ("\n============== POPULATE ==============\n\n")
    ));

  CORBA::StructMemberSeq members (2);
  members.length (2);
  members[0].name = CORBA::string_dup ("long_mem");
  members[0].type_def = this->repo_->get_primitive (CORBA::pk_long,
                                                    ACE_TRY_ENV);
  ACE_CHECK;
  members[0].type = members[0].type_def->type (ACE_TRY_ENV);
  ACE_CHECK;

  members[1].name = CORBA::string_dup ("array_mem");
  members[1].type_def = this->repo_->create_array (5,
                                                   members[0].type_def.in (),
                                                   ACE_TRY_ENV);
  ACE_CHECK;
  members[1].type = members[1].type_def->type (ACE_TRY_ENV);
  ACE_CHECK;


  CORBA::StructDef_var svar = this->repo_->create_struct ("IDL:my_struct:1.0",
                                                          "my_struct",
                                                          "1.0",
                                                          members,
                                                          ACE_TRY_ENV);
  ACE_CHECK;

  CORBA::EnumMemberSeq def_members (2);
  def_members.length (2);

  def_members[0] = CORBA::string_dup ("ZERO");
  def_members[1] = CORBA::string_dup ("ONE");

  CORBA::EnumDef_var e_def_var = svar->create_enum ("IDL:my_def_enum:1.0",
                                                    "my_enum",
                                                    "1.0",
                                                    def_members,
                                                    ACE_TRY_ENV);
  ACE_CHECK;
}

void
Ptest::query (CORBA::Environment &ACE_TRY_ENV)
{
  ACE_DEBUG ((
      LM_DEBUG,
      ACE_TEXT ("\n============== QUERY ==============\n\n")
    ));

  const char *members[] =
  {
    "long_mem",
    "array_mem",
    "my_enum"
  };

  CORBA::ContainedSeq_var contents = this->repo_->contents (CORBA::dk_all,
                                                            0,
                                                            ACE_TRY_ENV);
  ACE_CHECK;

  CORBA::ULong length = contents->length ();

  if (this->debug_)
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("Repository::contents::length: %d\n"),
                length));

  ACE_ASSERT (length == 1);

  CORBA::ULong i = 0;

  CORBA::StructDef_var svar = CORBA::StructDef::_narrow (contents[i],
                                                         ACE_TRY_ENV);
  ACE_CHECK;

  ACE_ASSERT (!CORBA::is_nil (svar.in ()));

  CORBA::StructMemberSeq_var out_members = svar->members (ACE_TRY_ENV);
  ACE_CHECK;

  length = out_members->length ();

  if (this->debug_)
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("\nStructDef::members::length: %d\n"),
                length));

  ACE_ASSERT (length == 3);

  for (i = 0; i < length; i++)
    {
      if (this->debug_)
        ACE_DEBUG ((LM_DEBUG,
                    ACE_TEXT ("StructDef::members[%d]::name: %s\n"),
                    i,
                    out_members[i].name.in ()));

      if (i == length - 1)
        {
          if (ACE_OS::strcmp (out_members[i].name, "my_enum"))
            {
              ACE_ERROR ((LM_ERROR,
                          ACE_TEXT ("persistence_test::query::members -")
                          ACE_TEXT ("incorrect local name in item %d"),
                          i));

              return;
            }
        }
      else
        {
          if (ACE_OS::strcmp (out_members[i].name, members[i]))
            {
              ACE_ERROR ((LM_ERROR,
                          ACE_TEXT ("persistence_test::query::members -")
                          ACE_TEXT ("incorrect local name in item %d"),
                          i));

              return;
            }
        }
    }

#if defined (ACE_NDEBUG)
  // ACE_ASSERT macro expands to nothing, so...
  ACE_UNUSED_ARG (members);
#endif /* ACE_NDEBUG */

  svar->destroy (ACE_TRY_ENV);
  ACE_CHECK;
}
