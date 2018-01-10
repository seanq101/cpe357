#include <ctype.h>
#include "part4.h"

void strlower(char input[], char buffer[]){
	int index = 0;

	while (input[index]){
		buffer[index] = tolower(input[index]);
		index++;
	}
	buffer[index] = '\0';
}

void str_lowermutate(char input[]){
	int index = 0;

	while (input[index]){
		input[index] = tolower(input[index]);
		index++;
	}
	input[index] = '\0';
}