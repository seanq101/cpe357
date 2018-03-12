#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char * argv[]){
    pid_t pid;

    printf("Hello World!\n");
    pid = fork();
    if(  pid == 0 ){
        pid = getpid();
        printf("This is the child, pid %i\n", pid);
        exit(EXIT_SUCCESS);
    }else{
        pid = getppid();
        printf("This is the parent, pid %i\n", pid);
        sleep(1);
    }
    printf("This is the parent, pid %i, signing off\n", pid);
    exit(EXIT_SUCCESS);

}
