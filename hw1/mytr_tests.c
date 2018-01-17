#include <stdio.h>

#include "mytr.h"


void test_escaped_1(){
	char * set1;
	char * set2;
	set1 = 'hello\0';
	set2 = checkEscaped(set1);
	printf("%s\n", set2);
}

void test_escaped()
{
   test_escaped_1();
   

}

int main(void)
{
   test_escaped();

   return 0;
 }