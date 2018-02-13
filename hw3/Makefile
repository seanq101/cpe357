CC = gcc
CFLAGS = -Wall -ansi -pedantic
MAIN = decode encode
all : $(MAIN)

encode : encode.o
     $(CC) $(FLAGS) -o hencode encode.o

decode : decode.o
     $(CC) $(FLAGS) -o hdecode decode.o

decode.o : decode.c decode.h
	$(CC) $(CFLAGS) -c decode.c encode.c

encode.c: encode.c encode.h
	$(CC) $(CFLAGS) -c encode.c


clean :
	rm *.o $(MAIN) core
