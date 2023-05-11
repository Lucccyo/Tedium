#ifndef ROOM_H
#define ROOM_H

#define ROOM_SIZE 30

#include <stdio.h>
#include <string.h>

typedef struct Room {
    char tiles[ROOM_SIZE][ROOM_SIZE];
    int x, y;
    /* Will become pointer to other rooms */
    char north_name[30];
    char south_name[30];
    char east_name[30];
    char west_name[30];
} Room;

Room create_room(char *room_path);

/* to_string */
void display_room(Room room);

#endif