#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "decode.h"

int mask;
char byte;
int n_bits;
int empty = 0;
int main(int argc, char* argv[]){
	char tempBuf[4];
	struct node **list;
	
	int infd, outfd;
	
	infd = open(argv[1], O_RDONLY, 400);
	if(infd == -1){
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	outfd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC|S_IRUSR|S_IWUSR, 777);
	if(outfd == -1){
		perror(argv[2]);
		exit(EXIT_FAILURE);
	}
	n_bits = 0;
	initCodeArr();

	readHeader(infd);
	if(empty == 0){
		list = create_node_list();
		qsort((void *)list,256,sizeof(struct node*),comparator);
		form_tree(list);
		mask = 256;
	
		readBody(infd, outfd, list[0], list[0]);




		freeEverything(list[0]);
		free(list);
	}else if(empty == 1){
		tempBuf[0] = '\0';
		tempBuf[1] = '\0';
		tempBuf[2] = '\0';
		tempBuf[3] = '\0';

		write(fdout, tempBuf, 4);
	}
	return 0;
}


void readHeader(int fdin){
	char buf[SIZE];
	char c;
	int index, totUnique;
	int temp1, temp2, temp3, temp4;
	read(fdin, buf, 4);
	/* buf[0] is the number of unique characters in the file */
	totUnique = buf[0];
	if(totUnique == 0){
		empty = 1;
	}
	for (index = 0; index < totUnique; index++){
		/* buf[0] is the char currently being read */
		
		/* buf[1] is now the frequency */
		read(fdin, buf, 5);
		c = (char)buf[0];
		if(buf[1] < 0)
			temp1 = 256 + buf[1];
		else
			temp1 = buf[1];
		if(buf[2] < 0)
			temp2 = 256 * (256 + buf[2]);
		else
			temp2 = 256 * buf[2];
		if(buf[3] < 0)
			temp3 = 256 * 256 * (256 + buf[3]);
		else
			temp3 = 256 * 256 * buf[3];
		if(buf[4] < 0)
			temp4 = 256 * 256 * 256 *(256 + buf[4]);
		else
			temp3 = 256 * 256 * 256 * buf[4];

		
		freqArr[(int)c] = temp1 + temp2 + temp3 + temp4;
	}
}


void readBody(int fdin,int fdout,struct node *currentNode,struct node *root){
	char temp;
	char buf[1];
	int res;
	if(currentNode->left == NULL && currentNode->right == NULL){
		buf[0] = currentNode->value;
		temp = buf[0];
		if(freqArr[(int)temp]>0&&root->left==NULL&&root->right==NULL){
			
			write(fdout, buf, 1);
			currentNode = root;
			
			freqArr[(int)temp] = freqArr[(int)temp] - 1;
			readBody(fdin, fdout, currentNode, root);
		}else if(root->left != NULL){
			buf[0] = currentNode->value;
			temp = buf[0];
			write(fdout, buf, 1);
			currentNode = root;
			readBody(fdin, fdout, currentNode, root);
		}
	}else{
		if(n_bits == 0){
			if(read(fdin, buf, 1) > 0){
				byte = buf[0];
				mask = 128;
				n_bits = 7;
			}else{
				return;
			}
		}else{
			mask = mask / 2;
			n_bits -= 1;
		}
		res = byte & mask;
		/* Right shift byte until its gone THEN read more */
		if(res == 0){
			readBody(fdin, fdout, currentNode->left, root);
		}else{
			readBody(fdin, fdout, currentNode->right, root);
		}
	}
}





void initCodeArr(){
	int index;
	for (index = 0; index < 256; index++){
		codeArr[index][0] = -1;
	}
}


struct node ** create_node_list(){
	int index;
	struct node **res =(struct node **)malloc(sizeof(struct node)*256);
	for (index = 0; index < 256; index++){
		if(freqArr[index] !=0){
			res[index] = (struct node *)malloc(sizeof(struct node));
			res[index]->value = (char)index;
			res[index]->frequency = freqArr[index];
			res[index]->right = NULL;
			res[index]->left = NULL;
			res[index]->justAdded = 0;
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


/*Forms a Huffman tree with a given list of 
pointers to nodes sorted in ascending order*/
struct node * form_tree(struct node ** list){
	struct node * temp;

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
		}
	}
	return list[0];
}


/*
list --> Node
#Finds the first two leaves/nodes in the tree and 
returns a node made out of both of them
*/
struct node * take_two_lowest(struct node **list){
	struct node  *res;
	res = (struct node *)malloc(sizeof(struct node));
	res->frequency = list[0]->frequency;

	res->left = list[0];

	res->right = list[1];

	res->frequency += list[1]->frequency;
	res->justAdded = 1;
	res->value = '\0';

	return res;
}

void freeEverything(struct node* list){
	if(list != NULL){
		if(list->value != '\0'){
			free(list);
		}else{
			freeEverything(list->left);
			freeEverything(list->right);
			free(list);
		}
	}
}

