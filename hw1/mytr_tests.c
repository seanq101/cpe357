#include <stdio.h>

#include "mytr.h"


void test_checkEscaped_1(){
	char c;
	int result;
	c = 'a';
	result = checkEscaped(c);
	printf("%d\n", result);
}

void test_escaped()
{
   test_checkEscaped_1();
   

}

int main(void)
{
   test_escaped();

   return 0;
 }