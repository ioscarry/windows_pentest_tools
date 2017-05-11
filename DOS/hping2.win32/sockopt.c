/* 
 * $smu-mark$ 
 * $name: sockopt.c$ 
 * $author: Salvatore Sanfilippo <antirez@invece.org>$ 
 * $copyright: Copyright (C) 1999 by Salvatore Sanfilippo$ 
 * $license: This software is under GPL version 2 of license$ 
 * $date: Fri Nov  5 11:55:49 MET 1999$ 
 * $rev: 8$ 
 */ 

#include <stdio.h>
#include <sys/types.h>

#ifndef WIN32
#include <sys/socket.h>
#include <netinet/in.h> /* IP_PROTOIP */
#else
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

void socket_broadcast(int sd)
{
	const int one = 1;

	if (setsockopt(sd, SOL_SOCKET, SO_BROADCAST,
		(char *)&one, sizeof(one)) == -1)
	{
		printf("[socket_broadcast] can't set SO_BROADCAST option\n");
		/* non fatal error */
	}
}

void socket_iphdrincl(int sd)
{
	const int one = 1;

	if (setsockopt(sd, IPPROTO_IP, IP_HDRINCL,
		(char *)&one, sizeof(one)) == -1)
	{
		printf("[socket_broadcast] can't set IP_HDRINCL option\n");
		/* non fatal error */
	}
}
