/* 
 * $smu-mark$ 
 * $name: sendip.c$ 
 * $author: Salvatore Sanfilippo <antirez@invece.org>$ 
 * $copyright: Copyright (C) 1999 by Salvatore Sanfilippo$ 
 * $license: This software is under GPL version 2 of license$ 
 * $date: Fri Nov  5 11:55:49 MET 1999$ 
 * $rev: 8$ 
 */
 
/* $Id: sendip.c,v 1.7 2003/08/01 13:28:07 njombart Exp $ */

/*
 * Revised for Windows: Rob Turpin <rgturpin@epop3.com> 
 *                      8/22/2004          
 */

#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>


#ifndef WIN32
#include <sys/socket.h>
#include <unistd.h>
#else
#include <winsock2.h>
#include <io.h>
#endif

#include "hping2.h"
#include "globals.h"
#include "dnet.h"

//Code to compute checksum.......
unsigned short in_cksum(u_short *ptr,int nbytes) {

         register u_long sum;
         u_short oddbyte;
         register u_short answer;

         /*
          * Our algorithm is simple, using a 32-bit accumulator (sum),
           * we add sequential 16-bit words to it, and at the end, fold back
            * all the carry bits from the top 16 bits into the lower 16 bits.
             */

             sum = 0;
             while (nbytes > 1)  {
                sum += *ptr++;
                nbytes -= 2;
             }

             /* mop up an odd byte, if necessary */ 
             if (nbytes == 1) { 
                oddbyte = 0;            /* make sure top half is zero */
                *((u_char *) &oddbyte) = *(u_char *)ptr;   /* one byte only */
                sum += oddbyte;
             }

             /*
              * Add back carry outs from top 16 bits to low 16 bits.
               */
               
             sum  = (sum >> 16) + (sum & 0xffff);    /* add high-16 to low-16 */
             sum += (sum >> 16);                     /* add carry */
             answer = ~sum;          /* ones-complement, then truncate to 16 bits */
             return(answer);
}


