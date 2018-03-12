CC = gcc
CFLAGS = -Wall -pedantic
MAIN = forkit
OBJS = forkit.c
all : $(MAIN)

$(MAIN) : forkit.c forkit.h
	$(CC) $(CFLAGS) -o $(MAIN) forkit.c

clean :
	rm *.o $(MAIN) core
