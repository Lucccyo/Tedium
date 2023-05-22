#include "../include/floor.h"

Floor* create_floor(char level_path[], Hashtbl *monsters) {
    /* get level number in level_path */
    
    Floor *floor = malloc(sizeof(Floor));
    floor->id = atoi(&level_path[10]);
    
    int rooms_amount = 0;

    /* generate rooms recursively */
    char starting_room[30];
    strcpy(starting_room, level_path);
    strcat(starting_room, "entry.level");
    
    generate_rooms_from_file(starting_room, floor->rooms, &rooms_amount, monsters);

    return floor;
}

void free_floor(Floor* floor) {
    for (int i = 0; i < FLOOR_SIZE; i++) {
        free_room(floor->rooms[i]);
    }
    free(floor);
    floor = NULL;
}

void display_rooms_names(Floor* floor) {
    printf("Floor %d:\n", floor->id);
    for (int i = 0; i < FLOOR_SIZE; i++) {
        if (floor->rooms[i] != NULL) {
            printf(" - %s\n", floor->rooms[i]->name); 
        }
    }
}
