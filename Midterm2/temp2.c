




    int i,j;
    int pipes[2];
    int tempPID;
    char tempargv[MAX];
    for (i = 0; i < stageCount - 1; i ++){
        if(items[i].outputFD == -1){
            if(pipe(pipes) == -1){
                perror("pipe");
                exit(EXIT_FAILURE);
            }
            items[i].outputFD = pipes[1];
            items[i+1].inputFD = pipes[0];
        }
    }


    for(i = 0; i < stageCount; i++){
        if(tempPID = fork() < 0){
            perror("Fork");
        }
        if(tempPID == 0){ /* child */
            dup2(items[i].inputFD, STDIN_FILENO )
            dup2(items[i]. outputFD, STDOUT_FILENO)

            for (j = 0; j < item[i].argc; j++){
                tempargv[j] = item[i].argv[j];
            }
            tempargv[j] = NULL;

            execvp(tempargv[0], tempargv);
        }else{  /* parent */

            if(items[i].inputFD != STDIN_FILENO){
                close(items[i].inputFD);
            }if(items[i].outputFD != STDOUT_FILENO){
                close(items[i].outputFD);
            }
            
        }
    }
