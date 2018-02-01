#ifndef ENCODEH
#define ENCODEH

struct node {
	int frequency;
	char value;
	struct node *left;
	struct node *right;
};

int freqArr [256];

char readChar();

#endif