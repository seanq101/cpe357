#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "encode.h"

int main(int argc, char* argv[]){
	struct node **list;
	makeTable();
	printTable();


	list = create_node_list();
	qsort((void *)list,256,sizeof(struct node*),comparator);
	printf("Hi2");
	printNodes(list);
	return 0;
}

void makeTable(){
	char c;
	while((c = getchar()) != EOF){
		freqArr[(int)c] = freqArr[(int)c] + 1;
	}
}

void printTable(){
	int index;
	for(index = 0; index < 256; index++){
		if(freqArr[index] !=0){
			printf("%i\n", freqArr[index]);
		}
	}
}

struct node ** create_node_list(){
	int index;
	struct node **res = (struct node **)malloc(sizeof(struct node) * 256);
	for (index = 0; index < 256; index++){
		if(freqArr[index] !=0){
			res[index]->value = (char)index;
			res[index]->frequency = freqArr[index];
			res[index]->right = NULL;
			res[index]->left = NULL;
			printf("Hi1\n");
		}
	}
	return res;
}

int comparator(const void *p, const void *q) {
    struct node * l = (*(struct node **)p);
    struct node * r = (*(struct node **)q); 
    if(l == NULL && r == NULL){
    	return 0;
    }else if(l != NULL && r == NULL){
    	return -1;
    }else if(l == NULL && r != NULL){
    	return 1;
    }

    if(l->frequency - r->frequency == 0){
    	return ( l->value - r->value );
    }
    return ( l->frequency - r->frequency );
}

void printNodes(struct node ** list){
	int index = 0;
	for (index = 0; index < 256; index++){
		printf("Hi3\n");
		if(list[index] != NULL){
			printf("Frequency: %i\tValue:%c\n",list[index]->frequency, list[index]->value );
		}else{
			break;
		}
	}

}



