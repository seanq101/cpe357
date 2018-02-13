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

void initCodeArr();
struct node ** create_node_list();
int comparator(const void *p, const void *q);
struct node * form_tree(struct node ** list);
struct node * take_two_lowest(struct node **list);
void freeEverything(struct node* list);


void makeUnixTable(int fdin);
void unixWriteToFile(int fdout, char* argv1);
void write_code(char letter, int fdout);
void makeTable();
void recursiveHuffCode(struct node * node, int curCode[20],int depth);


#endif