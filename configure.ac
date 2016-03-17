#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([mechanism],[0.1],[la.marentes455@uniandes.edu.co])
AM_INIT_AUTOMAKE([subdir-objects])
LT_INIT
AC_CONFIG_SRCDIR([/src/TwoAuctionMechanism.cpp])


## ------------------------Begin instantiation part 
## Meaning:
## An instantiating macro is one which defines one or more tags, 
## usually referring to files that are to be translated by the generated 
## configure scripts, from a template containing Autoconf substitution 
## variables.

AC_CONFIG_HEADERS([config.h])

AC_CONFIG_MACRO_DIR([m4])
AM_MAINTAINER_MODE

# Checks for build environment
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_AWK
AC_PROG_INSTALL

LT_INIT([dlopen])
AC_PROG_MAKE_SET

AC_LANG([C++])

AC_CHECK_LIB([dl], [dlopen])


dnl # Platform 
case "$target" in
*-linux*)
        OS=LINUX
        AC_DEFINE(LINUX, 1, "Linux OS")
        ;;
*-sunos*)
        OS=SUNOS
        AC_DEFINE(SUNOS, 1, "SUNOS")
        ;;
*-irix*)
        OS=IRIX
        AC_DEFINE(IRIX, 1, "IRIX OS")
        ;;
*-solaris*)
        OS=SOLARIS
        AC_DEFINE(SOLARIS, 1, "Solaris OS")
        ;;
*-freebsd*)
        OS=FREEBSD
        AC_DEFINE(FREEBSD, 1, "FreeBSD OS")
        ;;
*dec-os*)
        OS=ALPHA
        AC_DEFINE(ALPHA, 1, "Alpha")
        ;;
*)
        OS=UNIX
        AC_DEFINE(UNIX, 1, "Unix")
        ;;
esac

dnl # Hardware

case "$target" in
*i*86*)
        PROC=LINUX
        AC_DEFINE(INTEL, 1, "Intel")
        ;;
esac

# use our own defaults
LDFLAGS="$LDFLAGS -L/lib -L/usr/local/lib -L/usr/lib "
CFLAGS="$_CFLAGS -Wall"
CXXFLAGS="$_CXXFLAGS -Wall -Wno-deprecated "

dnl # check the options

AC_ARG_ENABLE(debug,
  [  --enable-debug            enable debug build ],
  [case "${enableval}" in
    yes) debug=true ;;
    no)  debug=false ;;
    *) AC_MSG_ERROR(bad value ${enableval} for --enable-debug) ;;
  esac],[debug=false])
AM_CONDITIONAL(ENABLE_DEBUG, test x$debug = xtrue)
if test $debug = true ; then
  AC_DEFINE(ENABLE_DEBUG, 1, [enable debug build])
fi

AC_ARG_ENABLE(test,
  [  --enable-test            enable all test applications ],
  [case "${enableval}" in
    yes) tst=true ;;
    no)  tst=false ;;
    *) AC_MSG_ERROR(bad value ${enableval} for --enable-test) ;;
  esac],[tst=false])
AM_CONDITIONAL(ENABLE_TEST, test x$tst = xtrue)
if test $tst = true ; then
  AC_DEFINE(ENABLE_TEST, 1, [enable test applications])
fi

dnl # check size

AC_CHECK_SIZEOF(off_t)

AC_CHECK_LIB([cppunit], [main])

# Checks for header files.
AC_HEADER_DIRENT
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([stdlib.h string.h sys/socket.h sys/time.h termios.h unistd.h float.h types.h limits.h ])


# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL

# Checks for library functions.
AC_CHECK_FUNCS([alarm bzero floor getaddrinfo inet_ntoa gettimeofday memmove memset select socket strdup strchr strerror strstr atoll strtof getopt_long])

PKG_CHECK_MODULES(OPENSSL, openssl  >= 0.9.8 ,
        CXXFLAGS="$CXXFLAGS `pkg-config --cflags openssl`";
        LIBS="$LIBS -lcrypto `pkg-config --libs-only-L --libs-only-other openssl`")

PKG_CHECK_MODULES([LIBPROT], [libprot-0.0])
AC_SUBST([LIBPROT_CFLAGS])
AC_SUBST([LIBPROT_LIBS])

PKG_CHECK_MODULES([LIBFASTQUEUE], [libfastqueue-0.0])
AC_SUBST([LIBFASTQUEUE_CFLAGS])
AC_SUBST([LIBFASTQUEUE_LIBS])

PKG_CHECK_MODULES([LIBGIST], [libgist-0.0])
AC_SUBST([LIBGIST_CFLAGS])
AC_SUBST([LIBGIST_LIBS])

PKG_CHECK_MODULES([LIBIPAP], [libipap-0.0])
AC_SUBST([LIBIPAP_CFLAGS])
AC_SUBST([LIBIPAP_LIBS])

PKG_CHECK_MODULES([LIBANSLP_MSG], [libanslp_msg-0.0])
AC_SUBST([LIBANSLP_MSG_CFLAGS])
AC_SUBST([LIBANSLP_MSG_LIBS])

