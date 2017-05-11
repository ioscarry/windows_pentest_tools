/*
 *  Unix uses a SIGALRM to send packets out depending on delay.
 *  Windows has no SIGALRM signal, so create another thread that will be a
 *  timer, and send packet when timer expires.
 *
 *
 *  Created: 8/22/2004
 */

#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>


#define TIMER_RESOLUTION 5      // 5-millisecond target resolution

UINT      wTimerRes = 0;        // timer resolturion
UINT      wTimerID = 0;         // timer ID

/*
 * Initialize time period once, then each call to create timer can use this
 * value.
 */
void initPeriod(void)
{
  TIMECAPS  timecaps;     // needed by timeGetDevCaps

  // get max & min of sys timer
  if ( timeGetDevCaps( &timecaps, sizeof( TIMECAPS ) ) != TIMERR_NOERROR ) {
    printf("timeGetDevCaps failed: %d\n", GetLastError());
    exit(1);
  }

  // get optimal resolution
  wTimerRes = max( timecaps.wPeriodMin, TIMER_RESOLUTION );

  // set minimal res for our timer
  if ( timeBeginPeriod( wTimerRes ) != TIMERR_NOERROR ) {
    fprintf(stderr, "timeBeginPeriod failed: %d\n", GetLastError());
    exit(1);
  }
}

/*
 *   Windows version of setting a timer signal
 *   Used for both send_packet and print_statistics (callback functions)
 *   Callback executed when timer has expired
 */
void setTimer(void CALLBACK(*func)(UINT, UINT, ULONG, ULONG, ULONG),
              UINT time_delay, UINT event)
{
  // Now, run the timer
  wTimerID = timeSetEvent(time_delay,       // delay in miliseconds
			                    wTimerRes,        // resolution
			                    func,             // callback function
			                    0,                // user data
			                    event );          // timer event

  if ( wTimerID == 0 ) {
    fprintf(stderr, "timeSetEvent failed: %d\n", GetLastError());
    exit(1);
  }
}

/*
 *  End the timer resolution
 */
void killPeriod(void)
{
  // kill the timer
  // timeKillEvent( wTimerID );

  // return previous settings
  timeEndPeriod( wTimerRes );
}
