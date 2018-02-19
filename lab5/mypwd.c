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
	int i = stat(".", &sb);
	if( i != 0){
		perror("Wrong\n");
		exit(EXIT_FAILURE);
	}
	
	listDir(".");

	return 0;
}

void listDir(char *path){
	char buf[PATH_MAX + 1];
	DIR * d;
	struct dirent *ent1, *ent2;
	printf("%s\n", path);
	if((d = opendir(path)) == NULL){
		perror("Bad path\n");
		exit(EXIT_FAILURE);
	}

	ent1 = readdir(d);
	ent2 = readdir(d);
	if(ent1->d_ino != ent2->d_ino){
		while(ent2 = readdir(d) != NULL){
			if(ent2->d_ino == ent1->d_ino){
				strcpy(buf, ent2->d_name);
				buf[PATH_MAX + 1] = '\0';
				strncat(buf, path, PATH_MAX);
				break;
			}
		}
		listDir(buf);
	}else{
		printf("%s\n", path);
	}

	
}
