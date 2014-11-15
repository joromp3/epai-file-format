AC_INIT([epai], [0.0.0.0], [tajjada@gmail.com])
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign -Wall])
AC_CONFIG_HEADER([config.h])

AC_SUBST([includedir], [${includedir}/${PACKAGE}])

AM_PROG_AR
LT_INIT
AC_PROG_CC

AC_CONFIG_FILES([Makefile lib/Makefile chk/Makefile enc/Makefile
		 dec/Makefile poke/Makefile txt/Makefile])

AC_OUTPUT
