AC_INIT([xbox], [0.2])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AC_PATH_XTRA
AS_IF([test "x$no_x" = "xyes"],
  [AC_MSG_ERROR(["Error: does not have X11"])]])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
