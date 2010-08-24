dnl This file is part of Rubik.
dnl
dnl Rubik is free software: you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation, either version 3 of the License, or
dnl (at your option) any later version.
dnl
dnl Rubik is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with Rubik.  If not, see <http://www.gnu.org/licenses/>

AC_PREREQ(2.59)

AC_INIT([rubik],[2.0],[sakhnik@gmail.com])

AM_INIT_AUTOMAKE([1.9])

AC_PROG_CXX

AC_LANG_PUSH([C++])

AC_CHECK_HEADER(ncursesw/ncurses.h,
                :,
                AC_MSG_ERROR([required <ncursesw/ncurses.h> is missing]))
AC_CHECK_LIB(ncursesw,initscr)

AC_LANG_POP

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
