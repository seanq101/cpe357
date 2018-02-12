#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "encode.c"
#include "encode.h"
#include "decode.h"
char mask;
int main(int argc, char* argv[]){
	struct node **list;
	
	int infd, outfd;
	singlechar = 0;
	
	infd = open(argv[1], O_RDONLY);
	if(infd == -1){
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	outfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 200);
	if(outfd == -1){
		perror(argv[2]);
		exit(EXIT_FAILURE);
	}
	uniqueCount = 0;
	n_bits = 0;
	initCodeArr();

	readHeader(infd);
	
	list = create_node_list();
	qsort((void *)list,256,sizeof(struct node*),comparator);
	form_tree(list);
	mask = (char)128;
	readBody(infd, outfd, list[0], list[0]);	


	freeEverything(list[0]);
	free(list);
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
	printf("Header:\n");
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
	printFreqArr();
	printf("Done\n");
}

void printFreqArr(){
	int index;
	for(index = 0; index < SIZE; index++){
		if(freqArr[index] != 0){
			printf("%c:%i:%i\n", (char)index, freqArr[index], index);
		}
	}
}

void readBody(int fdin, int fdout, struct node * currentNode, struct node * root){
	char temp;
	char buf[1];
	int res;
	if(currentNode->left == NULL && currentNode->right == NULL){
		buf[0] = currentNode->value;
		temp = buf[0];
		if(freqArr[(int)temp] > 0 && root->left == NULL && root->right == NULL){
			
			write(fdout, buf, 1);
			currentNode = root;
			printf("%c\n", temp);
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
			read(fdin, buf, 1);
			byte = buf[0];
			mask = (char)128;
			n_bits = 7;
		}else{
			mask = mask / 2;
			n_bits--;
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
