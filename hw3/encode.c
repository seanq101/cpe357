#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "encode.h"

int main(int argc, char* argv[]){
	struct node **list;
	makeTable();
	
	list = create_node_list();
	qsort((void *)list,256,sizeof(struct node*),comparator);
	form_tree(list);
/*
	recursiveHuffCode(list[0], buffer, 0);
	
	printTable();
*/
	printRecursive(list[0]);
	return 0;
}

/*
int main(int argc, char* argv[]){
	int infd, outfd;
	infd = open(argv[1], O_RONLY);
	if(intfd == -1){
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	outfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 200);
	if(outfd == -1){
		perror(argv[2]);
		exit(EXIT_FAILURE);
	}
	unix_makeTable(infd, outfd);
}

void unix_makeTable(int fdin, int fdout){
	char buf[SIZE];
	int n;
	while( (n = read(fdin, buf, SIZE)) > 0 ){
		if( write(fdout, buf, n) == -1  ){
			perror();
			exit(EXIT_FAILURE);
		}
		if( n < 0 ){
			perror();
			exit(EXIT_FAILURE);
		}
	}
}
*/
void makeTable(){
	char c;
	while((c = getchar()) != EOF){
		freqArr[(int)c] = freqArr[(int)c] + 1;
	}
}

void printTable(){
	int index;
	for(index = 0; index < 256; index++){
		if(codeArr[index] != NULL){
			printf("%s\n", codeArr[index]);
		}
	}
}

struct node ** create_node_list(){
	int index;
	struct node **res = (struct node **)malloc(sizeof(struct node) * 256);
	for (index = 0; index < 256; index++){
		if(freqArr[index] !=0){
			res[index] = (struct node *)malloc(sizeof(struct node));
			res[index]->value = (char)index;
			res[index]->frequency = freqArr[index];
			res[index]->right = NULL;
			res[index]->left = NULL;
			res[index]->justAdded = 0;
			res[index]->code = (char *)malloc(sizeof(char) * 20);
			res[index]->codelen = 0;
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
    	if(l->justAdded == 1){
    		return -1;
    	}else if(r->justAdded == 1){
    		return 1;
    	}else{
    		return ( l->value - r->value );
    	}
    }
    return ( l->frequency - r->frequency );
}

void printNodes(struct node ** list){
	int index = 0;
	for (index = 0; index < 256; index++){
		if(list[index] != NULL){
			printf("Value:%c\tFreq:%i\tCode:%s\n", current->value, current->frequency, current->code);
		}else{
			break;
		}
	}

}

/*Forms a Huffman tree with a given list of pointers to nodes sorted in ascending order*/
struct node * form_tree(struct node ** list){
	struct node * temp;
	temp = (struct node *)malloc(sizeof(struct node));
	if(list[1] == NULL){
		return list[0];
	}
	else{
		while(list[1] != NULL){
			temp = take_two_lowest(list);
			list[0] = temp;
			list[1] = NULL;
			qsort((void *)list,256,sizeof(struct node*),comparator);
			temp->justAdded = 0;
			printNodes(list);
			printf("Hello\n");
		}
	}
	return list[0];
}
/*
list --> Node
#Finds the first two leaves/nodes in the tree and returns a node made out of both of them
*/
struct node * take_two_lowest(struct node **list){
	struct node  *res;
	res = (struct node *)malloc(sizeof(struct node));
	res->frequency = list[0]->frequency;
	res->left = list[0];
	list[0]->code[list[0]->codelen] = '0';
	list[0]->codelen += 1;
	list[0]->code[list[0]->codelen] = '\0';

	res->right = list[1];
	list[1]->code[list[1]->codelen] = '1';
	list[1]->codelen += 1;
	list[1]->code[list[1]->codelen] = '\0';

	res->frequency += list[1]->frequency;
	res->justAdded = 1;
	res->value = '\0';

	return res;
}
/*
void recursiveHuffCode(struct node * node, char *buffer, int depth){
	if(node != NULL){
		if(node->value != '\0'){
			buffer[depth] = '\0';
			codeArr[(int)(node->value)] = buffer;
		}else{
			buffer + depth = '0';
			recursiveHuffCode(node->left, buffer, depth + 1);
			buffer[depth] = '1';
			recursiveHuffCode(node->right, buffer, depth + 1);
		}
	}

}
*/

void printRecursive(struct node *current){
	if(current != NULL){
		printf("Value:%c\tFreq:%i\tCode:%s\n", current->value, current->frequency, current->code);
		printRecursive(current->right);
		printRecursive(current->left);
	}
	return;
	
}





