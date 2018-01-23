#include <stdio.h>

#include "fw.h"


void test_isNumber(){
	char *b;
	char *a;
	char *fishsticks;
	a = "-123";
	b = "123";
	if(isNumber(a) == 1){
		printf("Test passed\n");
	}else{
		printf("-123 Failed\n");
	}
	if(isNumber(b) == 0){
		printf("Test passed\n");
	}else{
		printf("123 Failed\n");
	}
	if(isNumber(c) == 1){
		printf("Test passed\n");
	}else{
		printf("fishsticks Failed\n");
	}
}


int main(void)
{
   test_isNumber();

   return 0;
 }