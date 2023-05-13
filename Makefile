CC=gcc
CFLAGS= -W -Wall -Werror
SRC=src/main.c src/room.c src/floor.c 
EXEC=main
	
main:
	$(CC) $(SRC)
	./a.out

debug:
	$(CC) $(CFLAGS) $(SRC) 
	./a.out