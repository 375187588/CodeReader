// helper.cpp,v 1.12 2001/02/02 02:32:10 fhunleth Exp

// ============================================================================
//
// = LIBRARY
//    TAO/tests/Param_Test
//
// = FILENAME
//    helper.cpp
//
// = DESCRIPTION
//    Defines a helper class that can generate values for the parameters used
//    for the Param_Test example
//
// = AUTHORS
//    Aniruddha Gokhale
//
// ============================================================================

#include "helper.h"

const CORBA::ULong TEST_BUFSIZE = 128;

ACE_RCSID(Param_Test, helper, "helper.cpp,v 1.12 2001/02/02 02:32:10 fhunleth Exp")

Generator::Generator (void)
{
}

Generator::~Generator (void)
{
}

CORBA::Short
Generator::gen_short (void)
{
  return (CORBA::Short) (ACE_OS::rand () % TEST_BUFSIZE);
}

CORBA::Long
Generator::gen_long (void)
{
  return ::ACE_OS::rand () % TEST_BUFSIZE;
}

char *
Generator::gen_string (void)
{
  return gen_string (TEST_BUFSIZE);
}

char *
Generator::gen_string (int max_length)
{
  CORBA::ULong len = (CORBA::ULong) (::ACE_OS::rand () % max_length);
  char *buf = CORBA::string_alloc (len);
  CORBA::ULong i = 0;

  while (i < len)
    {
      int c = ACE_OS::rand () % 128;
      if (isprint (c) && !isspace (c))
        {
          buf [i] = c;
          i++;
        }
    }

  buf[i] = 0;
  return buf;
}

CORBA::WChar *
Generator::gen_wstring (void)
{
  return gen_wstring (TEST_BUFSIZE);
}

CORBA::WChar *
Generator::gen_wstring (int max_length)
{
  CORBA::ULong len = (CORBA::ULong) (::ACE_OS::rand () % max_length);
  CORBA::WChar *buf = CORBA::wstring_alloc (len);
  CORBA::ULong i = 0;

  while (i < len)
    {
      CORBA::WChar wc = ACE_OS::rand () % ACE_WCHAR_MAX;
      if (wc)
        {
          buf[i] = wc;
          i++;
        }
    }

  buf[i] = 0;
  return buf;
}

const Param_Test::Fixed_Struct
Generator::gen_fixed_struct (void)
{
  this->fixed_struct_.l = ACE_OS::rand ();
  this->fixed_struct_.c = ACE_OS::rand () % 128;
  this->fixed_struct_.s = (CORBA::Short) ACE_OS::rand ();
  this->fixed_struct_.o = ACE_OS::rand () % 128;
  this->fixed_struct_.f = (CORBA::Float) (ACE_OS::rand () * 1.0);
  this->fixed_struct_.b = (CORBA::Boolean) ACE_OS::rand () % 2;
  this->fixed_struct_.d = (ACE_OS::rand () * 1.0);
  return this->fixed_struct_;
}

const Param_Test::Step
Generator::gen_step (void)
{
  this->step_.name.id = this->gen_string ();
  this->step_.name.kind = this->gen_string ();
  this->step_.process = (CORBA::Boolean) ACE_OS::rand () % 2;
  return this->step_;
}

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)
template class ACE_Singleton<Generator, TAO_SYNCH_RECURSIVE_MUTEX>;
#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)
#pragma instantiate ACE_Singleton<Generator, TAO_SYNCH_RECURSIVE_MUTEX>
#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */
