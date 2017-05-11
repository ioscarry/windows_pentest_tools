/* 
 * $smu-mark$ 
 * $name: sendudp.c$ 
 * $author: Salvatore Sanfilippo <antirez@invece.org>$ 
 * $copyright: Copyright (C) 1999 by Salvatore Sanfilippo$ 
 * $license: This software is under GPL version 2 of license$ 
 * $date: Fri Nov  5 11:55:49 MET 1999$ 
 * $rev: 8$ 
 */

/* $Id: send.c,v 1.6 2003/08/01 14:53:08 antirez Exp $ */
 
/*
 * Revised for Windows: Rob Turpin <rgturpin@epop3.com> 
 *                      8/22/2004          
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "hping2.h"
#include "globals.h"

#ifndef WIN32
#include <sys/time.h>
#include <unistd.h>
#else 
#include <windows.h>
#include <sys/timeb.h>
#include <io.h>
#endif


static void select_next_random_source(void)
{
	unsigned char ra[4];

#ifndef WIN32
	ra[0] = hp_rand() & 0xFF;
	ra[1] = hp_rand() & 0xFF;
	ra[2] = hp_rand() & 0xFF;
	ra[3] = hp_rand() & 0xFF;
#else
	ra[0] = rand() & 0xFF;
	ra[1] = rand() & 0xFF;
	ra[2] = rand() & 0xFF;
	ra[3] = rand() & 0xFF;
#endif
	memcpy(&local.sin_addr.s_addr, ra, 4);
	
	if (opt_debug)
		printf("DEBUG: the source address is %u.%u.%u.%u\n",
		    ra[0], ra[1], ra[2], ra[3]);
}

static void select_next_random_dest(void)
{
	unsigned char ra[4];
	char a[4], b[4], c[4], d[4];

	if (sscanf(targetname, "%4[^.].%4[^.].%4[^.].%4[^.]", a, b, c, d) != 4)
	{
		fprintf(stderr,
			"wrong --rand-dest target host, correct examples:\n"
			"  x.x.x.x, 192,168.x.x, 128.x.x.255\n"
			"you typed: %s\n", targetname);
		exit(1);
	}
	a[3] = b[3] = c[3] = d[3] = '\0';

#ifndef WIN32
	ra[0] = a[0] == 'x' ? (hp_rand() & 0xFF) : strtoul(a, NULL, 0);
	ra[1] = b[0] == 'x' ? (hp_rand() & 0xFF) : strtoul(b, NULL, 0);
	ra[2] = c[0] == 'x' ? (hp_rand() & 0xFF) : strtoul(c, NULL, 0);
	ra[3] = d[0] == 'x' ? (hp_rand() & 0xFF) : strtoul(d, NULL, 0);
#else
  ra[0] = a[0] == 'x' ? (rand() & 0xFF) : strtoul(a, NULL, 0);
	ra[1] = b[0] == 'x' ? (rand() & 0xFF) : strtoul(b, NULL, 0);
	ra[2] = c[0] == 'x' ? (rand() & 0xFF) : strtoul(c, NULL, 0);
	ra[3] = d[0] == 'x' ? (rand() & 0xFF) : strtoul(d, NULL, 0);
#endif
	memcpy(&remote.sin_addr.s_addr, ra, 4);
    sprintf(targetstraddr, "%u.%u.%u.%u", ra[0], ra[1], ra[2], ra[3]);
	if (opt_debug) {
		printf("DEBUG: the dest address is %u.%u.%u.%u\n",
				ra[0], ra[1], ra[2], ra[3]);
	}
}

/* The signal handler for SIGALRM will send the packets */
#ifndef WIN32
void send_packet()
#else
void CALLBACK send_packet(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1, 
                          DWORD dw2) 
#endif
{
	int errno_save = errno;

	if (opt_rand_dest)
		select_next_random_dest();
	if (opt_rand_source)
		select_next_random_source();

	if (opt_rawipmode)	      send_rawip();
	else if (opt_icmpmode)	  send_icmp();
	else if (opt_udpmode)	    send_udp();
	else			                send_tcp();
	sent_pkt++;
#ifndef WIN32
  Signal(SIGALRM, send_packet);
#endif

  if (count != -1 && count == sent_pkt) { /* count reached? */
#ifndef WIN32
    Signal(SIGALRM, print_statistics);
    alarm(COUNTREACHED_TIMEOUT);
#else
    setTimer(print_statistics, COUNTREACHED_TIMEOUT * 1000, TIME_ONESHOT);
#endif
  } 
  else if (!opt_listenmode) {
#ifndef WIN32    
    if (opt_waitinusec == FALSE)
        alarm(sending_wait);
    else
		    setitimer(ITIMER_REAL, &usec_delay, NULL);
#else
    if (opt_waitinusec == FALSE)
      setTimer(send_packet, sending_wait * 1000, TIME_ONESHOT);
    else
      setTimer(send_packet, msec_delay.millitm, TIME_ONESHOT);
#endif
  }
  errno = errno_save;
}
