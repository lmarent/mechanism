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

lib_LTLIBRARIES = libtwoauction.la libtwoauctionuser.la libtwoauctiongen.la libtwoauctiongenuser.la libsubsidyauction.la libsubsidyauctionuser.la

if ENABLE_DEBUG
AM_CXXFLAGS = -I$(top_srcdir)/include $(LIBIPAP_CFLAGS) $(LIBAUCTIONFDTION_CFLAGS) \
   			  $(LIBANSLP_MSG_CFLAGS) $(PQXX_CFLAGS) -g  -fno-inline -DDEBUG -ggdb
else
AM_CXXFLAGS = -I$(top_srcdir)/include $(LIBIPAP_CFLAGS) $(LIBAUCTIONFDTION_CFLAGS) \
			  $(LIBANSLP_MSG_CFLAGS) -O2
endif

#-----------------------------------------------------------------------
#--------------------------- Two Auction Few Users
#-----------------------------------------------------------------------

libtwoauction_la_CPPFLAGS = $(LIBIPAP_CFLAGS) $(LIBAUCTIONFDTION_CFLAGS) \
							$(LIBANSLP_MSG_CFLAGS) $(PQXX_CFLAGS)

libtwoauction_la_SOURCES = TwoAuctionMechanism.cpp \
						   twoauction.cpp

libtwoauction_la_LIBADD = MiscProcModule.lo ProcError.lo $(LIBIPAP_LIBS)


libtwoauctionuser_la_CPPFLAGS = $(LIBIPAP_CFLAGS) $(LIBAUCTIONFDTION_CFLAGS) \
								$(LIBANSLP_MSG_CFLAGS) $(PQXX_CFLAGS)

libtwoauctionuser_la_SOURCES = twoauctionuser.cpp

libtwoauctionuser_la_LIBADD = MiscProcModule.lo ProcError.lo $(LIBIPAP_LIBS)

#-----------------------------------------------------------------------
#--------------------------- Two Auction Generalized 
#-----------------------------------------------------------------------

libtwoauctiongen_la_CPPFLAGS = $(LIBIPAP_CFLAGS) $(LIBAUCTIONFDTION_CFLAGS) \
							$(LIBANSLP_MSG_CFLAGS) $(PQXX_CFLAGS)

libtwoauctiongen_la_SOURCES = TwoAuctionMechanismGeneralized.cpp \
						   TwoAuctionGeneralized.cpp

libtwoauctiongen_la_LIBADD = MiscProcModule.lo ProcError.lo $(LIBIPAP_LIBS)


libtwoauctiongenuser_la_CPPFLAGS = $(LIBIPAP_CFLAGS) $(LIBAUCTIONFDTION_CFLAGS) \
								$(LIBANSLP_MSG_CFLAGS) $(PQXX_CFLAGS)

libtwoauctiongenuser_la_SOURCES = TwoAuctionGeneralizedUser.cpp

libtwoauctiongenuser_la_LIBADD = MiscProcModule.lo ProcError.lo $(LIBIPAP_LIBS)

#-----------------------------------------------------------------------
#--------------------------- Subsidy Auction 
#-----------------------------------------------------------------------

libsubsidyauction_la_CPPFLAGS = $(LIBIPAP_CFLAGS) $(LIBAUCTIONFDTION_CFLAGS) \
								$(LIBANSLP_MSG_CFLAGS) $(PQXX_CFLAGS)

libsubsidyauction_la_SOURCES = subsidyauction.cpp

libsubsidyauction_la_LIBADD = MiscProcModule.lo ProcError.lo $(LIBIPAP_LIBS)


libsubsidyauctionuser_la_CPPFLAGS = $(LIBIPAP_CFLAGS) $(LIBAUCTIONFDTION_CFLAGS) \
									$(LIBANSLP_MSG_CFLAGS) $(PQXX_CFLAGS)

libsubsidyauctionuser_la_SOURCES = subsidyauctionuser.cpp

libsubsidyauctionuser_la_LIBADD = MiscProcModule.lo ProcError.lo $(LIBIPAP_LIBS)


LDADD = $(LIBIPAP_LIBS) $(PQXX_LIBS) $(LIBAUCTIONFDTION_LIBS)


# end of Makefile.am

