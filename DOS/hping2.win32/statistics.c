/* 
 * $smu-mark$ 
 * $name: statistics.c$ 
 * $author: Salvatore Sanfilippo <antirez@invece.org>$ 
 * $copyright: Copyright (C) 1999 by Salvatore Sanfilippo$ 
 * $license: This software is under GPL version 2 of license$ 
 * $date: Fri Nov  5 11:55:50 MET 1999$ 
 * $rev: 8$ 
 */
 
/*
 * Revised for Windows: Rob Turpin <rgturpin@epop3.com> 
 *                      8/22/2004          
 */

#include <stdio.h>
#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#include <signal.h>
#include <mmsystem.h>
#include "dnet.h"
#endif

#include "hping2.h"
#include "globals.h"

#ifdef WIN32
extern UINT      wTimerID;
#endif

#ifndef WIN32
void print_statistics(int signal_id)
#else
void CALLBACK print_statistics(UINT wTimerID, UINT msg, DWORD dwUser, 
                                DWORD dw1, DWORD dw2)
#endif
{
	unsigned int lossrate;

#if (defined OSTYPE_LINUX) && (!defined FORCE_LIBPCAP)
	close_sockpacket(sockpacket);
#else
	close_pcap();
#endif /* OSTYPE_LINUX && !FORCE_LIBPCAP */

	if (recv_pkt > 0)
		lossrate = 100 - ((recv_pkt*100)/sent_pkt);
	else if (!sent_pkt)
	  lossrate = 0;
	else
	  lossrate = 100;

	fprintf(stderr, "\n--- %s hping statistics ---\n", targetname);
	fprintf(stderr, "%d packets transmitted, %d packets received, "
			"%d%% packet loss\n", sent_pkt, recv_pkt, lossrate);
	if (out_of_sequence_pkt)
		fprintf(stderr, "%d out of sequence packets received\n",
			out_of_sequence_pkt);
	fprintf(stderr, "round-trip min/avg/max = %.1f/%.1f/%.1f ms\n",
		rtt_min, rtt_avg, rtt_max);

	/* manage exit code */
#ifdef WIN32
  arp_t* a;
  killPeriod();
  WSACleanup();
  
  a = arp_open();
  struct arp_entry arp;
  
  addr_aton(targetstraddr, &arp.arp_pa);
  arp_delete(a, &arp);
  arp_close(a);
#endif
	
  if (opt_tcpexitcode) {
		exit(tcp_exitcode);
	}
	else if (recv_pkt)
	  exit(0);
	else
	  exit(1);
}

#ifdef WIN32
void win_print_statistics(int signalID)
{ 
  timeKillEvent( wTimerID );

  if (signalID == SIGINT) {
    setTimer(print_statistics , 2000, TIME_ONESHOT);
  }
  else {
    print_statistics(0, 0, 0, 0, 0);
  }
}
#endif
