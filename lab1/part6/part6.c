#include "part6.h"

struct point create_point(double x, double y)
{
   struct point p = {x, y};
   return p;
}


struct rectangle create_rectangle(struct point p1, struct point p2){
	struct rectangle r = {p1,p2};
	return r;
}


int is_a_square(struct rectangle rect){
	int xDist, yDist;
	xDist = rect.topLeft.x - rect.bottomRight.x;
	yDist = rect.topLeft.y - rect.bottomRight.y;
	if(xDist == yDist)
		return 1;
	return 0;
}

