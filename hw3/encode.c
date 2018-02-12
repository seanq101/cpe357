#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "encode.h"

int uniqueCount;
char byte;
int n_bits;
int singlechar;

int main(int argc, char* argv[]){
	int buff[20];
	struct node **list;
	
	int infd, outfd;
	singlechar = 0;
	
	infd = open(argv[1], O_RDONLY);
	if(infd == -1){
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	uniqueCount = 0;
	n_bits = 0;
	initCodeArr();

	makeUnixTable(infd);
	
	list = create_node_list();
	qsort((void *)list,256,sizeof(struct node*),comparator);
	form_tree(list);

	recursiveHuffCode(list[0], buff, 0);
	
	printCodesList();


	outfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 200);
	if(outfd == -1){
		perror(argv[2]);
		exit(EXIT_FAILURE);
	}
	unixWriteToFile(outfd, argv[1]);

	freeEverything(list[0]);
	free(list);
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

void unixWriteToFile(int fdout, char* argv1){
	int index;
	int buf[5];
	char readingbuffer[SIZE];
	int n, infd;
	/*Write how many chars are present*/
	buf[0] = uniqueCount;
	write(fdout, buf, 4);

	/* Fish header by writing each char and its frequency */
	for(index = 0; index < 256; index++){
		if(freqArr[index]!= 0){
			buf[0] = index;
			write(fdout, buf, 1);
			
			buf[0] = freqArr[index];
			write(fdout, buf, 4);

		}
	}

	infd = open(argv1, O_RDONLY);
	if(infd == -1){
		perror(argv1);
		exit(EXIT_FAILURE);
	}
	lseek(infd,0, SEEK_SET); 
	/* Write the body */
	while( (n = read(infd, readingbuffer, SIZE)) > 0 ){
		printf("%s\n", readingbuffer);
		for(index = 0; index < n; index++){
			write_code(readingbuffer[index], fdout);/* Try passing buf[index] which is a char */
		}
	}
	/* Once the file is done, you must write whatever was left in byte  */
	readingbuffer[0] = byte;
	if(byte != 0 && singlechar != 1){
		write(fdout, readingbuffer, 1);
	}
}

void write_code(char letter, int fdout){
	
	int bit, depth;
	char outputBuf[1];
	static int count = 0;
	depth = 0;
	bit = codeArr[(int)letter][depth];
	printf("%c\n", letter);
    while ( bit != -1 && bit != -2){

         if (bit == 1) {
            byte += 1;
            printf("Hi1\n");
         }
         if (n_bits == 7){
         	printf("Hi2\n");
         	outputBuf[0] = byte;
            write(fdout, outputBuf, 1); 
           	byte = 0;
            n_bits = 0;

        }else{
            n_bits += 1;
            byte = byte << 1;
            printf("Hi3\n");
        }
        depth++;
        bit = codeArr[(int)letter][depth];
    }
   	if(bit == -2){
   		 singlechar = 1;
   	}
    printf("%i\n", count);
    count++;
}


void makeUnixTable(int fdin){
	char buf[SIZE];
	int n;
	int index;
	while( (n = read(fdin, buf, SIZE)) > 0 ){
		for(index = 0; index < n; index++){
			if(freqArr[(int)buf[index]]  == 0){
				uniqueCount++;
			}
			freqArr[(int)buf[index]] = freqArr[(int)buf[index]] + 1;
		}
	}
	printf("%i\n", uniqueCount);
}


void initCodeArr(){
	int index;
	for (index = 0; index < 256; index++){
		codeArr[index][0] = -1;
	}
}

void printCodesList(){
	int index;
	int i;
	for(index = 0; index < SIZE; index++){
		if(codeArr[index][0] != -1){
			if(codeArr[index][0] != -2){
				printf("0x%x: ", (int)index);
				for(i = 0; codeArr[index][i] != -1; i++){
					printf("%i", codeArr[index][i]);
				}
				printf("\n");
			}else{
				printf("0x%x: \n", (int)index);
			}
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
			printf("Value:%c\tFreq:%i\t\n", list[index]->value, list[index]->frequency);
		}else{
			break;
		}
	}

}

/*Forms a Huffman tree with a given list of pointers to nodes sorted in ascending order*/
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
#Finds the first two leaves/nodes in the tree and returns a node made out of both of them
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



void recursiveHuffCode(struct node * node, int curCode[20],int depth){
	int index;
	if(node != NULL){
		if(node->value != '\0'){
			index = 0;
			if(depth != 0){
				while(index < depth){
					codeArr[(int)node->value][index] = curCode[index];
					index++;
				}
					codeArr[(int)node->value][index] = -1;
				return;
			}else{
				codeArr[(int)node->value][index] = -2;
			}
		}else{
			curCode[depth] = 0;
			recursiveHuffCode(node->left, curCode, depth + 1);
			curCode[depth] = 1;
			recursiveHuffCode(node->right, curCode, depth + 1);
			
		}
	}
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


