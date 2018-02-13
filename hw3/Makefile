CC = gcc
CFLAGS = -Wall -ansi -pedantic
MAIN = decode encode
all : $(MAIN)

decode.o : decode.c decode.h
	$(CC) $(CFLAGS) -c decode.c

encode.c: encode.c encode.h
	$(CC) $(CFLAGS) -c encode.c

encode : encode.o
	$(CC) $(CFLAGS) -o hencode encode.o

decode : decode.o
	$(CC) $(CFLAGS) -o hdecode decode.o

clean :
	rm *.o $(MAIN) core
