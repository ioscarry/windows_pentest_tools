/*
 * $smu-mark$
 * $name: memlockall.c$
 * $other_author: Alfonso De Gregorio <dira@speedcom.it>
 * $other_copyright: Copyright (C) 1999 by Alfonso De Gregorio
 * $license: This software is under GPL version 2 of license$
 * $date: Fri Nov  5 11:55:48 MET 1999$
 * $rev: 2$
 */
 
/*
 * Revised for Windows: Rob Turpin <rgturpin@epop3.com> 
 *                      7/03/2004          
 */

#ifndef WIN32
#include <unistd.h>
#include <sys/mman.h>
#endif

int memlockall(void)
{
#ifdef _POSIX_MEMLOCK
	return ( mlockall(MCL_CURRENT|MCL_FUTURE) );
#endif
	return (-1);
}

