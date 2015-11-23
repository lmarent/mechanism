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

pkgincludedir = $(includedir)/$(PACKAGE)

API_INC		= $(top_srcdir)/include
INC_DIR 	= $(top_srcdir)/include

lib_LTLIBRARIES = libtwoauction.la

pkginclude_HEADERS = $(INC_DIR)/TwoAuctionMechanism.h


if ENABLE_DEBUG
AM_CXXFLAGS = -I$(top_srcdir)/include \
   			  -g  -fno-inline -DDEBUG -D_GLIBCXX_DEBUG -ggdb
else
AM_CXXFLAGS = -I$(top_srcdir)/include \
			  -O2
endif

libtwoauction_la_CPPFLAGS = $(LIBIPAP_CFLAGS)

libtwoauction_la_SOURCES = TwoAuctionMechanism.cpp 

libtwoauction_la_LIBADD = $(LIBIPAP_LIBS)

LDADD = $(LIBIPAP_LIBS)



# end of Makefile.am

