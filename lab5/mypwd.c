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
	char buf[PATH_MAX + 1];
	char *result, *temp;
	result = "";
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
		printf("Hi1,%i\n", i);
		while((ent = readdir(d)) != NULL){
			printf("Hi2, %i, %s\n", (int)ent->d_ino, ent->d_name);
			if(ent->d_ino == i){
				buf[0] = '/';
				temp = strcpy(temp, ent->d_name);
				strcat(buf, temp);
				result = strncat(buf, result, PATH_MAX);
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
