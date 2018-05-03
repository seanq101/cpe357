#include <stdio.h>
#include <string.h>

#define a(x) (x) + (x)
#define b(c,d) (d)
int x = 2;
int y = 3;


int main(){
	
	int x=3;
	int y=4;

	printf("%d\n",a(1));
	printf("%d\n",b((y*y),y));
	printf("%d\n",((6) * a(2)));
	printf("%d\n",a(b(1,2)));

	


	return 0;
}