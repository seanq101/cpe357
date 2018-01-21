#include <stdio.h>

#include "mytr.h"


void test_checkEscaped_1(){
	char c,d;

	int result,res2;
	c = '"';
	d = '-'
	result = checkEscaped(c);
	res2 = checkEscaped(d);
	printf("%d, %d\n", result, res2);
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