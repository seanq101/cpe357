#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pwd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

int twice, count;
void signal_handler(int signum){
    if(count % 2 == 0){
        printf("Tock\n");
        count ++;
    }else {
        printf("Tick");
        fflush(stdout);
        count++;
    }
    if( count == (twice + 1) ){
        printf("Done\n");
    }
}

int main(int argc, char * argv[]){
    
    struct sigaction sa;
    struct itimerval timer;

    count = 1;
    twice = 2 * atoi(argv[1]);

    memset( &sa, 0, sizeof(sa) );
    sa.sa_handler = signal_handler;
    sigaction ( SIGALRM, &sa , NULL );

    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 500000;

    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 500000;

    setitimer(ITIMER_REAL, &timer, NULL);


}



void updateChkSum(headerField * head){

    int i;
    int sum = 0;
    memset(head->checksum,' ', 8);
    for (i = 0; i < 512; i++){
        sum += 0xFF & ((char*)head)[i];
    }
    snprintf(head->checksum, 8, "%07o", sum);
    head->checksum[7] = 0;

}



