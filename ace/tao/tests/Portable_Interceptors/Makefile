#----------------------------------------------------------------------------
#
#       Makefile,v 1.5 2001/09/24 08:31:36 othman Exp
#
#       Makefile for the PortableInterceptor tests
#
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
#       Local macros
#----------------------------------------------------------------------------

DIRS  = \
  Dynamic \
  Benchmark \
  Service_Context_Manipulation \
  IORInterceptor \
  ForwardRequest \
  Request_Interceptor_Flow \
  PICurrent

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