void send_ip (char* src, char *dst, char *data, unsigned int datalen,
		int more_fragments, unsigned short fragoff, char *options,
		char optlen)
{
	char	*packet;
	char     *frame;
	char     *arpframe;
	int		result,
	        arpresult,
			packetsize;

	struct myiphdr	*ip;

	
    /* objects for james to mess with */
     typedef struct ip_address{
        u_char byte1;
        u_char byte2;
        u_char byte3;
        u_char byte4;
        }ip_address;
        
     typedef struct mac_address{
        u_char byte1;
        u_char byte2;
        u_char byte3;
        u_char byte4;
        u_char byte5;
        u_char byte6;                
        }mac_address;    
    
    struct pcap_pkthdr *header;
    const u_char *pkt_data;
    char ipstring[15];                
    char macstring[17];
    struct arp_entry arpreply;
   	char    resultc;
	route_t *r;
    arp_t *a;
    eth_t *e;
    intf_t *i;
    struct arp_entry arp;
    struct route_entry route;
    struct intf_entry intf;
    struct addr sourceip;
    struct eth_hdr ehdr;
    struct bpf_program pcapfilter;
    char filterstring[50];
    /* end james objects */
    
	packetsize = IPHDR_SIZE + optlen + datalen;
	if ( (packet = malloc(packetsize)) == NULL) {
		perror("[send_ip] malloc()");
		return;
	}
	frame = malloc(14 + packetsize);

	memset(packet, 0, packetsize);
	memset(frame, 0, packetsize + 14);
	ip = (struct myiphdr*) packet;

	/* copy src and dst address */
	memcpy(&ip->saddr, src, sizeof(ip->saddr));
	memcpy(&ip->daddr, dst, sizeof(ip->daddr));

	/* build ip header */
	ip->version	= 4;
	ip->ihl		= (IPHDR_SIZE + optlen + 3) >> 2;
	ip->tos		= ip_tos;

#if defined OSTYPE_FREEBSD || defined OSTYPE_NETBSD || defined OSTYPE_BSDI
/* FreeBSD */
/* NetBSD */
	ip->tot_len	= packetsize;
#else
/* Linux */
/* OpenBSD */
	ip->tot_len	= htons(packetsize);
#endif

	if (!opt_fragment)
	{
		ip->id		= (src_id == -1) ?
			htons((unsigned short) rand()) :
			htons((unsigned short) src_id);
	}
	else /* if you need fragmentation id must not be randomic */
	{
		/* FIXME: when frag. enabled sendip_handler shold inc. ip->id */
		/*        for every frame sent */
		ip->id		= (src_id == -1) ?
			htons(getpid() & 255) :
			htons((unsigned short) src_id);
	}

#if defined OSTYPE_FREEBSD || defined OSTYPE_NETBSD
/* FreeBSD */
/* NetBSD */
	ip->frag_off	|= more_fragments;
	ip->frag_off	|= fragoff >> 3;
#else
/* Linux */
/* OpenBSD */
	ip->frag_off	|= htons(more_fragments);
	ip->frag_off	|= htons(fragoff >> 3); /* shift three flags bit */
#endif

	ip->ttl		= src_ttl;
	if (opt_rawipmode)	ip->protocol = raw_ip_protocol;
	else if	(opt_icmpmode)	ip->protocol = 1;	/* icmp */
	else if (opt_udpmode)	ip->protocol = 17;	/* udp  */
	else			ip->protocol = 6;	/* tcp  */
	ip->check	= 0; /* always computed by the kernel */
    ip->check = in_cksum((u_short *)ip, IPHDR_SIZE); // Attempt to compute the checksum

	/* copies options */
	if (options != NULL)
		memcpy(packet+IPHDR_SIZE, options, optlen);

	/* copies data */
	memcpy(packet + IPHDR_SIZE + optlen, data, datalen);
	
  if (opt_debug == TRUE) {
    unsigned int i;

    for (i=0; i<packetsize; i++)
      printf("%.2X ", packet[i]&255);
    printf("\n");
  }
#ifdef WIN32
// Discovered that this is windows so use libdnet to open sockets.

   addr_pton(ifstraddr,&sourceip); // convert source interface IP to dnet addr

   i = intf_open();
   if (i == NULL)
   {
         fprintf(stderr, "intf_open()");
         intf_close(i);
         result = -1;
         return;
   }

   intf_get_src(i, &intf, &sourceip);

   e = eth_open(intf.intf_name);
   if (e == NULL)
   {
         fprintf(stderr, "eth_open()");
         eth_close(e);
         result = -1;
         return;
   }

   r = route_open(); // open handle r into routing table
    if (r == NULL)
    {
        fprintf(stderr, "route_open()");
        route_close(r);
        result = -1;
        return;
    }
    
   a = arp_open();

    if (a == NULL)
    {
        fprintf(stderr, "arp_open()");
        arp_close(a);
        result = -1;
        return;
    }

   addr_pton(targetstraddr,&route.route_dst); // convert target IP address to dnet addr

   if (route_get(r, &route) < 0)
    {
        arp.arp_pa = route.route_dst; //if the routing table doesn't have a gateway assume local, set arp proto address to target IP
    }
    else
    {
        arp.arp_pa = route.route_gw; // if routing table had a gateway, assume remote, set arp proto address to gateway IP
    }       
    
   route_close(r);
   

   
   if (arp_get(a, &arp) < 0) // try to get the arp entry from the local arp cache on the box.  
      {
//        printf("\nBefore we started all this crap, the target dst was %x.\n", (char*)&remote.sin_addr.s_addr);
        //printf("\nTarget string address is %s\n", targetstraddr);
        //printf("Failed to find MAC for %s in local ARP cache.  Attempting ARP for target now...\n", addr_ntoa(&arp.arp_pa));
        pcap_t *pd; // open a listening handle
        arp_close(a);        
        pd = pcap_open_live(ifname, 60, 1, 500, errbuf); //dunno what these values are.  'dev' is the interface name also used with eth
        

        sprintf(filterstring, "arp and ether dst host %-20s", addr_ntoa(&intf.intf_link_addr)); // create filter string
        pcap_compile(pd, &pcapfilter, filterstring, 1, 0); // compile filter string
        pcap_setfilter(pd, &pcapfilter); // associate filter to pcap handle
        
        arpframe = malloc(60); // allocate 60 bytes for arp frame
        eth_pack_hdr(arpframe, ETH_ADDR_BROADCAST, intf.intf_link_addr.addr_eth, ETH_TYPE_ARP); // build eth header for arp request
        arp_pack_hdr_ethip(arpframe + ETH_HDR_LEN, ARP_OP_REQUEST, intf.intf_link_addr.addr_eth, ip->saddr, ETH_ADDR_BROADCAST, ip->daddr); //build arp request
        arpresult = eth_send(e, arpframe, 60); // send arp request
        
//        pcap_loop(pd, 1, arp_listener, NULL);

        while((resultc = pcap_next_ex(pd, &header, &pkt_data)) >= 0){
            if(resultc == 0) { // if we timed out waiting for a reply
            /* Timeout elapsed */
//                       fprintf(stderr, "No ARP reply received.  Please see release notes for possible explanations.\n");
                       free(arpframe);
                       delaytable_add(sequence, 0, time(NULL), get_msec(), S_SENT);
                       result = 1;
                       pcap_close(pd);
                       eth_close(e);
                       free(frame);
                       break;
                       printf("This is after the return...\n");
//                       exit(1);  
            } // end of what to do if we timed out waiting for a reply
            else if(resultc == -1) { // if we got an error from the listener
                       fprintf(stderr, "Pcap returned an error listening for ARP reply.\n");
                       free(arpframe);
                       eth_close(e);
                       free(frame);
                       exit(1);
                 } // end of what to do if we got an error from the listener
            else { // we got a packet matching our filter
            ip_address *arp_src_ip; 
            mac_address *arp_src_mac;
            arp_src_ip = (ip_address *) (pkt_data + 28);
            arp_src_mac = (mac_address *) (pkt_data + 22);
   
            sprintf(ipstring, "%d.%d.%d.%d", 
                       arp_src_ip->byte1,
                       arp_src_ip->byte2,
                       arp_src_ip->byte3,
                       arp_src_ip->byte4
                       );
                       
            sprintf(macstring, "%x:%x:%x:%x:%x:%x",
                        arp_src_mac->byte1,
                        arp_src_mac->byte2,
                        arp_src_mac->byte3,
                        arp_src_mac->byte4,
                        arp_src_mac->byte5,
                        arp_src_mac->byte6
                        );
                        
//            printf("received arp from IP %s and MAC %s\n", ipstring, macstring);
            if (strcmp(targetstraddr,ipstring) == 0) // if the arp reply is from our target do this
               {
//                  printf("IP received in ARP reply matches our target.\n");

                  addr_pton(ipstring,&arpreply.arp_pa);
                  addr_pton(macstring,&arpreply.arp_ha);

                  a = arp_open();

                  if (a == NULL)
                  {
                    fprintf(stderr, "arp_open()");
                    arp_close(a);
                    result = -1;
                    return;
                  }                  

                  if (arp_add(a, &arpreply) < 0) // try to add arp to cache.  If fail...
                  {
                     fprintf(stderr, "failed to add to ARP cache");
                     arp_close(a);
                     result = -1;
                     exit(1);
                  } // end of failure to add arp entry
                  else // we succeeded in adding an arp entry
                  { 
//                     printf("\nAdded entry to ARP cache for target IP %s and MAC %s\n\n", ipstring, macstring);
                        arp_get(a, &arp);
                        memcpy(frame + 14, packet, packetsize);
                        eth_pack_hdr(frame, arp.arp_ha.addr_eth, intf.intf_link_addr.addr_eth, ETH_TYPE_IP);
                        // put entry in table for rtt calculation
                        delaytable_add(sequence, src_port, time(NULL), get_msec(), S_SENT);
                        result = eth_send(e, frame, packetsize + 14);
                        pcap_close(pd);
                        eth_close(e);
                        free(frame);
                        if (opt_rand_dest) {
                            arp_delete(a, &arp);
                        }
                        arp_close(a);
                        break;
                  } // end of we succeeded to add an arp entry
             } // end of what to do if arp reply is from our target
             else // arp reply NOT from our target
             {    
                      result = -1;
                      return;
             } // end of arp reply not from our target
           }                               
        } // END of the while loop looking for arp replies GO HERE ON BREAK
    }                
   else { 
   arp_close(a);
   memcpy(frame + 14, packet, packetsize);
   eth_pack_hdr(frame, arp.arp_ha.addr_eth, intf.intf_link_addr.addr_eth, ETH_TYPE_IP);
   // put entry in table for rtt calculation
   delaytable_add(sequence, src_port, time(NULL), get_msec(), S_SENT);
   result = eth_send(e, frame, packetsize + 14);
   eth_close(e);
   free(frame);
   }
   
#else

	result = sendto(sockraw, packet, packetsize, 0, (struct sockaddr*)&remote, 
                  sizeof(remote));
#endif

	
	if (result == -1 && errno != EINTR && !opt_rand_dest && !opt_rand_source) {
#ifndef WIN32
		perror("[send_ip] sendto");
		if (close(sockraw) == -1)
		  perror("[ipsender] close(sockraw)");		  
#else
    fprintf(stderr, "[send_ip] sendto: %d\n", WSAGetLastError());
    if (closesocket(sockraw) == -1)
      fprintf(stderr, "[ipsender] closesocket(sockraw): %d\n", 
              WSAGetLastError());
#endif
			
#if (!defined OSTYPE_LINUX) || (defined FORCE_LIBPCAP)
		if (close_pcap() == -1)
			printf("[ipsender] close_pcap failed\n");
#else
		if (close_sockpacket(sockpacket) == -1)
			perror("[ipsender] close(sockpacket)");
#endif /* ! OSTYPE_LINUX || FORCE_LIBPCAP */
		exit(1);
	}

	free(packet);

	/* inc packet id for safe protocol */
	if (opt_safe && !eof_reached)
		src_id++;
}
