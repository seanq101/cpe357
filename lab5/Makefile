CC = gcc
CFLAGS = -Wall -ansi -pedantic
MAIN = mypwd 
all : $(MAIN)



mypwd.o : mypwd.c mypwd.h
	$(CC) $(CFLAGS) -c -g mypwd.c

mypwd : mypwd.o
	$(CC) $(CFLAGS) -o mypwd mypwd.o



clean :
	rm *.o $(MAIN) core
