#include <stdio.h>
#include <string.h>

int main(int arg, char *argv[])
{
	char *token;
	int idx;
	const char s[2] = " ";
	idx = 0;

	while (argv != NULL){
		if(argv[idx][0] == '-'){
			printf("%s\n",argv[idx]);
		}
	}

	/*
	token = strtok(argv, s);

	while (token != NULL){
		if(token[0] == '-')
			printf("%s\n", token);
	}
	return 0;
	*/
}