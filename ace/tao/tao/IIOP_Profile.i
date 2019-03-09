// -*- C++ -*-
// IIOP_Profile.i,v 1.22 2000/09/14 01:06:53 marina Exp

ACE_INLINE const TAO_ObjectKey &
TAO_IIOP_Profile::object_key (void) const
{
  return this->object_key_;
}

ACE_INLINE TAO_ObjectKey *
TAO_IIOP_Profile::_key (void) const
{
  TAO_ObjectKey *key = 0;

  ACE_NEW_RETURN (key,
                  TAO_ObjectKey (this->object_key_),
                  0);

  return key;
}




