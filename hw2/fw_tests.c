#include <stdio.h>

#include "fw.h"


void test_isNumber(){
	char *b;
	char *a;
	a = "-123";
	b = "123";
	if(!isNumber(a)){
		printf("Test passed\n");
	}else{
		printf("-123 Failed\n");
	}
	if(isNumber(b)){
		printf("Test passed\n");
	}else{
		printf("123 Failed\n");
	}
}


int main(void)
{
   test_isNumber();

   return 0;
 }