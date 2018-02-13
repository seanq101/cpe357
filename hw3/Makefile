CC = gcc
CFLAGS = -Wall -ansi -pedantic
MAIN = decode
OBJS = decode.o
all : $(MAIN)

$(MAIN) : $(OBJS) decode.h 
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

decode.o : decode.c decode.h
	$(CC) $(CFLAGS) -c decode.c



clean :
	rm *.o $(MAIN) core
