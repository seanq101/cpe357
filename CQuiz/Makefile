CC = gcc
CFLAGS = -Wall -pedantic
MAIN = tester
OBJS = tester.o 
all : $(MAIN)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

tester.o : tester.c 
	$(CC) $(CFLAGS) -c tester.c

clean :
	rm *.o $(MAIN) core
