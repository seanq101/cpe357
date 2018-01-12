#include <stdio.h>
#include <string.h>

int main(int arg, char *argv[])
{
	char *token;
	const char s[2] = " ";

	token = strtok(argv, s);

	while (token != NULL){
		if(token[0] == '-')
			printf("%s\n", token);
	}
	return 0;
}