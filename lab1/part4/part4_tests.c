#include <stdio.h>

#include "part4.h"



void test_strlower_1(){
	char mystr [6] = "HeLlO";
	char buff[6] = "     ";
	int idx = 0;
	int temp;
	strlower(mystr, buff);
	
	while (buff[idx]){
		temp = buff[idx];
		if (temp <= 96 || temp >= 122){
			printf("Test 1 failed\n");		
		}
		idx++;
	}
	printf("Test 1 passed, %s\n", buff);
	
}

void test_strlower_2(){
	char mystr [6] = "HeLlO";
	char buff[6] = "     ";
	int idx = 0;
	int temp;
	strlower(mystr, buff);
	
	while (buff[idx]){
		temp = buff[idx];
		if (temp <= 96 || temp >= 122){
			printf("Test 2 failed\n");		
		}
		idx++;
	}
	printf("Test 2 passed, %s\n", buff);
	
}

void test_strlower_3(){
	char mystr [6] = "";
	char buff[6] = "     ";
	int idx = 0;
	int temp;
	strlower(mystr, buff);
	
	while (buff[idx]){
		temp = buff[idx];
		if (temp <= 96 || temp >= 122){
			printf("Test 3 failed\n");		
		}
		idx++;
	}
	printf("Test 3 passed\n");
	
}


void test_strlower()
{
   test_strlower_1();
   test_strlower_2();
   test_strlower_3();
   
   
}

int main(void)
{
   test_strlower_1();

   return 0;
 }