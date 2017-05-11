/* 
 * $smu-mark$ 
 * $name: rtt.c$ 
 * $author: Salvatore Sanfilippo <antirez@invece.org>$ 
 * $copyright: Copyright (C) 1999 by Salvatore Sanfilippo$ 
 * $license: This software is under GPL version 2 of license$ 
 * $date: Fri Nov  5 11:55:49 MET 1999$ 
 * $rev: 3$ 
 */
 
/*
 * Revised for Windows: Rob Turpin <rgturpin@epop3.com> 
 *                      7/03/2004          
 */ 

#include <time.h>
#include <stdio.h>

#include "hping2.h"
#include "globals.h"

void minavgmax(float ms_delay)
{
	static int avg_counter = 0;

	if (rtt_min == 0 || ms_delay < rtt_min)
		rtt_min = ms_delay;
	if (rtt_max == 0 || ms_delay > rtt_max)
		rtt_max = ms_delay;
	avg_counter++;
	rtt_avg = (rtt_avg*(avg_counter-1)/avg_counter)+(ms_delay/avg_counter);
}

int rtt(int *seqp, int recvport, float *ms_delay)
{
    long sec_delay = 0;
#ifdef WIN32
    short msec_delay = 0;
#else
    usec_delay = 0;
#endif
  int i, tablepos = -1, status;
  

	if (*seqp != 0) {
		for (i = 0; i < TABLESIZE; i++)
			if (delaytable[i].seq == *seqp) {
				tablepos = i;
				break;
			}
	} else {
		for (i=0; i<TABLESIZE; i++)
			if (delaytable[i].src == recvport) {
				tablepos = i;
				break;
			}
			if (i != TABLESIZE)
				*seqp = delaytable[i].seq;
	}

	if (tablepos != -1)
	{
		status = delaytable[tablepos].status;
		delaytable[tablepos].status = S_RECV;

		sec_delay = time(NULL) - delaytable[tablepos].sec;
#ifndef WIN32
    usec_delay = get_usec() - delaytable[tablepos].usec;

    if (sec_delay == 0 && usec_delay < 0)
      usec_delay += 1000000;

    *ms_delay = (sec_delay * 1000) + ((float)usec_delay / 1000);
#else
    msec_delay = get_msec() - delaytable[tablepos].msec;

    if (sec_delay == 0 && msec_delay < 0)
      msec_delay += 1000;

    *ms_delay = (float)(sec_delay * 1000) + (float)msec_delay;
#endif
		minavgmax(*ms_delay);
	}
	else
	{
		*ms_delay = 0;	/* not in table.. */
		status = 0;	/* we don't know if it's DUP */
	}

	/* SANITY CHECK */
	if (*ms_delay < 0)
	{
		printf("\n\nSANITY CHECK in rtt.c FAILED!\n");
		printf("- seqnum = %d\n", *seqp);
		printf("- status = %d\n", status);
#ifndef WIN32
    printf("- get_usec() = %ld\n", (long int)get_usec());
    printf("- delaytable.usec = %ld\n", (long int)delaytable[tablepos].usec);
    printf("- usec_delay = %ld\n", usec_delay);
#else
    printf("- get_msec() = %i\n", get_msec());
    printf("- delaytable.msec = %i\n", delaytable[tablepos].msec);
    printf("- msec_delay = %i\n", msec_delay);
#endif
		printf("- time(NULL) = %ld\n", (long int)time(NULL));
		printf("- delaytable.sec = %ld\n", (long int)delaytable[tablepos].sec);
		printf("- sec_delay = %ld\n", sec_delay);
		printf("- ms_delay = %f\n", *ms_delay);
		printf("END SANITY CHECK REPORT\n\n");
	}

	return status;
}

#ifndef WIN32
void delaytable_add(int seq, int src, time_t sec, time_t usec, int status)
#else
void delaytable_add(int seq, int src, time_t sec, short msec, int status)
#endif
{
  delaytable[delaytable_index % TABLESIZE].seq = seq;
  delaytable[delaytable_index % TABLESIZE].src = src;
  delaytable[delaytable_index % TABLESIZE].sec = sec;
#ifndef WIN32
  delaytable[delaytable_index % TABLESIZE].usec = usec;
#else
  delaytable[delaytable_index % TABLESIZE].msec = msec;
#endif
  delaytable[delaytable_index % TABLESIZE].status = status;
  delaytable_index++;
}

