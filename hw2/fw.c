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
			fclose(file);
			
		}else{
			printf("Unable to open file: %s\n", argv[1]);
			fclose(file);
		}
	}
	return myMap;
	

}


struct map_table * parseFile(FILE *f, struct map_table *t){
	char *currentWord;
	currentWord = readWord(f, 40);

	while( currentWord != NULL ){
		t = addToTable(t, currentWord);
		currentWord = readWord(f, 40);

	}
	return t;

}


struct map_table *addToTable(struct map_table *t, char *currentWord){

	
	int key, index;
	key = getHash(currentWord) % t->map_size;
	index = 0;


	if(t->list[key] && strcmp(t->list[key]->value, currentWord) == 0){
		t->list[key]->frequency++;
		return t;
	}else{

		while(t->list[key + index] != NULL && strcmp(t->list[key + index]->value, currentWord) != 0) {
			index++;
			if(( key + index) >= t->map_size){
				key = 0;
				index = 0;
			}
		}
		if( t->list[key + index] && strcmp(t->list[key + index]->value, currentWord) == 0 ){
			t->list[key + index]->frequency++;
			return t;
		}else{
			t->list[key + index] = (struct map_element *)malloc(sizeof(struct map_element));
			t->list[key + index]->value = currentWord;
			t->list[key + index]->frequency = 1;
		
			t->used_size = t->used_size + 1;
		}	

	}
	
	

	if( ((double) t->used_size / t->map_size ) >= .90) {
		/*
		t->list = (struct map_element **)realloc(t->list, sizeof(struct map_element) * t->map_size * 2);
		t->map_size = t->map_size * 2;
		*/
		t = reassignNewMap(t);
	}
	return t;

}

struct map_table * createBlankTable(int size){

	struct map_table *myMap = (struct map_table *)malloc(sizeof(struct map_table));

	myMap->map_size = size;
	myMap->used_size = 0;
	myMap->list = (struct map_element **)malloc(sizeof(struct map_element) * myMap->map_size);
	return myMap;
}


struct map_table *reassignNewMap(struct map_table *original) {
	int i;
	struct map_table *newMap;
	newMap = createBlankTable(original->map_size * 2);
	
	for (i = 0; i < original->map_size; i++){
		if(original->list[i] != NULL){
			addToTable(newMap, original->list[i]->value);
			free(original->list[i]);
		}
	}
	free(original->list);
	original->list = newMap->list;
	original->map_size = 2 * original->map_size;
	free(newMap);
	return original;
}
	/*
	int index;
	struct map_table *tempMap;
	int key;
	int quadratic = 1;
	tempMap = createBlankTable(original->map_size * 2);
	
	for (index = 0; index < original->map_size; index++){

		printf("Hello, %d, %d\n", original->map_size, tempMap->map_size);
		if(original->list[index]){

			key = ht_hash(original->list[index]->value) % tempMap->map_size;

				while(tempMap->list[key] != NULL) {
			
					key = key + (quadratic * quadratic);
					key = key % tempMap->map_size;
					quadratic++;
				}

				tempMap->list[key] = (struct map_element *)malloc(sizeof(struct map_element));
				tempMap->list[key]->value = original->list[index]->value;
				tempMap->list[key]->frequency = original->list[index]->frequency;
			
			aroudn this guy    tempMap = addToTable(tempMap, original->list[index]->value);
			
			
			
		}
		free(original->list[index]);
	}
	free(original->list);
	original->list = tempMap->list;
	original->map_size = original->map_size * 2;
	free(tempMap);
	printTable(original);
}*/
/*
void reassignNewMap( struct map_table *original){
	struct map_element **currentEle, **newList;
	size_t s, size;
	int index, i, quadratic;

	quadratic = 1;

	currentEle = original->list;
	s = original->map_size;
	size = s << 1;

	newList = calloc(size, sizeof(struct map_element *));

	for (i = 0; i < s; i++){
		if(currentEle[i]){
			index = ht_hash(currentEle[i]->value);
			if(newList[index] == NULL)
				newList[index] = currentEle[i];
			else{
				while(newList[index] != NULL) {
					index = index + (quadratic * quadratic);
					index = index % size;
					quadratic++;
				}
				newList[index] = currentEle[i];
			}
		}
	}
	free(original->list);
	original->list = newList;
	original->map_size = size;



	int index;
	struct map_table *tempMap;
	struct map_element ** newList = original->list;
	original->list = (struct map_element **)realloc(original->list, sizeof(struct map_element) * original->map_size * 2);
	tempMap = createBlankTable(2 * original->map_size);
	tempMap->list = newList;

	for (index = 0; index < original->map_size; index++){
		if(original->list[index]){
			tempMap = addToTable(tempMap, original->list[index]->value);
		}
		
	}
	free(original->list);
	original->list = tempMap->list;
	free(tempMap);
	original->map_size = original->map_size * 2;

	return original;
	
}

*/
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
	printf("The top %i words (out of %i) are:\n", freqOutput, t->used_size);
	for (index = 0; index < freqOutput; index++){
			printf("\t%i\t%s\n", t->list[index]->frequency,t->list[index]->value);
	}

	hashmap_free(t);
}

void sortMap(struct map_table *t){
	qsort((void *)t->list,t->map_size,sizeof(struct map_element*),comparator);
}


	/*
	Basically I'm accessing somehting thats null and also my used_size isn't right because it only sometimes 
	recognizes it as a mathcing word
	*/

	/*
		while (vector != NULL){
			printf("Element:\t%d\tValue:\t%s\tFrequency:%d\n", index, vector->value, vector->frequency);
			vector++;
		}
	

	for (index = 0; index < t->map_size; index++){
			printf("Element:\t%d\tValue:\t%s\tFrequency:%d\n", index, vector[index]->value, vector[index]->frequency);
		}*/

		

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
/*
char *readWord(FILE *f, int buffSize){
	int size;
	char current;
	int index;
	char *word = malloc(sizeof(char) * buffSize);
	current = getc(f);
	size = buffSize;
	for(index = 0; isalpha(current) && (current != EOF); current = getc(f)){
		if(index >= size - 1){
			size += buffSize;
			word = realloc(word, size);
		}
		word[index] = tolower(current);
		index++;
	}
	if(index == 0){
		return NULL;
	}else{
		return word;
	}

}
*/


char *readWord(FILE *f, int buffSize){
	int size;
	char *c;
	char *temp;
	int i = 0;
	size = buffSize;

	c = malloc(sizeof(char) * size);
	while((c[i] = getc(f)) != EOF){
		if (isalpha(c[i]) == 0){
			if(c[i] == ' ' || c[i] == '\n' || c[i] == '\t'){
				break;
			}if(c[i] == '\''){
				c[i] = '\0';
				i = strlen(c);
				temp = realloc(c, sizeof(char) * (i+1));
				return temp;
			}else{
				continue;
			}
		}
		c[i] = tolower(c[i]);	
		i++;
		if(i * sizeof(char) >= size){
			size += buffSize;
			c = realloc(c, size);
		}
	}
	if(c == EOF){
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
