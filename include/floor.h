#ifndef FLOOR_H
#define FLOOR_H

/* Floor can't excess this size */
#define FLOOR_SIZE 16

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "room.h"

typedef struct Floor Floor;
struct Floor {
    int id;
    Room *rooms[FLOOR_SIZE];
    /* Pointers to others floors */
    Floor *next;
    Floor *previous;
};

/* return a floor pointer and fill it with all the rooms from the path provided */
Floor* create_floor(char level_path[], Hashtbl *monsters);

/* free the floor and all the rooms in it */
void free_floor(Floor *floor);

/* print floor id and a list of all the rooms in it */
void display_floor(Floor* floor);

#endif
