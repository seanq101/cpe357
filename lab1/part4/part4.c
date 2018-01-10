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