PKG_CHECK_MODULES([LIBANSLP], [libanslp-0.0])
AC_SUBST([LIBANSLP_CFLAGS])
AC_SUBST([LIBANSLP_LIBS])

PKG_CHECK_MODULES(PQXX, libpqxx >= 3.1)
AC_SUBST(PQXX_CFLAGS)
AC_SUBST(PQXX_LIBS)

PKG_CHECK_MODULES([LIBAUCTIONFDTION], [libauctionfdtion-0.0])
AC_SUBST([LIBAUCTIONFDTION_CFLAGS])
AC_SUBST([LIBAUCTIONFDTION_LIBS])


dnl # checks for programs

if test -z "$XML2_DIR" ; then 
  AC_PATH_PROG(XML_CONFIG, xml2-config, no) 
  if test "$XML_CONFIG" = "no" ; then
    AC_MSG_WARN([cannot find xml2-config])
  else
    XML_LIBS=`$XML_CONFIG --libs` 
    XML_CFLAGS=`$XML_CONFIG --cflags` 
    LDFLAGS="$LDFLAGS $XML_LIBS" 
    CFLAGS="$CFLAGS $XML_CFLAGS" 
    CXXFLAGS="$CXXFLAGS $XML_CFLAGS" 
    CPPFLAGS="$CPPFLAGS $XML_CFLAGS" 
  fi
else          
   LDFLAGS="$LDFLAGS -L$XML2_DIR/lib -lz -lm"          
   CFLAGS="$CFLAGS -I$XML2_DIR/include" 
   CXXFLAGS="$CXXFLAGS -I$XML2_DIR/include" 
   CPPFLAGS="$CPPFLAGS -I$XML2_DIR/include" 
fi

if test "$XSLT_DIR" ; then
   LDFLAGS="$LDFLAGS -L$XSLT_DIR/lib"          
   CFLAGS="$CFLAGS -I$XSLT_DIR/include" 
   CXXFLAGS="$CXXFLAGS -I$XSLT_DIR/include"
   CPPFLAGS="$CPPFLAGS -I$XSLT_DIR/include"
fi

AC_CHECK_HEADERS([libxml/parser.h],,[AC_MSG_ERROR([cannot find libxml2 headers])]) 
AC_CHECK_LIB(xml2, xmlParseFile,
  [XMLLIB="-lxml2"],
  [AC_MSG_ERROR([cannot find libxml2])])
dnl # check xslt lib
AC_CHECK_HEADERS([libxslt/transform.h libxslt/xsltutils.h],,
  [AC_MSG_WARN([cannot find xslt headers])])
AC_CHECK_LIB(xslt, xsltApplyStylesheet,
  [XSLTLIB="-lxslt"],
  [AC_MSG_WARN([cannot find libxsltl])])



AC_CHECK_PROG(DOXY,doxygen,doxygen,[])
if test "$DOXY" = "" ; then
  AC_MSG_WARN([doxygen not installed, can not build documentation])
fi

dnl # set version and data

dnl # Output substitution

AC_DEFINE_UNQUOTED(BUILD_TIME, "`date +"%d/%m/%Y %H:%M:%S"`", "release date")

dnl # set default directories

if test "${prefix}" = "NONE" ; then
  prefix=${ac_default_prefix}
fi

dnl # set default config directory for testing
sysconfdir="${sysconfdir}"

DEF_SYSCONFDIR=`eval echo ${sysconfdir}`
AC_DEFINE_UNQUOTED(DEF_SYSCONFDIR, "$DEF_SYSCONFDIR", "sysconfig dir")

DEF_STATEDIR=`eval echo ${localstatedir}`
AC_DEFINE_UNQUOTED(DEF_STATEDIR, "$DEF_STATEDIR", "state dir")

libdir="${libdir}/auctionmanager"
if test "${exec_prefix}" = "NONE" ; then
  exec_prefix=${prefix}
fi
DEF_LIBDIR=`eval echo ${libdir}`
AC_DEFINE_UNQUOTED(DEF_LIBDIR, "$DEF_LIBDIR", "lib dir")

DEF_BINDIR=`eval echo ${bindir}`
AC_DEFINE_UNQUOTED(DEF_BINDIR, "$DEF_BINDIR", "bin dir")

AC_SUBST(VERSION)
AC_SUBST(REL_DATE)
AC_SUBST(OS)
AC_SUBST(ENABLE_TEST)
AC_SUBST(ENABLE_DEBUG)
AC_SUBST(MATHLIB)
AC_SUBST(XMLLIB)
AC_SUBST(XSLTLIB)
AC_SUBST(DEF_SYSCONFDIR)
AC_SUBST(DEF_STATEDIR)
AC_SUBST(DEF_LIBDIR)
AC_SUBST(DEF_BINDIR)
AC_SUBST(DOXY)

AC_CONFIG_FILES([Makefile \
			     etc/Makefile \
				 src/Makefile \
				 test/Makefile  ] )

AC_OUTPUT
