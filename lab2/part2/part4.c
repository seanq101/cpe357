#include <ctype.h>
#include "part4.h"

void strlower(char *input, char *buffer){

	while (*input){
		*buffer = tolower(*input);
		input++;
		buffer++;
	}
	*buffer = '\0';
}

void str_lowermutate(char *input){

	while (*input){
		*input = tolower(*input);
		input++;
	}
	*input = '\0';
}