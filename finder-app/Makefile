CC=$(CROSS_COMPILE)gcc
CFLAGS=-Wall -Wextra -O2

all: writer

writer: writer.o
	$(CC) $(CFLAGS) -o writer writer.o

writer.o: writer.c
	$(CC) $(CFLAGS) -c writer.c -o writer.o

clean:
	rm -f writer *.o
