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
	LIB=-L lib/mac/ -l SDL2
else ifeq ($(UNAME_S),Windows)
	LIB=-L lib/win/ -l SDL2-2.0.0
endif

SRC=src/main.c src/room.c src/floor.c src/monster.c src/player.c src/texture.c src/monster_hashtbl.c src/renderer.c src/maze.c src/animator.c
EXEC=main

main:
	$(CC) $(SRC) $(LIB) $(INC)
	./a.out

debug:
	$(CC) $(CFLAGS) $(SRC) $(LIB) $(INC)
	./a.out

test-floor:
	$(CC) -W -Wall tests/test_floor.c src/floor.c src/room.c src/monster_hashtbl.c
	./a.out

test-hashtbl:
	$(CC) -W -Wall tests/test_hashtbl.c src/monster_hashtbl.c src/monster.c
	./a.out

test-maze:
	$(CC) -W -Wall tests/test_maze.c src/maze.c src/room.c src/floor.c src/monster_hashtbl.c src/player.c
	./a.out

test-player:
	$(CC) -W -Wall tests/test_player.c src/player.c
	./a.out