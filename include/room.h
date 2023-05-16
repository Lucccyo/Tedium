#ifndef ROOM_H
#define ROOM_H

#define ROOM_SIZE 30

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Room Room;
struct Room {
    char tiles[ROOM_SIZE][ROOM_SIZE];
    int x, y;
    char name[30];
    int empty;
    char north_name[30];
    char south_name[30];
    char east_name[30];
    char west_name[30];
    Room *north;
    Room *south;
    Room *east;
    Room *west;
};

Room* create_room(char *room_path);
void free_room(Room *room);

/* to_string */
void display_room(Room *room);

#endif
