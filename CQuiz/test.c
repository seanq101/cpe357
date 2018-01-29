#include <stdio.h>
#include <string.h>

#define one(x) x + x 
#define two(a) printf("%d\n", a);

int main(){
	
	int x=6;
	int y=7;

	printf("%d\n",one(2));
	printf("%d\n",two(y++));
	printf("%d\n",one(2) + one(2));
	printf("%d\n",two(2 + 2));

	
	return 0;
}