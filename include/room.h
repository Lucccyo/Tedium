#ifndef ROOM_H
#define ROOM_H

#define ROOM_SIZE 30

#include <stdio.h>
#include <string.h>

typedef struct Room {
    char tiles[ROOM_SIZE][ROOM_SIZE];
    int x;
    int y;
    char *north;
    char *south;
    char *east;
    char *west;
} Room;

Room create_room();

#endif