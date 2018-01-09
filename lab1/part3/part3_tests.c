#include <stdio.h>

#include "part3.h"

int arr [5] = {0,1,2,3,4};

void test_sum_1(){
	int res = sum(arr, 5);
	if (res == 10){
		printf("Test 1 passed\n");
	}
}