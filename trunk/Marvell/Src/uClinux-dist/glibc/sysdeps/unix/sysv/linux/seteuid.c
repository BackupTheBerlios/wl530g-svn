/* Copyright (C) 1998, 1999 Free Software Foundation, Inc.
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

#include <errno.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

#include "kernel-features.h"

#if defined __NR_setresuid || __ASSUME_SETRESUID_SYSCALL > 0

extern int __setresuid (uid_t ruid, uid_t euid, uid_t suid);

int
seteuid (uid_t uid)
{
  int result;

  if (uid == (uid_t) ~0)
    {
      __set_errno (EINVAL);
      return -1;
    }

  /* First try the syscall.  */
  result = __setresuid (-1, uid, -1);
# if __ASSUME_SETRESUID_SYSCALL == 0
  if (result == -1 && errno == ENOSYS)
    /* No system call available.  Use emulation.  This may not work
       since `setreuid' also sets the saved user ID when UID is not
       equal to the real user ID, making it impossible to switch back.  */
    result = __setreuid (-1, uid);
# endif

  return result;
}
#else
# include <sysdeps/unix/bsd/seteuid.c>
#endif
