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
	char *buf;
	char result[4096], temp[100];
	count = 0;
	while(count < 4){
		printf("Hi, %s\n", result);
		i = stat(".", &sb);
		if( i != 0){
			perror("Wrong\n");
			exit(EXIT_FAILURE);
		}
		
		i = sb.st_ino;
		chdir("..");
		d = opendir(".");
		while((ent = readdir(d)) != NULL){
			
			if((int)ent->d_ino == i){
				printf("Hi1\n");
				buf = "/";
				strcpy(temp, ent->d_name);
				printf("Hi2\n");
				temp[strlen(ent->d_name)] = '\0';
				strcat(buf, temp);
				printf("Hi3\n");
				strncat(buf, result, PATH_MAX);
				strcpy(result, buf);
				printf("Hi4\n");
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
