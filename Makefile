build: battleship.c
	gcc -Wall -o battleship battleship.c -lcurses
clean: battleship
	rm battleship
run: battleship
	./battleship
