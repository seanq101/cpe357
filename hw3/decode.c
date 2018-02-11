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

	readBody(infd, outfd, list[0], list[0]);	


	freeEverything(list[0]);
	free(list);
	return 0;
}


void readHeader(int fdin){
	char buf[SIZE];
	char c;
	int index;
	read(fdin, buf, 4);
	/* buf[0] is the number of unique characters in the file */
	printf("Header:\n");
	for (index = 0; index < buf[0]; index++){
		/* buf[0] is the char currently being read */
		read(fdin, buf, 1);
		c = (char)buf[0];
		/* buf[0] is now the frequency */
		read(fdin, buf, 4);
		freqArr[(int)c] = buf[0];
		printf("%i\n", freqArr[61]);
	}
	printf("Done\n");
}

void readBody(int fdin, int fdout, struct node * currentNode, struct node * root){
	char buf[1];
	if(currentNode->left == NULL && currentNode->right == NULL){
		buf[0] = currentNode->value;
		write(fdout, buf, 1);
		currentNode = root;
		readBody(fdin, fdout, currentNode, root);
	}else{
		read(fdin, buf, 1);
		if(buf[0] == '0'){
			readBody(fdin, fdout, currentNode->left, root);
		}else{
			readBody(fdin, fdout, currentNode->right, root);
		}
	}
}
