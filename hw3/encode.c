#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "encode.h"

int main(int argc, char* argv[]){
	struct node **list;
	makeTable();
	
	list = create_node_list();
	qsort((void *)list,256,sizeof(struct node*),comparator);
	printNodes(list);
}

void makeTable(){
	char c;
	while((c = getchar()) != EOF){
			freqArr[(int)c] = freqArr[(int)c] + 1;
	}
}

struct node ** create_node_list(){
	int index;
	struct node **res[256] = (struct node **)malloc(sizeof(struct node *) * 256);
	for (index = 0; index < 256; index++){
		if(freqArr[index] !=0){
			struct node * current = malloc(sizeof(struct node));
			current->value = (char)index;
			current->frequency = freqArr[index];
			current->right = NULL;
			current->left = NULL;
			res[index] = current;
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
    	return (strcmp( l->value, r->value ));
    }
    return ( l->frequency - r->frequency );
}

void printNodes(struct node ** list){
	int index = 0;
	for (index = 0; index < 256; index++){
		if(list[index] != NULL){
			printf("Frequency: %i\tValue:%c\n",list[index]->frequency, list[index]->value );
		}else{
			break;
		}
	}

}



