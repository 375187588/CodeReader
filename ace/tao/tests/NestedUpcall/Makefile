#----------------------------------------------------------------------------
#
#	Makefile,v 1.13 1999/09/24 17:01:03 nanbor Exp
#
#	Makefile for the NestedUpcall tests
#
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
#	Local macros
#----------------------------------------------------------------------------

DIRS  = Simple \
        Triangle_Test \
	MT_Client_Test

ifndef TAO_ROOT
  TAO_ROOT = $(ACE_ROOT)/TAO
endif

#----------------------------------------------------------------------------
#	Include macros and targets
#----------------------------------------------------------------------------

include	$(ACE_ROOT)/include/makeinclude/wrapper_macros.GNU
include	$(ACE_ROOT)/include/makeinclude/macros.GNU
include $(TAO_ROOT)/rules.tao.GNU
include	$(ACE_ROOT)/include/makeinclude/rules.common.GNU
include	$(ACE_ROOT)/include/makeinclude/rules.nested.GNU
include	$(ACE_ROOT)/include/makeinclude/rules.nolocal.GNU
