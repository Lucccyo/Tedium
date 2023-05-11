#include "../include/floor.h"

Floor create_floor(char level_path[15]) {
    Floor new_floor;
    /* get level number in level_path */
    new_floor.id = atoi(level_path + 11);

    int rooms_amount = 0;
    char rooms_names[10][30];
    char rooms_done[10][30];
    char coords[10][2];
    Room rooms[10];

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
    }

    /* fix entry room coordinates */
    /* would be better to do it with a random room to prevent repetitive patterns */
    strcpy(rooms_done[0], rooms_names[0]);
    coords[0][0] = 0; coords[0][1] = 0;

    /* iterate trough neighbors until every room is done */
    /* Recursive method would be MUCH better but hard to do */
    int rooms_done_amount = 1;
    while (rooms_done_amount < rooms_amount) {
        for (int i = 0; i < rooms_done_amount; i++) {
            for (int j = 0; j < rooms_amount; j++) {
                if (strcmp(rooms_done[i], rooms_names[j]) == 0) {
                    /* check if there is a neighbor in east direction */
                    if (strcmp(rooms[j].east_name, "") != 0) {
                        /* check if neighbor is already done */
                        int neighbor_done = 0;
                        for (int k = 0; k < rooms_done_amount; k++) {
                            if (strcmp(rooms_done[k], rooms[j].east_name) == 0) {
                                neighbor_done = 1;
                            }
                        }
                        /* if neighbor is not done, add it to rooms_done and set its coordinates */
                        if (neighbor_done == 0) {
                            strcpy(rooms_done[rooms_done_amount], rooms[j].east_name);
                            coords[rooms_done_amount][0] = coords[i][0] + 1;
                            coords[rooms_done_amount][1] = coords[i][1];
                            rooms_done_amount++;
                        }
                    }
                    /* check if there is a neighbor in south direction */
                    if (strcmp(rooms[j].south_name, "") != 0) {
                        /* check if neighbor is already done */
                        int neighbor_done = 0;
                        for (int k = 0; k < rooms_done_amount; k++) {
                            if (strcmp(rooms_done[k], rooms[j].south_name) == 0) {
                                neighbor_done = 1;
                            }
                        }
                        /* if neighbor is not done, add it to rooms_done and set its coordinates */
                        if (neighbor_done == 0) {
                            strcpy(rooms_done[rooms_done_amount], rooms[j].south_name);
                            coords[rooms_done_amount][0] = coords[i][0];
                            coords[rooms_done_amount][1] = coords[i][1] + 1;
                            rooms_done_amount++;
                        }
                    }
                    /* check if there is a neighbor in west direction */
                    if (strcmp(rooms[j].west_name, "") != 0) {
                        /* check if neighbor is already done */
                        int neighbor_done = 0;
                        for (int k = 0; k < rooms_done_amount; k++) {
                            if (strcmp(rooms_done[k], rooms[j].west_name) == 0) {
                                neighbor_done = 1;
                            }
                        }
                        /* if neighbor is not done, add it to rooms_done and set its coordinates */
                        if (neighbor_done == 0) {
                            strcpy(rooms_done[rooms_done_amount], rooms[j].west_name);
                            coords[rooms_done_amount][0] = coords[i][0] - 1;
                            coords[rooms_done_amount][1] = coords[i][1];
                            rooms_done_amount++;
                        }
                    }
                    /* check if there is a neighbor in north direction */
                    if (strcmp(rooms[j].north_name, "") != 0) {
                        /* check if neighbor is already done */
                        int neighbor_done = 0;
                        for (int k = 0; k < rooms_done_amount; k++) {
                            if (strcmp(rooms_done[k], rooms[j].north_name) == 0) {
                                neighbor_done = 1;
                            }
                        }
                        /* if neighbor is not done, add it to rooms_done and set its coordinates */
                        if (neighbor_done == 0) {
                            strcpy(rooms_done[rooms_done_amount], rooms[j].north_name);
                            coords[rooms_done_amount][0] = coords[i][0];
                            coords[rooms_done_amount][1] = coords[i][1] - 1;
                            rooms_done_amount++;
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < rooms_amount; i++) {
        printf("%s | %d, %d\n", rooms_done[i], coords[i][0], coords[i][1]);
    }

    /* TODO: make all coordinates positives */
    /* TODO: place rooms in array */
    /* TODO: fix all pointers */
    return new_floor;
}

void display_floor(Floor floor) {
    printf("Floor %d\n", floor.id);
    for (int i = 0;  i < FLOOR_SIZE; i++) {
        for (int j = 0; j < FLOOR_SIZE; j++) {
            /* not working because floor.rooms is not filled yet*/
            // display_room(floor.rooms[i][j]);
        }
    }
}