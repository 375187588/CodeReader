##---------------------------------------------------------------------------
##       Makefile.am,v 1.2 1999/04/07 20:53:27 othman Exp
##
##       Makefile for TAO's Naming Service
##
##---------------------------------------------------------------------------

##
##  Process this file with automake to create Makefile.in
##

## The number in AUTOMAKE_OPTIONS is the minimum required version automake
## needed to process this file.
AUTOMAKE_OPTIONS = 1.4

INCLUDES = -I$(top_builddir) -I$(top_srcdir)

bin_PROGRAMS = Naming_Service

Naming_Service_LDADD = \
	$(top_builddir)/ace/libACE.la $(top_builddir)/TAO/tao/libTAO.la

Naming_Service_SOURCES = \
        Naming_Service.cpp

noinst_HEADERS = \
        Naming_Service.h

EXTRA_DIST = README

## Clean up some additional files/directories possibly created during
## the configure script tests.
clean-local:
	-rm -f *.bak *.rpo *.sym lib*.*_pure_* Makefile.old core
	-rm -rf ptrepository Templates.DB gcctemp.c gcctemp so_locations

