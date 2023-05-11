#ifndef FLOOR_H
#define FLOOR_H

#define FLOOR_SIZE 4

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "../include/room.h"

typedef struct Floor {
    int id;
    Room rooms[FLOOR_SIZE][FLOOR_SIZE];

    struct Floor *next;
    struct Floor *previous;
} Floor;

Floor create_floor(char level_path[15]);
void display_floor(Floor floor);

#endif