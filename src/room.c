#include "../include/room.h"

Room* create_room(char *room_path) {
    Room *room = malloc(sizeof(Room));

    room->empty = 1;
    strcpy(room->name, "");
    strcpy(room->north_name, "");
    strcpy(room->south_name, "");
    strcpy(room->east_name, "");
    strcpy(room->west_name, "");
    room->east = NULL;
    room->south = NULL;
    room->west = NULL;
    room->north = NULL;
    for (int i = 0; i < ROOM_SIZE; i++) {
        for (int j = 0; j < ROOM_SIZE; j++) {
            room->tiles[i][j] = ' ';
        }
    }
    room->x = 0;
    room->y = 0;


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
        if (strncmp(line, "Est : ", 6) == 0) {
            strncpy(room->east_name, line + 6, sizeof(room->east_name) - 1);
            room->east_name[strcspn(room->east_name, "\n")] = '\0';
        } else if (strncmp(line, "Sud : ", 6) == 0) {
            strncpy(room->south_name, line + 6, sizeof(room->south_name) - 1);
            room->south_name[strcspn(room->south_name, "\n")] = '\0';
        } else if (strncmp(line, "Ouest : ", 8) == 0) {
            strncpy(room->west_name, line + 8, sizeof(room->west_name) - 1);
            room->west_name[strcspn(room->west_name, "\n")] = '\0';
        } else if (strncmp(line, "Nord : ", 7) == 0) {
            strncpy(room->north_name, line + 7, sizeof(room->north_name) - 1);
            room->north_name[strcspn(room->north_name, "\n")] = '\0';
        /* Tiles */
        }  else if (actual_line < 30){ 
            strncpy(room->tiles[actual_line], line, 30);
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
    return room;
}

void free_room(Room *room) {
    free(room);
    room = NULL;
}

void display_room(Room *room) {
    printf("Room :%d | %d\n", room->x, room->y);
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            printf("%c", room->tiles[i][j]);
        }
        printf("\n");
    }
    printf("North : %s\n", room->north_name);
    printf("South : %s\n", room->south_name);
    printf("East : %s\n", room->east_name);
    printf("West : %s\n", room->west_name);
}
