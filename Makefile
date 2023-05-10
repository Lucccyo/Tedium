# main.o: src/main.c
# 	gcc -o src/main.o -c src/main.c -W

CC=gcc
CFLAGS= -W -Wall -Werror
INC=-I include/
SRC=src/
EXEC=main
	
main: $(SRC)main
		$(CC) $(SRC)main.c 
		./a.out

debug: $(SRC)main
		$(CC) $(SRC)main.c $(CFLAGS) 
		./a.out
