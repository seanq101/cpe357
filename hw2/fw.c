#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#include "fw.h"

	struct map_table *myMap;
int main(int argc, char *argv[]) {
	
	
	myMap = createBlankTable(100);

	if(checkArgs(argc, argv) == 1){
		return 0;
	}

	parseFileNames(argc, argv, myMap);
	
	printTable(myMap);
	
	return 0;
}

int checkArgs(int argc, char *argv[]){
	if(argc < 2){
		printf("usage: fw [-n num] [ file1 [ file 2 ...] ]\n");
		return 1;
	}
	if (strcmp(argv[1], "-n") == 0 && argc < 4){
		printf("usage: fw [-n num] [ file1 [ file 2 ...] ]\n");
		return 1;
	}

	if(strcmp(argv[1], "-n") == 0 && isNumber(argv[2]) == -1 ) {
		printf("//home/pn-cs357/demos/fw: It is not possible to count fewer than zero words\n");
		return 1;
	}

	if(strcmp(argv[1], "-n") == 0 && isNumber(argv[2]) == 1){
		printf("%s: not a well-formed number\nusage: fw [-n num] [ file1 [ file 2 ...] ]\nNo negative number inputs\n", argv[2]);
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
		return -1;
	}
	while(*input){
		if( !(isdigit(*input)) ){
			return 1;
		}
		input++;
	}
	return 0;
}

void parseFileNames(int argc, char *argv[],struct map_table *myMap){
	FILE *file;
	int index;
		
	for(index = 1; index < argc; index++){
		file = fopen(argv[index], "r");
		if(file != NULL){

			parseFile(file, myMap);
			fclose(file);
			
		}else{
			printf("Unable to open file: %s\n", argv[1]);
			fclose(file);
		}
	}
	

}


void parseFile(FILE *f, struct map_table *t){
	char *currentWord;
	currentWord = readWord(f, 40);

	while( currentWord != NULL ){
		addToTable(t, currentWord);
		currentWord = readWord(f, 40);

	}
	return;

}


int addToTable(struct map_table *t, char *currentWord){

	int key, index;
	key = getHash(currentWord) % t->map_size;
	index = 0;


	if(t->list[key] && strcmp(t->list[key]->value, currentWord) == 0){
		t->list[key]->frequency++;
		return key;
	}else{

		while(t->list[key + index] != NULL && strcmp(t->list[key + index]->value, currentWord) != 0) {
			index++;
			if(( key + index) >= t->map_size){
				key = 0;
				index = 0;
			}
		}
		if( t->list[key + index] ){
			t->list[key + index]->frequency++;
		}else{
			t->list[key + index] = (struct map_element *)malloc(sizeof(struct map_element));
			t->list[key + index]->value = currentWord;
			t->list[key + index]->frequency = 1;
		
			t->used_size = t->used_size + 1;

		}	

	}
	
	

	if( ((double) t->used_size / t->map_size ) >= .75) {
		reassignNewMap(t);
	}
	return (key + index);
}

struct map_table * createBlankTable(int size){

	struct map_table *myMap = (struct map_table *)malloc(sizeof(struct map_table));

	myMap->map_size = size;
	myMap->used_size = 0;
	myMap->list = (struct map_element **)malloc(sizeof(struct map_element) * myMap->map_size);
	return myMap;
}


void reassignNewMap(struct map_table *original) {
	int i, newSpot;
	struct map_table *newMap;
	newMap = createBlankTable(original->map_size * 2);

	
	for (i = 0; i < original->map_size; i++){
		if(original->list[i] != NULL){
			newSpot = addToTable(newMap, original->list[i]->value);
			newMap->list[newSpot]->frequency = original->list[i]->frequency;
			free(original->list[i]);
		}
	}
	free(original->list);
	original->list = newMap->list;
	original->map_size = newMap->map_size;
	original->used_size = newMap->used_size;
	free(newMap);
	
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

size_t stringLength( char* source)
{
	size_t length = 0;

    if(source == NULL) { return 0; }

    while(*source != '\0') {
        length++;
        source++;
    }
    return length;  
}

size_t getHash( char* source)
{
    size_t length, hash, i;
    length = stringLength(source);
    hash = 0;
    for(i = 0; i < length; i++) {
        char c = source[i];
        int a = c - '0';
        hash = (hash * 10) + a;     
    } 

    return hash;
}

void printTable(struct map_table *t){

	int index;
	
	sortMap(t);
	/*
	for (index = 0; index < t->used_size; index++){
			printf("\t%i\t%s\n", t->list[index]->frequency,t->list[index]->value);
	}
*/
	printf("The top %i words (out of %i) are:\n", freqOutput, t->used_size);
	for (index = 0; index < freqOutput; index++){
			printf("\t%i\t%s\n", t->list[index]->frequency,t->list[index]->value);
	}
	
	hashmap_free(t);
}

void sortMap(struct map_table *t){
	qsort((void *)t->list,t->map_size,sizeof(struct map_element*),comparator);
}


		

int comparator(const void *p, const void *q) {
    struct map_element * l = (*(struct map_element **)p);
    struct map_element * r = (*(struct map_element **)q); 
    if(l == NULL && r == NULL){
    	return 0;
    }else if(l != NULL && r == NULL){
    	return -1;
    }else if(l == NULL && r != NULL){
    	return 1;
    }

    if(l->frequency - r->frequency == 0){
    	return strcmp( ((struct map_element *)r)->value, ((struct map_element *)l)->value );
    }
    return ( r->frequency - l->frequency );
}

char *readWord(FILE *f, int buffSize){
	int size;
	char *c;
	char *temp;
	int i = 0;
	size = buffSize;

	c = malloc(sizeof(char) * size);
	while((c[i] = getc(f)) != EOF){
		if (isalpha(c[i]) == 0 && i != 0){
			break;
		}else if( isalpha(c[i]) == 0 && i == 0 ){
			continue;
		}else{
			c[i] = tolower(c[i]);	
			i++;
			if(i * sizeof(char) >= size){
				size += buffSize;
				c = realloc(c, size);
			}
		}
	}
	if(i == 0 && c[i] == EOF){
		return NULL;
	}
	c[i] = '\0';
	i = strlen(c);
	temp = realloc(c, sizeof(char) * (i+1));
	return temp;
}

void hashmap_free(struct map_table *original){
	int index;

	for (index = 0; index < original->map_size; index++){
		if(original->list[index]){
			free(original->list[index]->value);
			free(original->list[index]);
		}
	}

	free(original->list);
	free(original);
}

