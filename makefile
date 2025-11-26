all: main

main:  helpers.o room.o ghost.o hunter.o main.o
	gcc main.o helpers.o room.o ghost.o hunter.o -o main

main.o: main.c
	gcc -Wall -Wextra -g -c main.c

helpers.o: helpers.c
	gcc -Wall -Wextra -g -c helpers.c

ghost.o: ghost.c
	gcc -Wall -Wextra -g -c ghost.c

room.o: room.c
	gcc -Wall -Wextra -g -c room.c

hunter.o: hunter.c
	gcc -Wall -Wextra -g -c hunter.c

clean:
	rm -f *.o *.csv main
