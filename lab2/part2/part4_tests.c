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
	printf("Test 1 passed, %s\n", mystr);
	
}

void test_strlower_2(){
	char mystr [6] = "hello";
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
	printf("Test 2 passed, %s\n", mystr);
	
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

void test_str_lowermutate_1(){
	char mystr [6] = "HeLlO";
	int idx = 0;
	int temp;
	str_lowermutate(mystr);
	
	while (mystr[idx]){
		temp = mystr[idx];
		if (temp <= 96 || temp >= 122){
			printf("Test 1 mutate failed\n");		
		}
		idx++;
	}
	printf("Test 1 mutate passed, %s\n", mystr);
	
}

void test_str_lowermutate_2(){
	char mystr [6] = "hello";
	int idx = 0;
	int temp;
	str_lowermutate(mystr);
	
	while (mystr[idx]){
		temp = mystr[idx];
		if (temp <= 96 || temp >= 122){
			printf("Test 2 mutate failed\n");		
		}
		idx++;
	}
	printf("Test 2 mutate passed, %s\n", mystr);
	
}

void test_str_lowermutate_3(){
	char mystr [6] = "";
	int idx = 0;
	int temp;
	str_lowermutate(mystr);
	
	while (mystr[idx]){
		temp = mystr[idx];
		if (temp <= 96 || temp >= 122){
			printf("Test 3 mutate failed\n");		
		}
		idx++;
	}
	printf("Test 3 mutate passed, %s\n", mystr);
	
}

void test_strlower()
{
   test_strlower_1();
   test_strlower_2();
   test_strlower_3();
   test_str_lowermutate_1();
   test_str_lowermutate_2();
   test_str_lowermutate_3();

}

int main(void)
{
   test_strlower();

   return 0;
 }