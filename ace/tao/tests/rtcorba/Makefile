#----------------------------------------------------------------------------
#
#       Makefile,v 1.11 2001/09/18 00:06:00 irfan Exp
#
#       Makefile for RTCORBA tests
#
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
#       Local macros
#----------------------------------------------------------------------------

DIRS  = \
	Banded_Connections \
	Client_Propagated \
	Client_Protocol \
	Collocation \
	Destroy_Thread_Pool \
	Explicit_Binding \
	Linear_Priority \
	MT_Client_Protocol_Priority \
	ORB_init \
	Persistent_IOR \
	Policy_Combinations \
	Private_Connection \
        RTMutex \
	Server_Declared \
        Server_Protocol \
	Thread_Pool

ifndef TAO_ROOT
  TAO_ROOT = $(ACE_ROOT)/TAO
endif

#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------

include $(ACE_ROOT)/include/makeinclude/wrapper_macros.GNU
include $(TAO_ROOT)/rules.tao.GNU
include $(ACE_ROOT)/include/makeinclude/macros.GNU
include $(ACE_ROOT)/include/makeinclude/rules.common.GNU
include $(ACE_ROOT)/include/makeinclude/rules.nested.GNU
include $(ACE_ROOT)/include/makeinclude/rules.nolocal.GNU
