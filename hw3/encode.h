#ifndef ENCODEH
#define ENCODEH

struct node {
	int frequency;
	char value;
	struct node *left;
	struct node *right;
};

int freqArr [256];

void makeTable();
struct node ** create_node_list();
int comparator(const void *p, const void *q);
void printNodes(struct node ** list);
void printTable();

#endif