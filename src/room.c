#include "../include/room.h"

Room create_room(char *room_path) {
    Room new_room = {
        .east_name = "",
        .south_name = "",
        .west_name = "",
        .north_name = "",
        .tiles = {{0}},
        .x = 0,
        .y = 0
    };

    FILE *file = fopen(room_path, "r");

    char line[31];
    int actual_line = 0;

    if (file == NULL) {
        printf("Error while oppening file.\n");
    }

    while (fgets(line, sizeof(line), file)) {
        /* End of file handling */
        if (feof(file))
            break;
        /* Empty line handling */
        if (strspn(line, " \t\n\r") == strlen(line))
            continue;
        /* Neigbors */
        if (strncmp(line, "East : ", 7) == 0) {
            strncpy(new_room.east_name, line + 7, sizeof(new_room.east_name) - 1);
            new_room.east_name[strcspn(new_room.east_name, "\n")] = '\0';
        } else if (strncmp(line, "South : ", 8) == 0) {
            strncpy(new_room.south_name, line + 8, sizeof(new_room.south_name) - 1);
            new_room.south_name[strcspn(new_room.south_name, "\n")] = '\0';
        } else if (strncmp(line, "West : ", 7) == 0) {
            strncpy(new_room.west_name, line + 7, sizeof(new_room.west_name) - 1);
            new_room.west_name[strcspn(new_room.west_name, "\n")] = '\0';
        } else if (strncmp(line, "North : ", 8) == 0) {
            strncpy(new_room.north_name, line + 8, sizeof(new_room.north_name) - 1);
            new_room.north_name[strcspn(new_room.north_name, "\n")] = '\0';
        /* Tiles */
        }  else if (actual_line < 30){ 
            strncpy(new_room.tiles[actual_line], line, 30);
            actual_line++;
        /* Monsters */
        } else if (strncmp(line, "A ", 1) == 0) {
            /* TODO: create monster in hashtbl*/
        } else if (strncmp(line, "B : ", 1) == 0) {
            /* TODO: create monster in hashtbl*/
        } else if (strncmp(line, "C : ", 1) == 0) {
            /* TODO: create monster in hashtbl*/
        }
    }
    fclose(file);
    return new_room;
}

void display_room(Room room) {
    printf("Room :%d | %d\n", room.x, room.y);
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            printf("%c", room.tiles[i][j]);
        }
        printf("\n");
    }
    printf("North : %s\n", room.north_name);
    printf("South : %s\n", room.south_name);
    printf("East : %s\n", room.east_name);
    printf("West : %s\n", room.west_name);
}