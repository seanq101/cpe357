#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char * argv[]){
    pid_t pid;
    int wstatus;

    if(argc != 2){
        fprintf(stderr, "usage: tryit command\n");
        return 0;
    }


    pid = fork();
    if(  pid == 0 ){
        if(execl(argv[1], argv[1], NULL) < 0){
            exit(EXIT_FAILURE);
        }else{
            exit(0);
        }
        
    }else{
        wait(&wstatus);
        if( WIFEXITED(wstatus)){
            if(WEXITSTATUS(wstatus) != EXIT_SUCCESS){
                printf("Process %i exited with an error value.\n", pid);
               
            }else{
                printf("Process %i succeeded.\n", pid);

            }
        }

    }
    return 0;
}
