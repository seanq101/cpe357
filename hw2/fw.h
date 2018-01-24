#ifndef FW_H
#define FW_H

int NUMBER;

struct map_element{
	int frequency;
	char *value;
};

struct map_table{
	int map_size;
	int used_size;
	struct map_element **list;
};

int checkArgs(int argc, char *argv[]);
int isNumber(char *input);
struct map_table * parseFileNames(int argc, char *argv[]);
struct map_table * createBlankTable(int size);
struct map_table * parseFile(FILE *f, struct map_table *t);
struct map_table * addToTable(struct map_table *t, char *currentWord);
struct map_table * reassignNewMap(struct map_table *blank, struct map_table *original);
unsigned long hash(unsigned char *str);
void printTable(struct map_table *t);

#endif
