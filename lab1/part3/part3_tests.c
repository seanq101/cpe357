#include <stdio.h>

#include "part3.h"

int arr [5] = {0,1,2,3,4};

void test_sum_1(){
	int res = sum(arr, 5);
	if (res == 10){
		printf("Test 1 passed\n");
	}
	else{
		printf("Test 1 failed\n");
	}
}

void test_sum_2(){
	int res = sum(arr, 0);
	if (res == 0){
		printf("Test 2 passed\n");
	}
	else{
		printf("Test 2 failed\n");
	}
}

void test_sum_3(){
	int res = sum(arr, 4);
	if (res == 6){
		printf("Test 3 passed\n");
	}
	else{
		printf("Test 3 failed\n");
	}
}

void test_sum()
{
   test_sum_1();
   test_sum_2();
   test_sum_3();
   
}

int main(void)
{
   test_sum();

   return 0;
}