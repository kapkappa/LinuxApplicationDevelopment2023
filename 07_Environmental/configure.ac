#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([Environmental], [1.0], [gse])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_SRCDIR([rhasher.c])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([rhash], [rhash_library_init],[],[AC_MSG_ERROR([Rhash is needed])])
AC_CHECK_LIB([readline],[readline])

# Checks for header files.
AC_CHECK_HEADER([rhash.h])
AC_CHECK_HEADER([readline/readline.h])
AC_CHECK_HEADER([readline/history.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strerror])

AC_ARG_ENABLE([readline], AS_HELP_STRING([--enable-readline], [Enable readline]), AC_DEFINE(READLINE,[],[Enable readline]))

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
