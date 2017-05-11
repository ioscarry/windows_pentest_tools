#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

#ifndef WIN32
#include <sys/time.h>
#include <unistd.h>
#else
#include <io.h>
#endif

#include "hping2.h"
#include "globals.h"

void send_rawip(void)
{
	char *packet;

	packet = malloc(data_size);
	if (packet == NULL) {
		perror("[send_rawip] malloc()");
		return;
	}
	memset(packet, 0, data_size);
	data_handler(packet, data_size);
	send_ip_handler(packet, data_size);
	free(packet);
}
