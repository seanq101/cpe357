#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mytr.h"


int main(int argc, char *argv[]) {

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



int checkArgs(int argc, char *argv[]){
	if( argc < 3 && strcmp(argv[1],"-d") != 0){
		printf("tr: missing operand after ‘abc’\nTwo strings must be given when translating.\nTry 'tr --help' for more information.\n");
		return 1;
	}else if( argc < 3 && strcmp(argv[1],"-d") == 0){
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




void buildDelArr(char *setA){
	while(*setA){
		if(*setA == '\\' && *(setA + 1)){
			setA++;
			*setA = findEscaped(*setA);
		}

		arr[(int) *setA] = '\0';
		setA++;
	}
}

int checkEscaped(char c){
	switch (c)
	{
		case 't':
			return 1;
		case 'n':
			return 1;
		case '\\':
			return 1;
		default:
			break;
	}
	if((int) c == 34 || (int) c == 45){
		return -1;
	}else{
		return 0;
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
		/* Checks for not \n, \t, \\ case in set so it can echo it*/
		if(*setA == '\\' && *(setA + 1) && (checkEscaped(*(setA + 1)) == 0) ) {
			setA++;
			arr[(int) *setA] = *setA;
			setA++;
		/* Checks for a \-, \" in setA, but not in setB */
		}else{
			if(*setA == '\\' && *(setA + 1) && (checkEscaped(*(setA + 1)) == -1) ){
				setA++;
			}
			
			/* Checks for a \-, \" in setB */
			if (*setB == '\\' && *(setB + 1) && (checkEscaped(*(setB + 1)) == -1) ){
				setB++;
			}
			/* Checks for not \n, \t, \\ in setB */
			if(*setB == '\\' && *(setB + 1) && (checkEscaped(*(setB + 1)) == 1) ){
				setB++;
				*setB = findEscaped(*setB);
			}
			/* Checks for not \n, \t, \\ in setB */
			if(*setA == '\\' && *(setA + 1) && (checkEscaped(*(setA + 1)) == 1) ){
				setA++;
				*setA = findEscaped(*setA);
			}
		
			arr[(int) *setA] = *setB;
			setA++;
		}

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

