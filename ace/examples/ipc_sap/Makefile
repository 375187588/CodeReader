#----------------------------------------------------------------------------
#	Makefile,v 4.3 2000/06/16 23:27:19 othman Exp
#
#	Makefile for the IPC_SAP test directory
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
#	Local macros
#----------------------------------------------------------------------------

DIRS  =	DEV_SAP \
        FIFO_SAP \
	FILE_SAP \
	SOCK_SAP \
	SPIPE_SAP \
	TLI_SAP \
	UPIPE_SAP

ifneq ($(ssl),)
  DIRS += SSL_SAP
endif # ssl

#----------------------------------------------------------------------------
#	macros and targets
#----------------------------------------------------------------------------

include	$(ACE_ROOT)/include/makeinclude/wrapper_macros.GNU
include	$(ACE_ROOT)/include/makeinclude/macros.GNU
include	$(ACE_ROOT)/include/makeinclude/rules.common.GNU
include	$(ACE_ROOT)/include/makeinclude/rules.nested.GNU
include	$(ACE_ROOT)/include/makeinclude/rules.nolocal.GNU
