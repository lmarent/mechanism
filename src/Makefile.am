# -----------------------------------*- mode: Makefile; -*--
# Makefile.am - Makefile.am for Mechanism Libraries
# ----------------------------------------------------------
# $Id$
# $HeadURL$
# ==========================================================
#                      
# (C)opyright, all rights reserved by
# - System and Computing Engineering, Universidad de los Andes
# ==========================================================
#
#

EXTRA_DIST = MiscProcModule.h MiscProcModule.cpp ProcError.cpp

pkgincludedir = $(includedir)/$(PACKAGE)

API_INC		= $(top_srcdir)/include
INC_DIR 	= $(top_srcdir)/include

lib_LTLIBRARIES = libtwoauction.la

if ENABLE_DEBUG
AM_CXXFLAGS = -I$(top_srcdir)/include $(LIBIPAP_CFLAGS) $(LIBAUCTIONFDTION_CFLAGS) \
   			  $(LIBANSLP_MSG_CFLAGS) -g  -fno-inline -DDEBUG -D_GLIBCXX_DEBUG -ggdb
else
AM_CXXFLAGS = -I$(top_srcdir)/include $(LIBIPAP_CFLAGS) $(LIBAUCTIONFDTION_CFLAGS) \
			  $(LIBANSLP_MSG_CFLAGS) -O2
endif

libtwoauction_la_CPPFLAGS = $(LIBIPAP_CFLAGS) $(LIBAUCTIONFDTION_CFLAGS) \
							$(LIBANSLP_MSG_CFLAGS)

libtwoauction_la_SOURCES = TwoAuctionMechanism.cpp \
						   twoauction.cpp

libtwoauction_la_LIBADD = MiscProcModule.lo ProcError.lo $(LIBIPAP_LIBS)

LDADD = $(LIBIPAP_LIBS) $(LIBAUCTIONFDTION_LIBS)


# end of Makefile.am

