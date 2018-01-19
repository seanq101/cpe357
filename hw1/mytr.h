#ifndef MYTR_H
#define MYTR_H

typedef int bool;
#define true 1
#define false 0

char arr[256];

char findEscaped(char c);
void initArr();
void buildArr(char *setA, char *setB);
void translate(bool del);
void buildDelArr(char *setA);
int checkArgs(int argc, char *argv[]);

#endif
