// Timeprobe.i,v 4.2 1998/06/06 23:37:49 schmidt Exp

ACE_INLINE int 
ACE_Event_Descriptions::operator== (const ACE_Event_Descriptions &rhs) const
{
  return this->minimum_id_ == rhs.minimum_id_ &&
    this->descriptions_ == rhs.descriptions_;
}
