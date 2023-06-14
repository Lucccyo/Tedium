#include "floor.h"

Floor* create_floor(char level_path[], Hashtbl *monsters) {

    /* get level number in level_path */
    Floor *floor = malloc(sizeof(Floor));
    floor->id = atoi(&level_path[10]);
    int rooms_amount = 0;

    /* generate rooms recursively */
    char starting_room[30];
    strcpy(starting_room, level_path);
    strcat(starting_room, "room1.level");

    generate_rooms_from_file(starting_room, floor->rooms, &rooms_amount, monsters);

    /* set coordinates and make them positives */
    floor->rooms[0]->x = 0;
    floor->rooms[0]->y = 0;
    set_rooms_coordinates(floor->rooms[0]);

    int min_x = 100;
    int min_y = 100;

    for (int i = 0; i < FLOOR_SIZE; i++) {
        if (floor->rooms[i] == NULL) { printf("END\n"); break; }
        if (floor->rooms[i]->x < min_x) { min_x = floor->rooms[i]->x; printf("[x] i = %d\n", i); }
        if (floor->rooms[i]->y < min_y) { min_y = floor->rooms[i]->y; printf("[y] i = %d\n", i); }
        printf("[ ] i = %d\n", i);
    }
    for (int i = 0; i < FLOOR_SIZE; i++) {
        if (floor->rooms[i] == NULL) { break; }
        floor->rooms[i]->x -= min_x;
        floor->rooms[i]->y -= min_y;
    }
    return floor;
}

void set_rooms_coordinates(Room *room) {
    if (room->neighbors[EAST] != NULL) {
        if (room->neighbors[EAST]->x == -100) {
            room->neighbors[EAST]->x = room->x + 1;
            room->neighbors[EAST]->y = room->y;
            set_rooms_coordinates(room->neighbors[EAST]);
        }
    }
    if (room->neighbors[SOUTH] != NULL) {
        if (room->neighbors[SOUTH]->x == -100) {
            room->neighbors[SOUTH]->x = room->x;
            room->neighbors[SOUTH]->y = room->y + 1;
            set_rooms_coordinates(room->neighbors[SOUTH]);
        }
    }
    if (room->neighbors[WEST] != NULL) {
        if (room->neighbors[WEST]->x == -100) {
            room->neighbors[WEST]->x = room->x - 1;
            room->neighbors[WEST]->y = room->y;
            set_rooms_coordinates(room->neighbors[WEST]);
        }
    }
    if (room->neighbors[NORTH] != NULL) {
        if (room->neighbors[NORTH]->x == -100) {
            room->neighbors[NORTH]->x = room->x;
            room->neighbors[NORTH]->y = room->y - 1;
            set_rooms_coordinates(room->neighbors[NORTH]);
        }
    }
}

void free_floor(Floor* floor) {
    for (int i = 0; i < FLOOR_SIZE; i++) {
        free_room(floor->rooms[i]);
    }
    free(floor);
    floor = NULL;
}

void display_floor(Floor* floor) {
    printf("Floor %d:\n", floor->id);
    for (int i = 0; i < FLOOR_SIZE; i++) {
        if (floor->rooms[i] != NULL) {
            printf(" - %s | %d, %d\n", floor->rooms[i]->name, floor->rooms[i]->x, floor->rooms[i]->y);
        }
    }
}
