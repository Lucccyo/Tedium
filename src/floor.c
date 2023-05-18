#include "../include/floor.h"

Floor* create_floor(char level_path[]) {
    /* get level number in level_path */
    
    Floor *floor = malloc(sizeof(Floor));
    floor->id = atoi(&level_path[10]);
    printf("floor id : %d\n", floor->id);
    
    int rooms_amount = 0;

    /* create the first room */
    char new_path[30];
    strcpy(new_path, level_path);
    strcat(new_path, "/entry.level");
    
    create_room_from_file(new_path, floor->rooms, rooms_amount);

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

/* NEED REWORK */
// void display_floor(Floor* floor) {
//     printf("Floor %d:\n", floor->id);
//     for (int i = 0;  i < FLOOR_SIZE; i++) {
//         for (int j = 0; j < FLOOR_SIZE; j++) {
//             if (floor->rooms[i][j]->empty) { printf("    empty    "); }
//             else { 
//                 printf(" %s ", floor->rooms[i][j]->name); 
//             }
//         }
//         printf("\n");
//     }
// }
