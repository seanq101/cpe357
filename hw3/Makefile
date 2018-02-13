CC = gcc
CFLAGS = -Wall -ansi -pedantic
MAIN = decode encode
OBJS = decode.o encode.o
all : $(MAIN)

$(MAIN) : $(OBJS) decode.h encode.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

decode.o : decode.c decode.h
	$(CC) $(CFLAGS) -c decode.c encode.c

encode.c: encode.c encode.h
	$(CC) $(CFLAGS) -c encode.c


clean :
	rm *.o $(MAIN) core
