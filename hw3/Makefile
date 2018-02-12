CC = gcc
CFLAGS = -Wall -ansi -pedantic
MAIN = decode encode
OBJS = encode.o 
OBJS2 = decode.o
all : $(MAIN) $(MAIN2)

$(MAIN) : $(OBJS) encode.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

decode.o : decode.c decode.h encode.c encode.h
	$(CC) $(CFLAGS) -c decode.c encode.c

encode.o : encode.c encode.h
	$(CC) $(CFLAGS) -c encode.c


clean :
	rm *.o $(MAIN) core
