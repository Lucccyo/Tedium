#include "../include/floor.h"

Floor* create_floor(char level_path[15]) {
    /* get level number in level_path */
    
    Floor *floor = malloc(sizeof(Floor));
    floor->id = atoi(level_path + 11);

    /* create empty rooms */
    for (int i = 0; i < FLOOR_SIZE; i++) {
        for (int j = 0; j < FLOOR_SIZE; j++) {
            floor->rooms[i][j] = create_room("rooms/empty.level");
            floor->rooms[i][j]->empty = 1;
            floor->rooms[i][j]->east = NULL;
            floor->rooms[i][j]->south = NULL;
            floor->rooms[i][j]->west = NULL;
            floor->rooms[i][j]->north = NULL;
        }
    }

    int rooms_amount = 0;
    char rooms_names[10][30];
    char rooms_done[10][30];
    int coords[10][2];
    Room *rooms[10];

    /* get the number of files with extension '.level' in level_path and their names */
    DIR* dp = opendir(level_path);
    if (dp != NULL) {
        struct dirent* dir;
        while ((dir = readdir(dp)) != NULL) {
            if (dir->d_type == DT_REG && strstr(dir->d_name, ".level") != NULL) {
                strcpy(rooms_names[rooms_amount], dir->d_name);
                rooms_amount++;
            }
        }
        closedir(dp);
    }

    /* create each room */
    for (int i = 0; i < rooms_amount; i++) {
        char path[50];
        strcpy(path, level_path);
        strcat(path, "/");
        strcat(path, rooms_names[i]);
        rooms[i] = create_room(path);
        rooms[i]->empty = 0;
        strcpy(rooms[i]->name, rooms_names[i]);
    }
    /* fix entry room coordinates */
    /* would be better to do it with a random room to prevent repetitive patterns */
    strcpy(rooms_done[0], rooms_names[0]);
    coords[0][0] = 0; coords[0][1] = 0;

    /* iterate trough neighbors until every room is done */
    /* Recursive method would be MUCH better but hard to do */
    int rooms_done_amount = 1;
    while (rooms_done_amount < rooms_amount) {
        for (int i = 0; i < rooms_done_amount+1; i++) {
            for (int j = 0; j < rooms_amount+1; j++) {
                if (strcmp(rooms_done[i], rooms_names[j]) == 0) {
                    /* check if there is a neighbor in east direction */
                    if (strcmp(rooms[j]->east_name, "") != 0) {
                        /* check if neighbor is already done */
                        int neighbor_done = 0;
                        for (int k = 0; k < rooms_done_amount; k++) {
                            if (strcmp(rooms_done[k], rooms[j]->east_name) == 0) {
                                neighbor_done = 1;
                            }
                        }
                        /* if neighbor is not done, add it to rooms_done and set its coordinates */
                        if (neighbor_done == 0) { 
                            int index = get_room_index(rooms[j]->east_name, rooms_names, rooms_amount);
                            strcpy(rooms_done[index], rooms[j]->east_name);
                            coords[index][0] = coords[i][0] + 1;
                            coords[index][1] = coords[i][1];
                            rooms_done_amount++;
                        }
                    }
                    /* check if there is a neighbor in south direction */
                    if (strcmp(rooms[j]->south_name, "") != 0) {
                        /* check if neighbor is already done */
                        int neighbor_done = 0;
                        for (int k = 0; k < rooms_done_amount; k++) {
                            if (strcmp(rooms_done[k], rooms[j]->south_name) == 0) {
                                neighbor_done = 1;
                            }
                        }
                        /* if neighbor is not done, add it to rooms_done and set its coordinates */
                        if (neighbor_done == 0) {
                            int index = get_room_index(rooms[j]->south_name, rooms_names, rooms_amount);
                            strcpy(rooms_done[index], rooms[j]->south_name);
                            coords[index][0] = coords[i][0];
                            coords[index][1] = coords[i][1] + 1;
                            rooms_done_amount++;
                        }
                    }
                    /* check if there is a neighbor in west direction */
                    if (strcmp(rooms[j]->west_name, "") != 0) {
                        /* check if neighbor is already done */
                        int neighbor_done = 0;
                        for (int k = 0; k < rooms_done_amount; k++) {
                            if (strcmp(rooms_done[k], rooms[j]->west_name) == 0) {
                                neighbor_done = 1;
                            }
                        }
                        /* if neighbor is not done, add it to rooms_done and set its coordinates */
                        if (neighbor_done == 0) {
                            int index = get_room_index(rooms[j]->west_name, rooms_names, rooms_amount);
                            strcpy(rooms_done[index], rooms[j]->west_name);
                            coords[index][0] = coords[i][0] - 1;
                            coords[index][1] = coords[i][1];
                            rooms_done_amount++;
                        }
                    }
                    /* check if there is a neighbor in north direction */
                    if (strcmp(rooms[j]->north_name, "") != 0) {
                        /* check if neighbor is already done */
                        int neighbor_done = 0;
                        for (int k = 0; k < rooms_done_amount; k++) {
                            if (strcmp(rooms_done[k], rooms[j]->north_name) == 0) {
                                neighbor_done = 1;
                            }
                        }
                        /* if neighbor is not done, add it to rooms_done and set its coordinates */
                        if (neighbor_done == 0) {
                            int index = get_room_index(rooms[j]->north_name, rooms_names, rooms_amount);
                            strcpy(rooms_done[index], rooms[j]->north_name);
                            coords[index][0] = coords[i][0];
                            coords[index][1] = coords[i][1] - 1;
                            rooms_done_amount++;
                        }
                    }
                }
            }
        }   
    }
    
    /* Make all coordinates positives */
    int min_x, min_y = 0;
    for (int i = 0; i < rooms_amount; i++) {
        if (coords[i][0] < min_x) { min_x = coords[i][0]; }
        if (coords[i][1] < min_y) { min_y = coords[i][1]; }
    }
    for (int i = 0; i < rooms_amount; i++) {
        coords[i][0] -= min_x;
        coords[i][1] -= min_y;
    }

    /* Place rooms in floor.rooms array */
    for (int i = 0; i < rooms_amount; i++) {
        free(floor->rooms[coords[i][1]][coords[i][0]]);
        floor->rooms[coords[i][1]][coords[i][0]] = rooms[i];
    }

    /* Fix pointers */
    for (int i = 0; i < FLOOR_SIZE; i++) {
        for (int j = 0; j < FLOOR_SIZE; j++) {
            if (floor->rooms[i][j]->empty == 0) {
                /* Check east neighbor */
                if (j < FLOOR_SIZE - 1 && !floor->rooms[i][j+1]->empty) {
                    floor->rooms[i][j]->east = floor->rooms[i][j+1];
                }
                /* Check south neighbor */
                if (i < FLOOR_SIZE - 1 && !floor->rooms[i+1][j]->empty) {
                    floor->rooms[i][j]->south = floor->rooms[i+1][j];
                }
                /* Check west neighbor */
                if (j > 0 && !floor->rooms[i][j-1]->empty) {
                    floor->rooms[i][j]->west = floor->rooms[i][j-1];
                }
                /* Check north neighbor */
                if (i > 0 && !floor->rooms[i-1][j]->empty) {
                    floor->rooms[i][j]->north = floor->rooms[i-1][j];
                }
            }
        }
    }
    return floor;
}

