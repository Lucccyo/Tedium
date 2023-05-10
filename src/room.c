#include "../include/room.h"

Room create_room() {
    Room new_room;

    FILE *file = fopen("rooms/blank", "r");

    char line[31];
    int actual_line = 0;

    if (file == NULL) {
        printf("Error while oppening file.\n");
    }

    while (fgets(line, sizeof(line), file) && actual_line < 30) {
        if (strspn(line, " \t\n\r") == strlen(line))
            continue; 
            
        if (strncmp(line, "East:", 5) == 0) {
            strncpy(new_room.east, line + 5, sizeof(new_room.east) - 1);
            new_room.east[sizeof(new_room.east) - 1] = '\0';
        } else if (strncmp(line, "South:", 6) == 0) {
            strncpy(new_room.south, line + 6, sizeof(new_room.south) - 1);
            new_room.south[sizeof(new_room.south) - 1] = '\0';
        } else if (strncmp(line, "West:", 5) == 0) {
            strncpy(new_room.west, line + 5, sizeof(new_room.west) - 1);
            new_room.west[sizeof(new_room.west) - 1] = '\0';
        } else if (strncmp(line, "North:", 6) == 0) {
            strncpy(new_room.north, line + 6, sizeof(new_room.north) - 1);
            new_room.north[sizeof(new_room.north) - 1] = '\0';
        } else {
            strncpy(new_room.tiles[actual_line], line, 30);
            actual_line++;
        }
    }

    fclose(file);
    return new_room;
}
