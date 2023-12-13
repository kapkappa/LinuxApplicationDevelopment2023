#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([Guesser], [1.0], [gse], [I18n])
AM_INIT_AUTOMAKE([foreign])
DX_INIT_DOXYGEN([I18n])
AC_CONFIG_SRCDIR([guess.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([libintl.h locale.h stdio.h string.h ctype.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([setlocale bindtextdomain textdomain])

AC_CONFIG_FILES([Makefile
                 Doxyfile])
AC_OUTPUT
