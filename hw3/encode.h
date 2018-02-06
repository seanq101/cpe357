#ifndef ENCODEH
#define ENCODEH

#define SIZE 256

struct node {
	int frequency;
	char value;
	struct node *left;
	struct node *right;
	int justAdded;
	char code[20];
	int codelen;
};

int freqArr [256];
int codeArr[256];

void makeTable();
struct node ** create_node_list();
int comparator(const void *p, const void *q);
void printNodes(struct node ** list);
void printTable();
struct node * form_tree(struct node ** list);
struct node * take_two_lowest(struct node **list);
void recursiveHuffCode(struct node * node, int code_table);
void printRecursive(struct node *current);

#endif