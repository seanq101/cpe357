#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#include "fw.h"


int main(int argc, char *argv[]) {
	
	struct map_table *myMap;
	myMap = createBlankTable(1000);

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
/*
	char currentWord[100];
	char currentChar;
	int index;


	index = 0;
	while( currentChar != EOF ) {
		currentChar = fgetc(f);
		if(currentChar == ' ' || currentChar == '\t' || currentChar == '\n'){
			currentWord[index] = '\0';
			t = addToTable(t, currentWord);
			index = 0;

		}else{
			if(currentChar != EOF){
				currentWord[index] = currentChar;
				index++;
			}
		}
	}
	currentWord[index] = '\0';
	*/
	char *currentWord;
	currentWord = readWord(f, 40);
	while( strcmp(currentWord,".")){
		t = addToTable(t, currentWord);
		currentWord = readWord(f, 40);
	}
	return t;

}


struct map_table * addToTable(struct map_table *t, char *currentWord){
	map_element **currentElement, *item, *newItem;
	char *wordptr;
	int key;
	key = ht_hash(currentWord) % t->map_size;
	wordptr = malloc(sizeof(char) * (strlen(currentWord) + 1 ));
	strcpy(wordptr, currentWord);

	
	currentElement = &(t->buckets[key]);

	for (item = *currentElement; item != NULL; item = item->next) {
		if (strcmp(item->value, wordptr)) {/* key already exists */
			item->frequency++;
			return;
		}
		if(item->next == NULL){
			newItem = (struct map_element *)mallolc(sizeof(map_element));
			newItem->value = wordptr;
			newItem->frequency = 1;
			item->next = newItem;
			t->used_size ++;
		}
	}


	return t;

}

struct map_table * createBlankTable(int size){

	struct map_table *myMap = (struct map_table *)malloc(sizeof(struct map_table));

	myMap->map_size = size;
	myMap->used_size = 0;
	myMap->buckets = (struct map_element **)malloc(sizeof(struct map_element*) * myMap->map_size);
	return myMap;
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
	int index, i;
	int j;
	struct map_element **vector, *currentElement;
	vector = malloc(sizeof(struct map_element *) * t->used_size);
	
	j = 0;

	for (index = 0; index < t->map_size; index++){
		if(t->buckets[index]){
			for(currentElement = t->buckets[index], currentElement != NULL, currentElement = currentElement->next){
				printf("Value:\t%s\tFrequency:%d\n", currentElement->value, currentElement->frequency);
			}

		}
	}
	printf("%d,%d\n",t->map_size, t->used_size );
	
/*
	for (index = 0; index < t->map_size; index++){
				printf("hi1");

		if(t->list[index] != NULL){
			
            vector[j]->value = t->list[index]->value;
            printf("%s\n", vector[j]->value);
            vector[j]->frequency = t->list[index]->frequency;
            j++;   
        }
        	
	}

	

	
		while (vector != NULL){
			printf("Element:\t%d\tValue:\t%s\tFrequency:%d\n", index, vector->value, vector->frequency);
			vector++;
		}
	

	qsort((void *)vector,t->map_size,sizeof(struct map_element),comparator);
	for (index = 0; index < t->map_size; index++){
			printf("Element:\t%d\tValue:\t%s\tFrequency:%d\n", index, vector[index]->value, vector[index]->frequency);
		}
		hashmap_free(t);
	*/
}

int comparator(const void *p, const void *q) {
    int l = (*(struct map_element **)p)->frequency;
    int r = (*(struct map_element **)q)->frequency; 
    if(l - r == 0){
    	return strcmp(((struct map_element *)p)->value, ((struct map_element *)q)->value);
    }
    return (l - r);
}

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
			}
			else{
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
	if(c[i] == EOF){
		return ".";
	}
	c[i] = '\0';
	i = strlen(c);
	temp = realloc(c, sizeof(char) * (i+1));
	return temp;

}
void hashmap_free(struct map_table *hm)
{
	int i;
	map_element *item, *next;

	for (i = 0; i < hm->size; i++) {
		for (item = hm->buckets[i]; item != NULL;) {
			next = item->next;
			free(item);
			item = next;
		}
	}

	free(hm->buckets);
	free(hm);
}