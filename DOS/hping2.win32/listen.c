/*
 * $smu-mark$
 * $name: listen.c$
 * $author: Salvatore Sanfilippo <antirez@invece.org>$
 * $copyright: Copyright (C) 1999 by Salvatore Sanfilippo$
 * $license: This software is under GPL version 2 of license$
 * $date: Fri Nov  5 11:55:48 MET 1999$
 * $rev: 8$
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#ifndef WIN32
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#else
#include <winsock2.h>
#include <io.h>
#endif

#include "hping2.h" /* hping2.h includes hcmp.h */
#include "globals.h"

void listenmain(void)
{
	int size, ip_size;
	int stdoutFD = fileno(stdout);
#ifndef WIN32
	char packet[IP_MAX_SIZE+linkhdr_size];
#endif
	char *p, *ip_packet;
	struct myiphdr ip;
	__u16 id;
	static __u16 exp_id; /* expected id */

#ifdef WIN32
	char *packet;

	packet = malloc(sizeof(char) * (IP_MAX_SIZE + linkhdr_size));
	if (packet == NULL) {
		fprintf(stderr, "[malloc] failed: %d\n", GetLastError());
		exit(1);
	}
#endif

	exp_id = 1;

	while(1) {
		size = read_packet(packet, IP_MAX_SIZE + linkhdr_size);
		switch(size) {
		case 0:
			continue;
		case -1:
			exit(1);
		}

		/* Skip truncated packets */
		if (size < linkhdr_size + IPHDR_SIZE)
			continue;
		ip_packet = packet + linkhdr_size;


		/* copy the ip header so it will be aligned */
		memcpy(&ip, ip_packet, sizeof(ip));
		id = ntohs(ip.id);
		ip_size = ntohs(ip.tot_len);
		if (size-linkhdr_size > ip_size)
			size = ip_size;
		else
			size -= linkhdr_size;

		if ((p = memstr(ip_packet, sign, size))) {
			if (opt_verbose)
				fprintf(stderr, "packet %d received\n", id);

			if (opt_safe) {
				if (id == exp_id)
					exp_id++;
				else {
					if (opt_verbose)
						fprintf(stderr, "packet not in sequence (id %d) received\n", id);
					send_hcmp(HCMP_RESTART, exp_id);
					if (opt_verbose)
						fprintf(stderr, "HCMP restart from %d sent\n", exp_id);
					continue; /* discard this packet */
				}
			}

			p+=strlen(sign);
			write(stdoutFD, p, size-(p-ip_packet));
		}
	}
}
