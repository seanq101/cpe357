#ifndef DECODEH
#define DECODEH

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


void readHeader(int fdin);
void readBody(int fdin,int fdout,struct node* currentNode,struct node * root);
void printFreqArr();

#endif