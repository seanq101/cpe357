#ifndef ENCODEH
#define ENCODEH

#define SIZE 256

struct node {
	int frequency;
	char value;
	struct node *left;
	struct node *right;
	int justAdded;
};

int freqArr [SIZE];

int codeArr[SIZE][20];

void makeUnixTable(int fdin);
void unixWriteToFile(int fdout, char* argv1);
void write_code(char letter, int fdout);
void makeTable();
void printCodesList();
void recursiveHuffCode(struct node * node, int curCode[20],int depth);


#endif