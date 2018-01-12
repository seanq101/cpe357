#include <stdio.h>
#include <string.h>

int main(int arg, char *argv[])
{
	char *token;
	token = strtok(argv, ' ');

	while (token != NULL){
		if(token[0] == '-')
			printf("%s\n", token);
	}
	return 0;
}