/* return the position of room_names in rooms_names array, -1 if not present */
int get_room_index(char room_name[30], char rooms_names[10][30], int rooms_amount) {
    for (int i = 0; i < rooms_amount; i++) {
        if (strcmp(room_name, rooms_names[i]) == 0) {
            return i;
        }
    }
    return -1;
}

void free_floor(Floor* floor) {
    for (int i = 0; i < FLOOR_SIZE; i++) {
        for (int j = 0; j < FLOOR_SIZE; j++) {
            free_room(floor->rooms[i][j]);
        }
    }
    free(floor);
    floor = NULL;
}


/* display the floor like a minimap */
void display_floor_map(Floor* floor) {
    printf("Floor %d:\n", floor->id);
    printf("  1 2 3 4\n");
    for (int i = 0;  i < FLOOR_SIZE; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < FLOOR_SIZE; j++) {
            if (floor->rooms[i][j]->empty) { printf("  "); }
            else { printf("X "); }
        }
        printf("\n");
    }
}

/* display floor by showing room_names */
void display_floor(Floor* floor) {
    printf("Floor %d:\n", floor->id);
    for (int i = 0;  i < FLOOR_SIZE; i++) {
        for (int j = 0; j < FLOOR_SIZE; j++) {
            if (floor->rooms[i][j]->empty) { printf("    empty    "); }
            else { 
                printf(" %s ", floor->rooms[i][j]->name); 
            }
        }
        printf("\n");
    }
}
