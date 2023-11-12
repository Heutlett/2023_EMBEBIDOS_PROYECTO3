AC_INIT([libfilter], [1.0], [adrian.araya.420@gmail.com])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_PROG_CC
AM_PROG_AR
LT_INIT
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile lib/Makefile src/Makefile])
AM_PROG_CC_C_O
AM_CFLAGS="-fopenmp $AM_CFLAGS"
AC_OUTPUT
