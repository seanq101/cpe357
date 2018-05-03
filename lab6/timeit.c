#include <sys/time.h> 
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
/*

You have to create a function that will handle the "alarm" and then set a signal handler for sigalrm
Then call setitimer ITIMER_REAL with the interval and delay as 500 ms
(convert it to microseconds)
Then have a global.variable called count to keep track of the ticks. Make it TWICE as big as what you type in.
Every OTHER time print tock

*/
int doubleInput;
int count;
void timer_handler (int signal)
{
	if(count % 2 == 0){
		printf("Tock\n");
		count++;
	}
	else{
		printf("Tick...");
		fflush(stdout);
		count++;
	}
	if(count > doubleInput){
		printf("Time's up!\n");
	}
}

int main (int argc, char *argv[])
{

	struct sigaction sa;
	struct itimerval timer;
	count = 1;
	doubleInput = 2 * (atoi(argv[1]));

 /* Install timer_handler as the signal handler for SIGALRM. */
 memset (&sa, 0, sizeof (sa));
 sa.sa_handler = timer_handler;
 sigaction (SIGALRM, &sa, NULL);

 /* Configure the timer to expire after 500 msec... */
 timer.it_value.tv_sec = 0;
 timer.it_value.tv_usec = 500000;
 /* ... and every 500 msec after that. */
 timer.it_interval.tv_sec = 0;
 timer.it_interval.tv_usec = 500000;
 /* Start a real timer. It counts down whenever this process is
   executing. */
 setitimer (ITIMER_REAL, &timer, NULL);
 while(count <= doubleInput);
 return 0;

}
