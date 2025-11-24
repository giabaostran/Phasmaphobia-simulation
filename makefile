all: main

main:  helpers.o room.o ghost.o log.o hunter.o main.o
	gcc main.o helpers.o room.o ghost.o log.o hunter.o -o main

main.o: main.c
	gcc -c main.c

helpers.o: helpers.c
	gcc -c helpers.c

ghost.o: ghost.c
	gcc -c ghost.c

room.o: room.c
	gcc -c room.c

hunter.o: hunter.c
	gcc -c hunter.c

log.o: log.c
	gcc -c log.c

clean:
	rm -f *.o *.csv main
