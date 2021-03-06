#include <stdlib.h>
#include "part6.h"

struct point create_point(double thex, double they)
{
   struct point p;
   p.x = thex;
   p.y = they;
   return p;
}


struct rectangle create_rectangle(struct point p1, struct point p2){
	struct rectangle r;
	r.topLeft = p1;
	r.bottomRight = p2;
	return r;
}


int is_a_square(struct rectangle rect){
	int xDist, yDist;
	xDist = abs(rect.topLeft.x - rect.bottomRight.x);
	yDist = abs(rect.topLeft.y - rect.bottomRight.y);
	if(xDist == yDist)
		return 1;
	return 0;
}

