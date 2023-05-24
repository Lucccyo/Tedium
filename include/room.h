#ifndef ROOM_H
#define ROOM_H

#define ROOM_SIZE 30

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* used to remove problematic non-ascii char from level files */
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include "../include/monster_hashtbl.h"

typedef enum {
    NORTH,
    SOUTH,
    EAST,
    WEST
} Direction;

typedef struct Room Room;
struct Room {
    char tiles[ROOM_SIZE][ROOM_SIZE];
    int x, y;
    char name[15];
    Room *neighbors[4];
};

/* generate rooms from the specified folder and return a pointer to it fill the rooms_done array with all the rooms created. */
Room* generate_rooms_from_file(char *room_path, Room *rooms_done[], int *rooms_done_amount, Hashtbl *monsters);

/* Check neigbor existence and link pointer / create neigbor */
void handle_neighbor(Room* room, char *path, char *line, Direction direction, Room** rooms_done, int* rooms_done_amount, Hashtbl* monsters);

/* Set all the coordinates by recursively traveling through rooms neighbors */
void set_rooms_coordinates(Room *room);

/* Free the specified room and all of its attributes */
void free_room(Room *room);

/* rewrite file_path and replace target_char with replacement_char */
void replace_character_in_file(const char* file_path, wchar_t target_char, wchar_t replacement_char);

/* to_string function */
void display_room(Room *room);

#endif
