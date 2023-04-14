#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])

AC_INIT([nosleep], [0.2], [the Cygwin mailing list <cygwin@cygwin.com>], , [https://launchpad.net/nosleep])

AC_DEFINE(PACKAGE_AUTHORS, ["Andrew E. Schulman"], [Define to the list of authors of this package.])
AC_DEFINE(PACKAGE_COPYRIGHT_YEAR, ["2011"], [Define to the copyright year of this package.])

AC_CONFIG_SRCDIR([src/nosleep.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL

# Checks for libraries.
AC_CHECK_LIB([argp], [argp_parse])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL

# Checks for library functions.
AC_FUNC_FORK

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 test/Makefile])
AC_OUTPUT
