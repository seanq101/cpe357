#include <stdio.h>

#include "mytr.h"


void test_checkEscaped_1(){
	char b [12];
	char a [5];
	int index;
	b = "\n\t\\\\\\-";
	a = "abcd";
	buildArr(a,b);
	for (index = 0; index< 256; index++){
		printf("%d, ", arr[index]);
	}

	
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