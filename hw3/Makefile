CC = gcc
CFLAGS = -Wall -ansi -pedantic
MAIN = encode
OBJS = encode.o
all : $(MAIN)

$(MAIN) : $(OBJS) encode.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

encode.o : encode.c encode.h
	$(CC) $(CFLAGS) -c encode.c

clean :
	rm *.o $(MAIN) core
