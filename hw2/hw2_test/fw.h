#ifndef FW_H
#define FW_H

int freqOutput;

struct map_element {
	struct map_element * next;
	char *key;
	int frequency;
};

struct map_table {
	struct map_element ** buckets;
	int map_size;
	int used_size;
};

int checkArgs(int argc, char *argv[]);
int isNumber(char *input);struct map_table * parseFileNames(int argc, char *argv[],struct map_table *myMap);
struct map_table * parseFile(FILE *f, struct map_table *t);
struct map_table * addToTable(struct map_table *t, char *currentWord);
struct map_table * createBlankTable(int size);
int ht_hash(char *key );
void printTable(struct map_table *t);
int comparator(const void *p, const void *q);
char *readWord(FILE *f, int buffSize);
void hashmap_free(struct map_table *original);

#endif
