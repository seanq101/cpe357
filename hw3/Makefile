CC = gcc
CFLAGS = -Wall -ansi -pedantic
MAIN = decode encode huffShare
all : $(MAIN)

decode.o : decode.c decode.h huffShare.h
	$(CC) $(CFLAGS) -c decode.c huffShare.c

encode.c: encode.c encode.h huffShare.h
	$(CC) $(CFLAGS) -c encode.c huffShare.c

huffShare.c: huffShare.c huffShare.h encode.h
	$(CC) $(CFLAGS) -c huffShare.c

encode : encode.o
	$(CC) $(CFLAGS) -o hencode encode.o huffShare.c

decode : decode.o
	$(CC) $(CFLAGS) -o hdecode decode.o huffShare.c



clean :
	rm *.o $(MAIN) core
