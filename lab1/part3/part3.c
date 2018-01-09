#include "part3.h"

double sum(int *arr, int length){
	int sum = 0;
	int index = 0;
	while (length != index){
		sum += arr[index];
		index++;
	}
	return sum;
}
