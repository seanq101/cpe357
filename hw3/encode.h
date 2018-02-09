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
void unixWriteToFile(int fdout, int fdin);
void write_code(int *code, int fdout);
void makeTable();
struct node ** create_node_list();
int comparator(const void *p, const void *q);
void printNodes(struct node ** list);
void printCodesList();
struct node * form_tree(struct node ** list);
struct node * take_two_lowest(struct node **list);
void recursiveHuffCode(struct node * node, int curCode[20],int depth);
void initCodeArr();
void freeEverything(struct node* list);

#endif