#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include "mypwd.h"

int main(int argc, char * argv[]){
	struct stat sb;
	struct dirent *ent;
	int i,count ;
	DIR * d;
	char buf[4096];
	char result[4096], temp[100];
	int done;

	count = 0;
	done = 0;
	while(done != 1){
		printf("Hi, %s\n", result);
		i = stat(".", &sb);
		if( i != 0){
			perror("Wrong\n");
			exit(EXIT_FAILURE);
		}
		
		i = sb.st_ino;
		chdir("..");
		d = opendir(".");
		stat(".", &sb);
		if(sb.st_ino == i){
			done = 1;
			break;
		}
		while((ent = readdir(d)) != NULL){
			
			if((int)ent->d_ino == i){
				buf[0] = '/';
				buf[1] = '\0';
				strcpy(temp, ent->d_name);
				temp[strlen(ent->d_name)] = '\0';
				strncat(buf, temp, strlen(temp));
				strncat(buf, result, PATH_MAX);
				strcpy(result, buf);
				break;
			}
		}
		count++;
	}
	

	return 0;
}

/*
stat on dot, get its i node from struct stat
	chdir .. then opendir ., find folder whose i node is same as 
	stop if name of directory
*/
