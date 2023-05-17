# Detect OS
ifeq ($(OS),Windows_NT)
	UNAME_S := Windows
else
	UNAME_S := $(shell uname -s)
endif

CC=gcc
CFLAGS= -W -Wall -Werror
INC=-I include/

# Define library path depending on OS
ifeq ($(UNAME_S),Linux)
	LIB=-L lib/linux/ -l SDL2-2.0
else ifeq ($(UNAME_S),Darwin)
	LIB=-L lib/mac/ -l SDL2-2.0.0
else ifeq ($(UNAME_S),Windows)
	LIB=-L lib/win/ -l SDL2-2.0.0
endif

SRC=src/main.c src/room.c src/floor.c src/monster.c src/player.c src/texture.c
EXEC=main

main:
	$(CC) $(SRC) $(LIB) $(INC)
	./a.out

debug:
	$(CC) $(CFLAGS) $(SRC) $(LIB) $(INC)
	./a.out