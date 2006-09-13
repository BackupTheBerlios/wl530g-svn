/* Minimum guaranteed maximum values for system limits.  Linux version.
   Copyright (C) 1993, 94, 95, 96, 97, 98, 2000 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

/* The kernel header pollutes the namespace with the NR_OPEN symbol
   and defines LINK_MAX although filesystems have different maxima.  A
   similar thing is true for OPEN_MAX: the limit can be changed at
   runtime and therefore the macro must not be defined.  Remove this
   after including the header if necessary.  */
#ifndef NR_OPEN
# define __undef_NR_OPEN
#endif
#ifndef LINK_MAX
# define __undef_LINK_MAX
#endif
#ifndef OPEN_MAX
# define __undef_OPEN_MAX
#endif

/* The kernel sources contain a file with all the needed information.  */
#include <linux/limits.h>

/* Have to remove NR_OPEN?  */
#ifdef __undef_NR_OPEN
# undef NR_OPEN
# undef __undef_NR_OPEN
#endif
/* Have to remove LINK_MAX?  */
#ifdef __undef_LINK_MAX
# undef LINK_MAX
# undef __undef_LINK_MAX
#endif
/* Have to remove OPEN_MAX?  */
#ifdef __undef_OPEN_MAX
# undef OPEN_MAX
# undef __undef_OPEN_MAX
#endif

/* Maximum amount by which a process can descrease its asynchronous I/O
   priority level.  */
#define AIO_PRIO_DELTA_MAX	20
