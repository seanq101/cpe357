#include <stdio.h>
#include <string.h>

#define one(x,y) (x + y) 
#define two(a) (x * x) 


int main(){
	
	int x=3;
	int y=4;

	printf("%d\n",one(2,3));
	printf("%d\n",one(2*3,3*2));
	printf("%d\n",two(two(2)));
	printf("%d\n",two(one(++x,0)));

	
	return 0;
}