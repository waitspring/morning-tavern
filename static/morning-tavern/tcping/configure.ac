AC_PREREQ([2.69])
AC_INIT([morning-tavern], [1.0.3], [newsfuxuanming@foxmail.com])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/tcping.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])

AC_PROG_CC

AC_CHECK_HEADERS([arpa/inet.h netdb.h stdlib.h string.h sys/socket.h sys/time.h unistd.h])

AC_FUNC_ERROR_AT_LINE
AC_CHECK_FUNCS([gettimeofday memset socket strrchr])

AC_OUTPUT

