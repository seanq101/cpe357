#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "fw.h"

/*
int main(int argc, char *argv[]) {

	return 0;
}
*/
int checkArgs(int argc, char *argv[]){
	if(argc < 2){
		printf("usage: fw [-n num] [ file1 [ file 2 ...] ]\n");
		return 1;
	}else if (strcmp(argv[1], "-n") && argc < 4){
		printf("usage: fw [-n num] [ file1 [ file 2 ...] ]\n");
		return 1;
	}else if(strcmp(argv[1], "-n") && isNumber(argv[2]) == 1 ) {
		printf("usage: fw [-n num] [ file1 [ file 2 ...] ]\n");
		return 1;
	}
	return 0;
}

int isNumber(char *input){
	/* Checks for a negative number */
	if(*input == '-'){
		return 1;
	}
	while(*input){
		if( !(isdigit(*input)) ){
			return 1;
		}
		input++;
	}
	return 0;
}