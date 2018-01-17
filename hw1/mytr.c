#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mytr.h"

int main(int argc, char *argv[]) {

	FILE *fileInput;
	FILE *fileOutput;


	int index;
		int arr[256];
	char *set1;
	char *set2;
	
	if(argc != 5) {
		printf("mytr: improper number of arguments\nUsage: %s <filename> <word>\n", argv[0]);
		return 1;
	}

	printf("%s %s %s %s %s\n", argv[0], argv[1], argv[2],argv[3],argv[4]);

	fileInput = fopen(argv[3], "r");
		
	if(fileInput == NULL) {
		printf("Unable to open file: %s\n", argv[3]);
		return 1;	
	}

	for ( index = 0; index < 256; index++ ) {
      arr[ index ] = index; 
   }
	
	set1 = argv[1];

	set2 = argv[2];
	while (strlen(set1) > strlen (set2)){
		set2[strlen(set2)] = set2[strlen(set2) - 1];
	}

	for(index = 0; index <= strlen(set1); index++){
		arr[  set1[index]  ] =  set2[index] - '0' ;
	}



	fileOutput= fopen(argv[4], "w+");

   
	fprintf(fileOutput, "%s %s %s %s %s\n", argv[0], argv[1], argv[2],argv[3],argv[4]);
	for(index = 0; index < 256; index ++){
		fprintf(fileOutput, "%d, ", arr[index]);
	}
	

	return 0;
}
