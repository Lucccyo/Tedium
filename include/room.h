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

/* rewrite file_path and replace target_char with replacement_char */
void replace_character_in_file(const char* file_path, wchar_t target_char, wchar_t replacement_char);

/* to_string */
void display_room(Room *room);

#endif
