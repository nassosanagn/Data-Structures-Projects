CC=gcc
CFLAGS=-Wall

myprog: ch6_QArray.o ch6_Simulation.o TStoixeiouOuras.o Controller.o
	$(CC) $(CFLAGS) -o myprog ch6_QArray.o ch6_Simulation.o TStoixeiouOuras.o Controller.o

ch6_QArray.o: ch6_QArray.c
	$(CC) $(CFLAGS) -c ch6_QArray.c

ch6_Simulation.o: ch6_Simulation.c
	$(CC) $(CFLAGS) -c ch6_Simulation.c

TStoixeiouOuras.o: TStoixeiouOuras.c
	$(CC) $(CFLAGS) -c TStoixeiouOuras.c

Controller.o: Controller.c
	$(CC) $(CFLAGS) -c Controller.c

.PHONY: clean

clean:
	rm -f myprog ch6_QArray.o ch6_Simulation.o TStoixeiouOuras.o Controller.o
