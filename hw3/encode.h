#ifndef ENCODEH
#define ENCODEH

#define SIZE 256

struct node {
	int frequency;
	char value;
	struct node *left;
	struct node *right;
	int justAdded;
	char code;
	struct node * parent;
};

struct code{
	char *code;
	char letter;
};

struct code *codesList;

int freqArr [SIZE];
int lenCodesList;
char* codeArr[SIZE];

void makeTable();
struct node ** create_node_list();
int comparator(const void *p, const void *q);
void printNodes(struct node ** list);
void printCodesList();
struct node * form_tree(struct node ** list);
struct node * take_two_lowest(struct node **list);
void recursiveHuffCode(struct node * node, char *buffer, int depth);

#endif