#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#include "fw.h"


int main(int argc, char *argv[]) {
	
	struct map_table *myMap;
	myMap = createBlankTable(100);
	if(checkArgs(argc, argv) == 1){
		return 0;
	}
	myMap = parseFileNames(argc, argv, myMap);
	printTable(myMap);
	printf("%d", strcmp(myMap->list[5]->value, myMap->list[65]->value));

	return 0;
}

int checkArgs(int argc, char *argv[]){
	if(argc < 2){
		printf("usage1: fw [-n num] [ file1 [ file 2 ...] ]\n");
		return 1;
	}
	if (strcmp(argv[1], "-n") == 0 && argc < 4){
		printf("usage2: fw [-n num] [ file1 [ file 2 ...] ]\n");
		return 1;
	}

	if(strcmp(argv[1], "-n") == 0 && isNumber(argv[2]) == 1 ) {
		printf("usage3: fw [-n num] [ file1 [ file 2 ...] ]\nNo negative number inputs\n");
		return 1;
	}

	if(strcmp(argv[1], "-n") == 0 && isNumber(argv[2]) == 0 ){
		freqOutput = atoi(argv[2]); 
	}else{
		freqOutput = 10;
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

struct map_table * parseFileNames(int argc, char *argv[],struct map_table *myMap){
	FILE *file;
	int index;
	
	for(index = 1; index < argc; index++){
		file = fopen(argv[index], "r");
		if(file != NULL){
			myMap = parseFile(file, myMap);
		}else{
			printf("Unable to open file: %s\n", argv[1]);
		}
	}
		printf("%s1\n", myMap->list[5]->value);

	return myMap;

}

struct map_table * createBlankTable(int size){
	struct map_table *myMap = (struct map_table *)malloc(sizeof(struct map_table));
	myMap->map_size = size;
	myMap->used_size = 0;
	myMap->list = (struct map_element **)malloc(sizeof(struct map_element*) * myMap->map_size);
	return myMap;
}

struct map_table * parseFile(FILE *f, struct map_table *t){

	char currentWord[100];
	char currentChar;
	int index;


	index = 0;
	while( currentChar != EOF ) {
		currentChar = fgetc(f);
		if(currentChar == ' ' || currentChar == '\t' || currentChar == '\n'){
			
			t = addToTable(t, currentWord);
			strcpy(currentWord, "");
			index = 0;

		}else{
			if(currentChar != EOF){
				currentWord[index] = currentChar;
				index++;
			}
		}
	}

	t = addToTable(t, currentWord);
	memset(currentWord, 0, sizeof(currentWord));

	printf("%s2\n", t->list[5]->value);

	return t;

}
/*
void resetString(char *str, int size){
	int index = 0;
	for(index = 0; index < size; index++){
		str[index] = '\0';
	}
}
*/

struct map_table * addToTable(struct map_table *t, char *currentWord){

	
	int key;
	struct map_element *ele;
	struct map_table *newMap;
	int quadratic = 1;
	printf("%s", currentWord);
	key = ht_hash(currentWord) % t->map_size;
	

	if(t->list[key] && strcmp(t->list[key]->value, currentWord) == 0){
		t->list[key]->frequency++;
	}else{
		
		while(t->list[key]) {
			
			key = key + quadratic * quadratic;
			key = key % t->map_size;
			quadratic++;
		}
		
		ele = (struct map_element *)malloc(sizeof(struct map_element*));
		ele->value = currentWord;
		ele->frequency = 1;
		t->list[key] = ele;
			

	}
	
	t->used_size = t->used_size + 1;

	if( ((double) t->used_size / t->map_size ) >= .75) {
		newMap = createBlankTable(t->map_size * 2);
		t = reassignNewMap(newMap, t);
	}
	return t;

}

struct map_table * reassignNewMap(struct map_table *blank, struct map_table *original){
	int index;
	blank = createBlankTable(original->map_size * 2);

	for (index = 0; index < original->map_size; index++){
		if(original->list[index]){
			blank = addToTable(blank, original->list[index]->value);
		}
		free(original->list[index]);
	}

	return blank;
}


/* Hash a string for a particular hash table. */
int ht_hash(char *key ) {

	unsigned long int hashval;
	int i = 0;

	/* Convert our string to an integer */
	while( hashval < ULONG_MAX && i < strlen( key ) ) {
		hashval = hashval << 8;
		hashval += key[ i ];
		i++;
	}

	return hashval;
}

void printTable(struct map_table *t){
	int index;
	char *currentWord;
	for (index = 0; index < t->map_size; index++){
		if(t->list[index]){
			currentWord = t->list[index]->value;
			printf("Element:\t%d\tValue:\t%s\tFrequency:%d\n", index, currentWord, t->list[index]->frequency);
		}
	}
}


