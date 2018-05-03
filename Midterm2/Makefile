CC = gcc
CFLAGS = -Wall -std=gnu99 -pedantic
MAIN = code
OBJS = code.o
all : $(MAIN)

$(MAIN) : $(OBJS) 
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

code.o : code.c
	$(CC) $(CFLAGS) -c code.c

clean :
	rm *.o $(MAIN) core
