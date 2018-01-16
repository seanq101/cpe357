#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mytr.h"

int main(int argc, char *argv[]) {

	FILE *file;
	int index;


	if(argc != 5) {
		printf("mytr: improper number of arguments\nUsage: %s <filename> <word>\n", argv[0]);
		return 1;
	}


	file = fopen(argv[1], "r");
		
	if(file == NULL) {
		printf("Unable to open file: %s\n", argv[1]);
		return 1;	
	}

	for(index = 0; index <= 255, index++){
		printf("%d, ", index);
	}

	printf("%s %s %s %s %s\n", argv[0], argv[1], argv[2],argv[3],argv[4]);

	return 0;
}
