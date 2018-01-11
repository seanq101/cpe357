#include <stdio.h>

#include "checkit.h"
#include "part6.h"

/* define testing functions */
void test_create_point1(void)
{
   struct point p = create_point(1.9, -2.7);

   checkit_double(p.x, 1.9);
   checkit_double(p.y, -2.7);
}

void test_create_point2(void)
{
   struct point p = create_point(0.2, 12.1);

   checkit_double(p.x, 0.2);
   checkit_double(p.y, 12.1);
}

void test_is_a_square1(void){
   int res;
   struct point p1 = create_point(1,1);
   struct point p2 = create_point(2,0);
   struct rectangle r = create_rectangle(p1,p2);
   res = is_a_square(r);
   checkit_int(res,1);
}

void test_is_a_square1(void){
   int res;
   struct point p1 = create_point(0,0);
   struct point p2 = create_point(2,1);
   struct rectangle r = create_rectangle(p1,p2);
   res = is_a_square(r);
   checkit_int(res,0);
}

void test_create_point(void)
{
   test_create_point1();
   test_create_point2();
}

void test_create_rectangle(void){
   test_is_a_square1();
   test_is_a_square2();
}

int main(int arg, char *argv[])
{
   /* call testing function(s) here */
   test_create_point();
   test_create_rectangle();
   return 0;
}
