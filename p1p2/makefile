CC = gcc
OBJS = main.o p1.o p2.o
qian: $(OBJS)
	$(CC) -o qian $(OBJS)

main.o: main.c p1.h p2.h
	$(CC) -c main.c

p1.o: p1.c p1.h p2.h
	$(CC) -c p1.c

p2.o: p2.c p1.h p2.h
	$(CC) -c p2.c

clean:	
	rm -f *.o
