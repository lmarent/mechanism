check_PROGRAMS = test_runner

API_INC			= $(top_srcdir)/include
INC_DIR 		= $(top_srcdir)/include/


test_runner_SOURCES =  @top_srcdir@/src/TwoAuctionMechanism.cpp \
					   @top_srcdir@/test/TwoAuctionMechanism_test.cpp \
					   @top_srcdir@/test/twoauction_test.cpp \
					   @top_srcdir@/test/twoauctionuser_test.cpp \
					   @top_srcdir@/test/subsidyauction_test.cpp \
					   @top_srcdir@/test/subsidyauctionuser_test.cpp \
					   @top_srcdir@/test/test_runner.cpp

test_runner_CPPFLAGS  = -I$(API_INC) $(CPPUNIT_CFLAGS) \
						 $(LIBGIST_CFLAGS) $(LIBPROT_CFLAGS) $(LIBFASTQUEUE_CFLAGS) \
						 $(LIBIPAP_CFLAGS) $(LIBANSLP_CFLAGS) $(LIBANSLP_MSG_CFLAGS) \
						 $(PQXX_CFLAGS) $(LIBAUCTIONFDTION_CFLAGS)

test_runner_LDADD  = $(CPPUNIT_LIBS) -ldl -lcppunit \
					 $(LIBAUCTIONFDTION_LIBS) \
					 $(LIBPROT_LIBS) $(LIBFASTQUEUE_LIBS) $(LIBGIST_LIBS) \
					 $(LIBIPAP_LIBS) $(LIBANSLP_MSG_LIBS) $(LIBANSLP_LIBS) $(PQXX_LIBS)

TESTS = $(check_PROGRAMS)

if ENABLE_DEBUG
  AM_CXXFLAGS = -I$(top_srcdir)/include \
				-g  -fno-inline -DDEBUG 
else
  AM_CXXFLAGS = -I$(top_srcdir)/include \
				-O2 
endif

AM_CXXFLAGS += -Wall -ggdb -pedantic -Wno-long-long


#  TEST_CXX_FLAGS=`cppunit-config --cflags`
