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
	if( argc < 3){
		printf("tr: missing operand\nTry 'tr --help' for more information.\n");
		return 1;
	}else if(strcmp(argv[1],"-d") == 0 && argc > 3){
		printf("tr: extra operand '%s'\nOnly one string may be given when deleting without squeezing repeats.\nTry 'tr --help' for more information.\n", argv[3]);
		return 1;
	}else if (argc > 3){
		printf("tr: extra operand ‘%s’\nTry 'tr --help' for more information.\n", argv[3]);
		return 1;
	}else if(strcmp(argv[1],"-d") == 0){
		return -1;
	}
	return 0;
}



int main(int argc, char *argv[]) {
/*
Assuming its not delete, args are at 1 and 2
*/
	int result;
	result = checkArgs(argc, argv);
	if( result == 1 ){
		return 1;
	}

	initArr();

	if(result == -1){
		buildDelArr(argv[2]);
		translate(true);
	}else{
		buildArr(argv[1], argv[2]);
		translate(false);
	}

	return 0;
}

void buildDelArr(*setA){
	while(*setA){
		if(*setA == '\\' && *(setA + 1)){
			setA++;
			*setA = findEscaped(*setA);
		}

		arr[(int) *setA] = NULL;
		setA++;
	}
}

char findEscaped(char c){
	
	switch (c)
	{
		case 't':
			return '\t';
		case 'n':
			return '\n';
		case '\\':
			return '\\';
		default:
			return c;
	}
}

void initArr(){
	int index;
	for(index = 0; index < 256; index++){
		arr[index] = index;
	}
}

void buildArr(char *setA, char *setB){

	

	while(*setA){
		if(*setB == '\\' && *(setB + 1)){
			setB++;
			*setB = findEscaped(*setB);
		}

		if(*setA == '\\' && *(setA + 1)){
			setA++;
			*setA = findEscaped(*setA);
		}

		arr[(int) *setA] = *setB;
		setA++;

		if(*(setB + 1)){
			setB++;
		}
	}
}


void translate(bool del){
	char c;

	while((c = getchar()) != EOF){
		if(del == false){
			putchar(arr[(int) c]);
		}else if(arr[(int) c] == c){
			putchar(c);
		}
	}
}

