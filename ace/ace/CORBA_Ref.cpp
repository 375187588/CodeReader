// CORBA_Ref.cpp
// CORBA_Ref.cpp,v 4.5 2000/05/03 06:32:03 schmidt Exp

#if !defined (ACE_CORBA_REF_C)
#define ACE_CORBA_REF_C

#include "ace/CORBA_Ref.h"
#include "ace/Log_Msg.h"

ACE_RCSID(ace, CORBA_Ref, "CORBA_Ref.cpp,v 4.5 2000/05/03 06:32:03 schmidt Exp")

template<class CORBA_REF>
ACE_CORBA_Ref<CORBA_REF>::ACE_CORBA_Ref (void)
  : ref_ (0)
{
  ACE_TRACE ("ACE_CORBA_Ref<CORBA_REF>::ACE_CORBA_Ref");
}

template<class CORBA_REF>
ACE_CORBA_Ref<CORBA_REF>::ACE_CORBA_Ref (CORBA_REF *ref)
{
  ACE_TRACE ("ACE_CORBA_Ref<CORBA_REF>::ACE_CORBA_Ref");
  if (ref != 0)
    ref_ = ref->_duplicate ();
  else
    ref_ = 0;
}

template<class CORBA_REF> CORBA_REF *
ACE_CORBA_Ref<CORBA_REF>::operator= (CORBA_REF *ref)
{
  ACE_TRACE ("ACE_CORBA_Ref<CORBA_REF>::operator=");
  if (ref_ != 0)
    ref_->_release ();
  if (ref == 0)
    {
      ref_ = 0;
      return 0;
    }
  else
    return ref_ = ref->_duplicate ();
}

template<class CORBA_REF>
ACE_CORBA_Ref<CORBA_REF>::operator CORBA_REF * (void) const
{
  ACE_TRACE ("ACE_CORBA_Ref<CORBA_REF>::operator CORBA_REF *");
  ACE_ASSERT (ref_ != 0);
  return ref_; 
}

template<class CORBA_REF> CORBA_REF *
ACE_CORBA_Ref<CORBA_REF>::operator-> (void) const
{
  ACE_TRACE ("ACE_CORBA_Ref<CORBA_REF>::operator->");
  ACE_ASSERT (ref_ != 0);
  return ref_;
}

template<class CORBA_REF> int
ACE_CORBA_Ref<CORBA_REF>::operator== (CORBA_REF *rhs) const
{
  ACE_TRACE ("ACE_CORBA_Ref<CORBA_REF>::operator==");
  // pointer comparison.
  return ref_ == rhs;
}

template<class CORBA_REF> int
ACE_CORBA_Ref<CORBA_REF>::operator!= (CORBA_REF *rhs) const
{
  ACE_TRACE ("ACE_CORBA_Ref<CORBA_REF>::operator!=");
  // pointer comparison.
  return ref_ != rhs;
}

template<class CORBA_REF>
ACE_CORBA_Ref<CORBA_REF>::~ACE_CORBA_Ref ()
{
  ACE_TRACE ("ACE_CORBA_Ref<CORBA_REF>::~ACE_CORBA_Ref");
  if (ref_ != 0)
    ref_->_release ();
}

#endif /* ACE_CORBA_REF_C */
