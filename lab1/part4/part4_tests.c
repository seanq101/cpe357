#include <stdio.h>

#include "part4.h"

char mystr [6] = "HeLlO";

void test_strlower_1(){
	char buff[6] = "     ";
	int idx = 0;
	int temp;
	strlower(mystr, buff);
	
	while (buff[idx]){
		printf("Hello\n");
		temp = buff[idx];
		if (temp <= 96 || temp >= 122){
			printf("Test 1 failed\n");		
		}
	}
	printf("Test 1 passed\n");
	
}


void test_strlower()
{
   test_strlower_1();
   
   
}

int main(void)
{
   test_strlower_1();

   return 0;
 }