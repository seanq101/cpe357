#include <stdio.h>

#include "fw.h"


void test_isNumber(){
	char *b;
	char *a;
	char *c;
	a = "-123";
	b = "123";
	c = "fishsticks";
	if(isNumber(a) == 1){
		printf("Test passed\n");
	}else{
		printf("-123 Failed\n");
	}
	if(isNumber(b) == 0){
		printf("Test passed\n");
	}else{
		printf("123 Failed\n");
	}
	if(isNumber(c) == 1){
		printf("Test passed\n");
	}else{
		printf("fishsticks Failed\n");
	}
}
/*
void test_comparator(){
	struct map_element * e1;
	struct map_element * e2; 
	struct map_element * e3;
	e1 = (struct map_element *)malloc(sizeof(struct map_element));
	e1->value = "abc";
	e1->frequency = 2;
	e2 = (struct map_element *)malloc(sizeof(struct map_element));
	e2->value = "xyz";
	e2->frequency = 2;
	e3 = (struct map_element *)malloc(sizeof(struct map_element));
	e3->value = "abc";
	e3->frequency = 2;
	if(comparator(e1,e2) < 0){
		printf("Test passed\n");
	}else{
		printf("Test e1 and e2 failed\n");
	}
	if(comparator(e1,e3) == 0){
		printf("Test passed\n");
	}else{
		printf("Test e1 and e3 failed\n");
	}
	if(comparator(e2,e3) > 0){
		printf("Test passed\n");
	}else{
		printf("Test e2 and e3 failed\n");
	}
}
*/
int main(void)
{
   test_isNumber();
   test_comparator();
   return 0;
 }