CC = gcc
CFLAGS = -Wall -pedantic
MAIN = tryit
OBJS = tryit.c
all : $(MAIN)

$(MAIN) : tryit.c tryit.h
	$(CC) $(CFLAGS) -o $(MAIN) tryit.c

clean :
	rm *.o $(MAIN) core
