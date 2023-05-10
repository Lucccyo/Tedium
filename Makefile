CC=gcc
CFLAGS= -W -Wall -Werror
SRC=src/
EXEC=main
	
main:
	$(CC) $(SRC)main.c $(SRC)room.c -o a
		
debug:
	$(CC) $(CFLAGS) $(SRC)main.c $(SRC)room.c -o a
