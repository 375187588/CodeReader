// Fill_ACE_QoS.cpp
// Fill_ACE_QoS.cpp,v 1.4 2001/09/11 23:08:42 yamuna Exp

#include "Fill_ACE_QoS.h"

ACE_RCSID(QOS, Fill_ACE_QoS,"Fill_ACE_QoS.cpp,v 1.4 2001/09/11 23:08:42 yamuna Exp")

const iovec Fill_ACE_QoS::iov_ = {0,0};

Fill_ACE_QoS::Fill_ACE_QoS (void)
{
  ACE_NEW (this->default_traffic_,
           ACE_Flow_Spec  (ACE_QOS_NOT_SPECIFIED,
                           ACE_QOS_NOT_SPECIFIED,
                           ACE_QOS_NOT_SPECIFIED,
                           ACE_QOS_NOT_SPECIFIED,
                           ACE_QOS_NOT_SPECIFIED,
                           ACE_SERVICETYPE_NOTRAFFIC,
                           ACE_QOS_NOT_SPECIFIED,
                           ACE_QOS_NOT_SPECIFIED,
                           25,
                           1));
}

// destructor.
Fill_ACE_QoS::~Fill_ACE_QoS (void)
{}

int
Fill_ACE_QoS::fill_simplex_receiver_qos (ACE_QoS &ace_qos,
                                         ACE_Flow_Spec *ace_flow_spec)
{
  ace_qos.receiving_flowspec (ace_flow_spec);
  ace_qos.sending_flowspec ((this->default_traffic_));
  ace_qos.provider_specific (Fill_ACE_QoS::iov_);

  return 0;
}


int
Fill_ACE_QoS::fill_simplex_sender_qos (ACE_QoS &ace_qos,
                                       ACE_Flow_Spec *sender_flow_spec)
{
  ace_qos.receiving_flowspec ((this->default_traffic_));
  ace_qos.sending_flowspec (sender_flow_spec);
  ace_qos.provider_specific (Fill_ACE_QoS::iov_);

  return 0;
}

int
Fill_ACE_QoS::fill_duplex_qos (ACE_QoS &ace_qos,
                               ACE_Flow_Spec *recv_flow_spec,
                               ACE_Flow_Spec *sender_flow_spec)
{
  ace_qos.receiving_flowspec (recv_flow_spec);
  ace_qos.sending_flowspec (sender_flow_spec);
  ace_qos.provider_specific (Fill_ACE_QoS::iov_);

  return 0;
}

Fill_ACE_QoS::FLOW_SPEC_HASH_MAP&
Fill_ACE_QoS::map (void)
{
  return this->flow_spec_map_;
}

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)
template class ACE_Hash_Map_Manager<ACE_CString,ACE_Flow_Spec *,ACE_Null_Mutex>;
template class ACE_Hash_Map_Manager_Ex<ACE_CString, ACE_Flow_Spec *, ACE_Hash<ACE_CString>, ACE_Equal_To<ACE_CString>, ACE_Null_Mutex>;
template class ACE_Hash_Map_Entry<ACE_CString, ACE_Flow_Spec *>;
template class ACE_Hash_Map_Iterator_Base_Ex<ACE_CString, ACE_Flow_Spec *, ACE_Hash<ACE_CString>, ACE_Equal_To<ACE_CString>, ACE_Null_Mutex>;
template class ACE_Hash_Map_Iterator_Ex<ACE_CString, ACE_Flow_Spec *, ACE_Hash<ACE_CString>, ACE_Equal_To<ACE_CString>, ACE_Null_Mutex>;
template class ACE_Hash_Map_Reverse_Iterator<ACE_CString, ACE_Flow_Spec *, ACE_Null_Mutex>;
template class ACE_Hash_Map_Reverse_Iterator_Ex<ACE_CString, ACE_Flow_Spec *, ACE_Hash<ACE_CString>, ACE_Equal_To<ACE_CString>, ACE_Null_Mutex>;
#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)
#pragma instantiate ACE_Hash_Map_Manager<ACE_CString,ACE_Flow_Spec *,ACE_Null_Mutex>
#pragma instantiate ACE_Hash_Map_Manager_Ex<ACE_CString, ACE_Flow_Spec *, ACE_Hash<ACE_CString>, ACE_Equal_To<ACE_CString>, ACE_Null_Mutex>
#pragma instantiate ACE_Hash_Map_Entry<ACE_CString, ACE_Flow_Spec *>
#pragma instantiate ACE_Hash_Map_Iterator_Base_Ex<ACE_CString, ACE_Flow_Spec *, ACE_Hash<ACE_CString>, ACE_Equal_To<ACE_CString>, ACE_Null_Mutex>
#pragma instantiate ACE_Hash_Map_Iterator_Ex<ACE_CString, ACE_Flow_Spec *, ACE_Hash<ACE_CString>, ACE_Equal_To<ACE_CString>, ACE_Null_Mutex>
#pragma instantiate ACE_Hash_Map_Reverse_Iterator<ACE_CString, ACE_Flow_Spec *, ACE_Null_Mutex>
#pragma instantiate ACE_Hash_Map_Reverse_Iterator_Ex<ACE_CString, ACE_Flow_Spec *, ACE_Hash<ACE_CString>, ACE_Equal_To<ACE_CString>, ACE_Null_Mutex>
#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */
