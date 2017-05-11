/* getifname.c -- network interface handling
 * Copyright(C) 1999,2000,2001 Salvatore Sanfilippo <antirez@invece.org>
 * Copyright(C) 2001 by Nicolas Jombart <Nicolas.Jombart@hsc.fr>
 * This code is under the GPL license */

/* BSD support thanks to Nicolas Jombart <Nicolas.Jombart@hsc.fr> */

/*
 * Revised for Windows: Rob Turpin <rgturpin@epop3.com> 
 *                      7/03/2004          
 */

#include <stdio.h>		/* perror */
#include <string.h>

#ifndef WIN32
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>		/* struct sockaddr_in */
#include <arpa/inet.h>		/* inet_ntoa */
#include <net/if.h>
#include <unistd.h>		/* close */
#else
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <io.h>
#endif

#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || \
    defined(__bsdi__) || defined(__APPLE__)
#include <stdlib.h>
#include <ifaddrs.h>
#endif /* defined(__*BSD__) */

#include "hping2.h"
#include "globals.h"

#if !defined(__FreeBSD__) && !defined(__OpenBSD__) && !defined(__NetBSD__) && !defined(__linux__) && !defined(__sun__) && !defined(WIN32) && \
!defined(__bsdi__) && !defined(__APPLE__)
#error Sorry, interface code not implemented.
#endif

#ifdef __sun__
#include <sys/sockio.h>
#include <net/route.h>
#include <net/if_dl.h>
#endif

static int get_output_if(struct sockaddr_in *dest, struct sockaddr_in *ifip);

#if (defined OSTYPE_LINUX) || (defined __sun__)
int get_if_name(void)
{
  int fd;
  struct ifconf	ifc;
  struct ifreq	ibuf[16],
         ifr,
        *ifrp,
        *ifend;
  struct sockaddr_in sa;
  struct sockaddr_in output_if_addr;
  int known_output_if = 0;

  /* Try to get the output interface address according to
   * the OS routing table */
  if (ifname[0] == '\0') {
    if (get_output_if(&remote, &output_if_addr) == 0) {
        known_output_if = 1;
        if (opt_debug)
          printf("DEBUG: Output interface address: %s\n",
        inet_ntoa(sa.sin_addr));
    } 
    else {
      fprintf(stderr, "Warning: Unable to guess the output "
	                  "interface\n");
    }
  }

  if ( (fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    perror("[get_if_name] socket(AF_INET, SOCK_DGRAM, 0)");
    return -1;
  }

  memset(ibuf, 0, sizeof(struct ifreq)*16);
  ifc.ifc_len = sizeof ibuf;
  ifc.ifc_buf = (caddr_t) ibuf;

  /* gets interfaces list */
  if ( ioctl(fd, SIOCGIFCONF, (char*)&ifc) == -1 ||
       ifc.ifc_len < sizeof(struct ifreq)		) {
    perror("[get_if_name] ioctl(SIOCGIFCONF)");
    close(fd);
    return -1;
  }

  /* ifrp points to buffer and ifend points to buffer's end */
  ifrp = ibuf;
  ifend = (struct ifreq*) ((char*)ibuf + ifc.ifc_len);

  for (; ifrp < ifend; ifrp++) {
    strlcpy(ifr.ifr_name, ifrp->ifr_name, sizeof(ifr.ifr_name));

    if ( ioctl(fd, SIOCGIFFLAGS, (char*)&ifr) == -1) {
      if (opt_debug)
	      perror("DEBUG: [get_if_name] ioctl(SIOCGIFFLAGS)");
      continue;
    }

    if (opt_debug)
      printf("DEBUG: if %s: ", ifr.ifr_name);

    /* Down interface? */
    if ( !(ifr.ifr_flags & IFF_UP) ) {
      if (opt_debug)
        printf("DOWN\n");
      continue;
    }

    if (known_output_if) {
      /* Get the interface address */
      if (ioctl(fd, SIOCGIFADDR, (char*)&ifr) == -1) {
        perror("[get_if_name] ioctl(SIOCGIFADDR)");
        continue;
      }
      /* Copy it */
      memcpy(&sa, &ifr.ifr_addr, sizeof(struct sockaddr_in));
      /* Check if it is what we are locking for */
      if (sa.sin_addr.s_addr != output_if_addr.sin_addr.s_addr) {
        if (opt_debug)
          printf("The address doesn't match\n");
        continue;
      }
    } 
    else if (ifname[0] != '\0' && !strstr(ifr.ifr_name, ifname)) {
      if (opt_debug)
	      printf("Don't Match (but seems to be UP)\n");
      continue;
    }

    if (opt_debug)
      printf("OK\n");

    /* interface found, save if name */
    strlcpy(ifname, ifr.ifr_name, 1024);

    /* get if address */
    if ( ioctl(fd, SIOCGIFADDR, (char*)&ifr) == -1) {
      perror("DEBUG: [get_if_name] ioctl(SIOCGIFADDR)");
      exit(1);
    }

    /* save if address */
    memcpy(&sa, &ifr.ifr_addr, sizeof(struct sockaddr_in));
    strlcpy(ifstraddr, inet_ntoa(sa.sin_addr), 1024);

    /* get if mtu */
    if ( ioctl(fd, SIOCGIFMTU, (char*)&ifr) == -1) {
      perror("Warning: [get_if_name] ioctl(SIOCGIFMTU)");
      fprintf(stderr, "Using a fixed MTU of 1500\n");
      h_if_mtu = 1500;
    }
    else {
#ifdef __sun__
      /* somehow solaris is braidamaged in wrt ifr_mtu */
      h_if_mtu = ifr.ifr_metric;
#else
      h_if_mtu = ifr.ifr_mtu;
#endif
    }
    close(fd);
    return 0;
  }
  /* interface not found, use 'lo' */
  strlcpy(ifname, "lo", 1024);
  strlcpy(ifstraddr, "127.0.0.1", 1024);
  h_if_mtu = 1500;

  close(fd);
  return 0;
}

#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || \
      defined(__bsdi__) || defined(__APPLE__)


/* return interface informations :
   - from the specified (-I) interface
   - from the routing table
   - or at least from the first UP interface found
*/
int get_if_name(void)
{
  /* variable declarations */
  struct ifaddrs	*ifap, *ifa;
  char			current_if_name[24];
  char			saved_ifname[24];
  struct sockaddr_in	output_if_addr;
#ifdef __NetBSD__
  int s;
  struct ifreq ifr;
#endif  /* __NetBSD__ */

  if (getifaddrs(&ifap) < 0)
    perror("getifaddrs");

  saved_ifname[0] = 0;

  /* lookup desired interface */
  if(ifname[0] == 0) {
    /* find gateway interface from kernel */
    if (get_output_if(&remote, &output_if_addr) == 0) {
      if (opt_debug)
        printf("DEBUG: Output interface address: %s\n",
	           inet_ntoa(output_if_addr.sin_addr));
      /* Put something in saved_ifname in order to tell
	     that the output adress is known */
      saved_ifname[0] = 'X'; saved_ifname[1] = 0;
    } 
    else {
      fprintf(stderr, "Warning: Unable to guess the output "
	                  "interface\n");
    }
  }
  else {
    /* use the forced interface name */
    strlcpy(saved_ifname,ifname,24);
  }

  /* get interface information */
  for (ifa = ifap; ifa; ifa = ifa->ifa_next) {

    if (opt_debug) printf("\n DEBUG: if %s: ", ifa->ifa_name);

    /* print if the data structure is null or not */
    if (ifa->ifa_data) {
      if(opt_debug) printf("DEBUG: (struct DATA) "); }
    else
      if(opt_debug) printf("DEBUG: (struct DATA is NULL) ");

    if (!(ifa->ifa_flags & IFF_UP)) {       /* if down */
      if (opt_debug)
	printf("DEBUG: DOWN");
      continue; 
    }

    if ((ifa->ifa_flags & IFF_LOOPBACK)&&
	(strncmp(saved_ifname,"lo0",3))) {  /* if loopback */
      if (opt_debug)
	printf("DEBUG: LOOPBACK, SKIPPED");
      continue;
    }

    if (ifa->ifa_addr->sa_family == AF_LINK) {
      if (opt_debug)
	printf("DEBUG: AF_LINK ");
      strlcpy(ifname,ifa->ifa_name,1024);
      strlcpy(current_if_name,ifa->ifa_name,24);

      /* I don't know why NetBSD behavior is not the same */
#ifdef __NetBSD__
      memset( &ifr, 0, sizeof(ifr));
      strlcpy(ifr.ifr_name, ifa->ifa_name, sizeof(ifr.ifr_name));
      if( sizeof(ifr.ifr_addr) >= ifa->ifa_addr->sa_len )
	memcpy(&ifr.ifr_addr, ifa->ifa_addr, 
	       ifa->ifa_addr->sa_len);
      if( (s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
	perror("[get_if_name] socket");
	return -1;
      }
      if (ioctl(s, SIOCGIFMTU, (caddr_t)&ifr) < 0) h_if_mtu = 0;
      else h_if_mtu = ifr.ifr_mtu;
      close(s);
#else
      if( ifa->ifa_data )
	h_if_mtu = ((struct if_data *)ifa->ifa_data)->ifi_mtu;
      else {
	h_if_mtu = 1500;
	fprintf(stderr, "Warning: fixing MTU to 1500 !\n");
      }
#endif /* __NetBSD__ */
      continue;
    }

    if (ifa->ifa_addr->sa_family == AF_INET6) {
      if (opt_debug)
	printf("AF_INET6 ");
      continue;
    }

    if (ifa->ifa_addr->sa_family == AF_INET) {
      if (opt_debug)
	printf("AF_INET ");

      if(strncmp(ifa->ifa_name,current_if_name,24))
	continue; /* error */

      if(opt_debug) printf("OK\n");

      strlcpy(ifname,ifa->ifa_name,1024);
      strlcpy(ifstraddr, 
              inet_ntoa(((struct sockaddr_in *)ifa->ifa_addr)->sin_addr),
              1024);
			
      if( (saved_ifname[0] == 0) || 
	  (!strncmp(ifa->ifa_name, saved_ifname, 24)) ||
	  ( ((struct sockaddr_in *)ifa->ifa_addr)->sin_addr.s_addr ==
	    output_if_addr.sin_addr.s_addr) )
	    break; /* asked if found or first UP interface */
    }

    /* interface not found, use hardcoded 'lo' */
    strlcpy(ifname, "lo0", 1024);
    strlcpy(ifstraddr, "127.0.0.1", 1024);
    h_if_mtu = 1500;
  }

  freeifaddrs(ifap);
  return 0;
}

#endif /* __*BSD__ */

#ifdef WIN32
int get_if_name(void)
{
  SOCKET            s;
  DWORD             bytesReturned;
  char             *pAddrString = NULL;
  SOCKADDR_IN      *pAddrInet = NULL,
                    sa,
                    output_if_addr;
  INTERFACE_INFO    localAddr[10];
  u_long            SetFlags;
  int               numLocalAddr,
                    wsError,
                    i,
                    known_output_if = 0;
  IP_ADAPTER_INFO   ip_adapters[10];
  IP_ADAPTER_INFO  *pNextAdapter;
  long              adapterSize;
  

  if (ifstraddr[0] == '\0') {
    if (get_output_if(&remote, &output_if_addr) == 0) {
      known_output_if = 1;
      if (opt_debug)
        printf("DEBUG: Output interface address: %s\n", 
	           inet_ntoa(output_if_addr.sin_addr));
    }
    else {
      fprintf(stderr, "Warning: Unable to guess the output "
	                    "interface\n");
    }
  }
 
  s = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, 0);
  if (s == INVALID_SOCKET) {
    fprintf (stderr, "[get_if_name] WSASocket failed: %d\n", GetLastError());
    return -1;
  }

  wsError = WSAIoctl(s, SIO_GET_INTERFACE_LIST, NULL, 0, &localAddr,
                     sizeof(localAddr), &bytesReturned, NULL, NULL);
  if (wsError == SOCKET_ERROR) {
    fprintf(stderr, "[get_if_name] WSAIoctl failed: %d\n", GetLastError());
    closesocket(s);
    return -1;
  }
  closesocket(s);

  numLocalAddr = (bytesReturned / sizeof(INTERFACE_INFO));
  for (i = 0; i < numLocalAddr; ++i) {
    pAddrInet = (SOCKADDR_IN *)&localAddr[i].iiAddress;
    pAddrString = inet_ntoa(pAddrInet->sin_addr);
    SetFlags = localAddr[i].iiFlags;
    
    if (opt_debug)
      printf("DEBUG: interface IP: %s ", pAddrString);
    
    if (!(SetFlags & IFF_UP)) {
      if (opt_debug)
        printf("DOWN\n");
      continue;
    }
    
    if (known_output_if) {
      memcpy(&sa, &localAddr[i].iiAddress.AddressIn, sizeof(SOCKADDR_IN));
      
      if (sa.sin_addr.s_addr != output_if_addr.sin_addr.s_addr) {
        if (opt_debug)
          printf("The address doesn't match\n");
        continue;
      }
    }
    else if (ifstraddr[0] != '\0' && !strstr(pAddrString, ifstraddr)) {
      if (opt_debug)
        printf("Don't Match (but seems to be UP)\n");
      continue;
    }
    
    if (opt_debug)
      printf("OK\n");
      
    /* interface found, save if IP */
    strlcpy(ifstraddr, pAddrString, 1024);

    adapterSize = sizeof(IP_ADAPTER_INFO) * 10;
    if (GetAdaptersInfo(ip_adapters, &adapterSize)) {
      fprintf(stderr, "[get_if_name] GetAdaptersInfo failed: %d\n", 
              GetLastError());
      return -1;
    }
  
    for (pNextAdapter = ip_adapters; pNextAdapter != NULL; 
         pNextAdapter = pNextAdapter->Next) {
      if (cmpIPAddr(pNextAdapter, ifstraddr)) {
        if (pcap_get_if_name(ifstraddr))
          return -1;
        strlcpy(description, pNextAdapter->Description, 1024);
        memcpy(&sa, &localAddr[i].iiAddress.AddressIn, sizeof(SOCKADDR_IN));
        if ((h_if_mtu = getMTU(pNextAdapter)) == -1)
          return -1;
                
        return 0;
      }
    } 
  }
  return -1;
}


/*
 *  To meke pcap happy, have to get the name of the interface using pcap
 *  functions
 */
int pcap_get_if_name(char *addr)
{
  pcap_if_t *alldevs;
  pcap_if_t *d;
  pcap_addr_t *a;
  char errbuf[PCAP_ERRBUF_SIZE + 1];        
  
  
  /* Retrieve the interfaces list */ 
  if (pcap_findalldevs(&alldevs, errbuf) == -1) {
    fprintf(stderr,"[pcap_get_if_name] pcap_findalldevs failed: %s\n", errbuf);
    return -1;
  }
    
  /* Scan the list */ 
  for (d = alldevs; d; d = d->next) {
    for (a = d->addresses; a; a = a->next) {
      if (a->addr->sa_family == AF_INET) {
        if (a->addr) {
          if (strcmp(inet_ntoa(((struct sockaddr_in *)a->addr)->sin_addr), 
                     addr) == 0) {
            strlcpy(ifname, d->name, 1024);
            pcap_freealldevs(alldevs);
            return 0;
          }
        }
      }
    }
  } 
  fprintf(stderr, "[pcap_get_if_name] failed\n");
  return -1;                                
}


/*
 *  Traverse through the list of IP's an *adapter may have and compare
 *  to the given *addr.  If there is a match, return 1, else return 0
 */
int cmpIPAddr(IP_ADAPTER_INFO *adapter, char *addr)
{
  IP_ADDR_STRING *pAddrString = &(adapter->IpAddressList);
  
  for (pAddrString; pAddrString != NULL; pAddrString = pAddrString->Next) {
    if (!strcmp((char *)&(pAddrString->IpAddress), addr))
      return 1;
  }
  return 0;
}


/*
 *  Determine the type of network adapter and return its MTU value
 *  error - return -1
 */
int getMTU(IP_ADAPTER_INFO *adapter)
{
  switch (adapter->Type) {
  case MIB_IF_TYPE_ETHERNET:
  case MIB_IF_TYPE_LOOPBACK:
  case MIB_IF_TYPE_OTHER:
  case MIB_IF_TYPE_PPP:
    return 1500;
  case MIB_IF_TYPE_FDDI:
    return 4352;
  case MIB_IF_TYPE_SLIP:
    return 1006;
  case MIB_IF_TYPE_TOKENRING:
    return 4464;
  default:
    return -1;
  }
}
    
#endif

/* Try to obtain the IP address of the output interface according
 * to the OS routing table. Derived from R.Stevens */
int get_output_if(struct sockaddr_in *dest, struct sockaddr_in *ifip)
{
  int sock_rt;
  int len, on=1;
  struct sockaddr_in iface_out;

 
  memset(&iface_out, 0, sizeof(iface_out));
  sock_rt = socket(AF_INET, SOCK_DGRAM, 0 );
    
  dest->sin_port = htons(11111);
#ifndef WIN32
  if (setsockopt(sock_rt, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on)) == -1)
#else
  if (setsockopt(sock_rt, SOL_SOCKET, SO_BROADCAST, (char *)&on, sizeof(on))
      == -1)
#endif
  {
    if (opt_debug)
      perror("DEBUG: [get_output_if] setsockopt(SOL_SOCKET, "
             "SO_BROADCAST");
#ifndef WIN32
    close(sock_rt);   
#else
    closesocket(sock_rt);
#endif
    return -1;
  }
  
  if (connect(sock_rt, (struct sockaddr*)dest, sizeof(struct sockaddr_in))
      == -1 ) {
    if (opt_debug)
      perror("DEBUG: [get_output_if] connect");
#ifndef WIN32
    close(sock_rt);
#else
    closesocket(sock_rt);
#endif
    return -1;
  }

  len = sizeof(iface_out);
  if (getsockname(sock_rt, (struct sockaddr *)&iface_out, &len) == -1 ) {
    if (opt_debug)
      perror("DEBUG: [get_output_if] getsockname");
#ifndef WIN32
    close(sock_rt);
#else
    closesocket(sock_rt);
#endif
    return -1;
  }
#ifndef WIN32
    close(sock_rt);
#else
    closesocket(sock_rt);
#endif
  if (iface_out.sin_addr.s_addr == 0)
    return 1;
  memcpy(ifip, &iface_out, sizeof(struct sockaddr_in));
  return 0;
}
