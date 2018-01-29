#include <stdio.h>
#include <string.h>

int main(){
	int A = 2; 
	char *cp = "abcdefg";
	int B = -1; 
	int grade[5] = { 4, 3, 2, 1, 0 };

	printf("%d, %d\n", (int)strlen(cp),(int) sizeof(grade));
}