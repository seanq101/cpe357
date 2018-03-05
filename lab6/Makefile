CC = gcc
CFLAGS = -Wall -std=gnu99 -pedantic
MAIN = timeit
OBJS = timeit.o
all : $(MAIN)

$(MAIN) : $(OBJS) timeit.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

timeit.o : timeit.c timeit.h
	$(CC) $(CFLAGS) -c timeit.c

clean :
	rm *.o $(MAIN) core
