CC=gcc
CFLAGS=-Wall

myprog: main.o Session.o
	$(CC) $(CFLAGS) -o myprog main.o Session.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

Session.o: Session.c
	$(CC) $(CFLAGS) -c Session.c

.PHONY: clean

clean:
	rm -f myprog main.o Session.o
