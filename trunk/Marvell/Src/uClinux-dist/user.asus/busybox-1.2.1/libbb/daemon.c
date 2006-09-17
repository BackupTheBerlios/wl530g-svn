/*
 * daemon() function for uClinux systems without MMU and fork().
 *
 * Copyright (C) 2005-2006 by Jamie Lokier <jamie@shareable.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "busybox.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>
#include <signal.h>
#include <errno.h>

#define _XDAEMON_NOMMU_HACK
#ifdef _XDAEMON_NOMMU_HACK

#define _PATH_DEVNULL "/dev/null"

static inline int fork_and_exit( void )
{
#if defined(__linux__) && (defined(__i386__) || defined(__arm__))

	/* Equivalent to fork-then-exit which allows the parent process
	   to exit properly even when fork() isn't available.  The trick
	   is to use clone(), and make the parent exit without
	   clobbering any memory.  Signals must be blocked to prevent
	   that clobbering.  Unfortunately each implementation of this
	   is architecture-specific. */

# ifndef CLONE_VM
#  define CLONE_VM	0x00000100
#  define CLONE_FS	0x00000200
#  define CLONE_FILES	0x00000400
#  define CLONE_SIGHAND	0x00000800
# endif

	int result;
	sigset_t new_set, old_set;
	sigfillset(&new_set);
	sigprocmask(SIG_BLOCK, &new_set, &old_set);

	{
		int flags = (CLONE_VM | CLONE_FS | CLONE_FILES
			     | CLONE_SIGHAND | SIGCHLD);

# ifdef __i386__
		__asm__ __volatile__ (
#  ifdef __PIC__
			"pushl	%%ebx\n\t"
			"movl	%1,%%ebx\n\t"
#  endif /* __PIC__ */
			"movl	$120,%0\n\t"
			"int	$0x80\n\t"
			"testl	%0,%0\n\t"
			"jle	0f\n\t"
			"movl	$1,%0\n\t"
			"int	$0x80\n"
			"0:"
#  ifdef __PIC__
			"\n\tpopl	%%ebx"
			: "=a" (result) : "ir" (flags), "c" ((int) 0)
#  else /* not __PIC__ */
			: "=a" (result) : "b" (flags), "c" ((int) 0)
#  endif /* not __PIC__ */
			);
# endif /* __i386__ */
# ifdef __arm__
		register int r0 __asm__("r0"), stack __asm__("r1") = 0;
		__asm__ __volatile__ (
#  ifdef __thumb__
			/* This Thumb version hasn't been tested.
			   If you do test it, please delete this comment. */
			"push	{r7}\n\t"
			"mov	r7, #120\t@ clone\n\t"
			"swi	0\n\t"
			"cmp	r0, #0\n\t"
			"ble	0f\n\t"
			"mov	r0, #0\n\t"
			"mov	r7, #1\t\t@ exit\n\t"
			"swi	0\n"
			"0:\t"
			"pop	{r7}"
#  else  /* Standard ARM, not Thumb. */
			"swi	0x900000+120\t@ clone\n\t"
			"cmp	r0, #0\n\t"
			"ble	0f\n\t"
			"mov	r0, #0\n\t"
			"swi	0x900000+1\t@ exit\n"
			"0:"
#  endif /* Standard ARM, not Thumb. */
			: "=r" (r0)
			: "0" (flags), "r" (stack)
			: "cc", "lr");
		result = r0;
# endif /* __arm__ */

	}
	sigprocmask(SIG_SETMASK, &old_set, (sigset_t *)0);
	if (result == 0)
		return(0);
	errno = -result;
	return(-1);

#else /* Can't do the special thing. */

	/* Half-hearted version with vfork().  The parent process won't
	   be able to exit until the child does, so this keeps extra
	   processes around, and requires the program to be started in
	   the background. */
	switch (vfork()) {
		case -1:
			return(-1);
		case 0:
			return(0);
		default:
			_exit(0);
	}

#endif /* Can't do the special thing. */
}

int daemon( int nochdir, int noclose )
{
	int fd;

	if (fork_and_exit() == -1)
		return(-1);

	if (setsid() == -1)
		return(-1);

	/* Make certain we are not a session leader, or else we
	 * might reacquire a controlling terminal */
	if (fork_and_exit() == -1)
		return(-1);

	if (!nochdir)
		chdir("/");

	if (!noclose && (fd = open(_PATH_DEVNULL, O_RDWR, 0)) != -1) {
		dup2(fd, STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		dup2(fd, STDERR_FILENO);
		if (fd > 2)
			close(fd);
	}
	return(0);
}

#endif
