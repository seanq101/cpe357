CC = gcc
CFLAGS = -Wall -ansi -pedantic
MAIN = uniq
OBJS = uniq.o
all : $(MAIN)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

uniq.o : uniq.c
	$(CC) $(CFLAGS) -c uniq.c

readline.o : readline.c
	$(CC) $(CFLAGS) -c readline.c

clean :
	rm *.o $(MAIN) core
