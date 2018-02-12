#ifndef DECODEH
#define DECODEH

void readHeader(int fdin);
void readBody(int fdin,int fdout,struct node* currentNode,struct node * root);
void printFreqArr();

#endif