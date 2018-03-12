CC = gcc
CFLAGS = -Wall -std=gnu99 -pedantic
MAIN = forkit
OBJS = forkit.o
all : $(MAIN)

$(MAIN) : $(OBJS) 
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

forkit.o : forkit.c
	$(CC) $(CFLAGS) -c forkit.c

clean :
	rm *.o $(MAIN) core
