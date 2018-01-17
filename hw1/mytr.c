#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mytr.h"
/*
int main(int argc, char *argv[]) {

	
	FILE *fileOutput;


	int index;
		int arr[256];
	char *set1;
	char *set2;
	
	if(checkArgs(argc, argv) == 1){
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
		arr[  set1[index] - '0' + '0'] =  set2[index] - '0' + '0';
	}



	fileOutput= fopen(argv[4], "w+");

   printf("%c\n",argv[2][2] );
	for(index = 0; index < 256; index ++){
		printf(fileOutput, "%d, ", arr[index]);
	}
	

	return 0;
}

*/

int checkArgs(int argc, char *argv[]){
	FILE *fileInput;
	if(argc != 5) {
		printf("Usage: mytr [-d] set1 set2\n");
		return 1;
	}
	fileInput = fopen(argv[3], "r");
		
	if(fileInput == NULL) {
		printf("Unable to open file: %s\n", argv[3]);
		return 1;	
	}

	return 0;

}



char * checkEscaped(char *set){
	
	while (*set){
		if(*set == 92 && (*(set + 1) == 92 || *(set + 1) == 110 || *(set + 1) == 116)){
			*set = *(set + 1);
			set++;
			set++;
		}
	}
	return set;
		
	
}


