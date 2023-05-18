#ifndef FLOOR_H
#define FLOOR_H

#define FLOOR_SIZE 16

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "../include/room.h"

typedef struct Floor Floor;
struct Floor {
    int id;
    Room *rooms[FLOOR_SIZE];
    Floor *next;
    Floor *previous;
};

Floor* create_floor(char level_path[]);
void free_floor(Floor *floor);
void display_rooms_names(Floor* floor);
void display_floor(Floor *floor);

#endif
