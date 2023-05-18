#include "../include/room.h"

Room* create_room_from_file(char *room_path, Room *rooms_done[], int rooms_done_amount) {
    /* format file to replace '§' with 'P'*/
    replace_character_in_file(room_path, L'§', L'P');
    printf("creating room : %s\n", room_path);

    /* Room initialization */
    Room *room = malloc(sizeof(Room));
    room->east = NULL;
    room->south = NULL;
    room->west = NULL;
    room->north = NULL;
    strcpy(room->name, room_path + 12);
    printf("room name : %s\n", room->name);
    for (int i = 0; i < ROOM_SIZE; i++) {
        for (int j = 0; j < ROOM_SIZE; j++) {
            room->tiles[i][j] = ' ';
        }
    }
    room->x = 0;
    room->y = 0;

    /* fill the floor room list */
    rooms_done[rooms_done_amount] = room;
    rooms_done_amount++;

    /*for debug purpose*/
    for (int i = 0; i < rooms_done_amount; i++) {
        printf("room %d : %s\n", i, rooms_done[i]->name);
    }

    /* Used as temp variable for monsters stats */
    int hp, force, armor;

    char line[30];
    int actual_line = 0;

    FILE *file = fopen(room_path, "r");
    if (file == NULL) { printf("Error while oppening file.\n"); }

    while (fgets(line, sizeof(line), file)) {
        /* End of file handling */
        if (feof(file))
            break;
        /* Empty line handling */
        if (strspn(line, " \t\n\r") == strlen(line))
            continue;
        /* Neigbors */
        if (strncmp(line, "Est : ", 6) == 0 && strlen(line) > 6 && line[6] != '\n') {
            char neighbor_name[30] = "";
            strncpy(neighbor_name, line + 6, strlen(line) - 6);
            neighbor_name[strlen(neighbor_name) - 1] = '\0';
            // if room already exists in rooms_done, link it, else create it
            int room_exists = 0;
            int index = 0;
            for (int i = 0; i < rooms_done_amount; i++) {
                if (strcmp(rooms_done[i]->name, neighbor_name) == 0) { 
                    room_exists = 1; 
                    index = i;
                    break;
                }
            }
            if (room_exists == 1) {
                printf("room already exists\n");
                room->east = rooms_done[index];
                rooms_done[index]->west = room;
            } else {
                printf("room doesn't exist\n");
                char new_room_path[30] = "";
                strncpy(new_room_path, room_path, strlen(room_path) - strlen(room->name));
                strcat(new_room_path, neighbor_name);
                room->east = create_room_from_file(new_room_path, rooms_done, rooms_done_amount);
            }
        } else if (strncmp(line, "Sud : ", 6) == 0 && strlen(line) > 6 && line[6] != '\n') {
            char neighbor_name[30] = "";
            strncpy(neighbor_name, line + 6, strlen(line) - 6);
            neighbor_name[strlen(neighbor_name) - 1] = '\0';
            // if room already exists in rooms_done, link it, else create it
            int room_exists = 0;
            int index = 0;
            for (int i = 0; i < rooms_done_amount; i++) {
                if (strcmp(rooms_done[i]->name, neighbor_name) == 0) {
                    room_exists = 1;
                    index = i;
                    break;
                }
            }
            if (room_exists == 1) {
                printf("room already exists\n");
                room->south = rooms_done[index];
                rooms_done[index]->north = room;
            } else {
                printf("room doesn't exist\n");
                char new_room_path[30] = "";
                strncpy(new_room_path, room_path, strlen(room_path) - strlen(room->name));
                strcat(new_room_path, neighbor_name);
                room->south = create_room_from_file(new_room_path, rooms_done, rooms_done_amount);
            }
        } else if (strncmp(line, "Ouest : ", 8) == 0 && strlen(line) > 8 && line[8] != '\n') {
            char neighbor_name[30] = "";
            strncpy(neighbor_name, line + 8, strlen(line) - 8);
            neighbor_name[strlen(neighbor_name) - 1] = '\0';
            // if room already exists in rooms_done, link it, else create it
            int room_exists = 0;
            int index = 0;
            for (int i = 0; i < rooms_done_amount; i++) {
                if (strcmp(rooms_done[i]->name, neighbor_name) == 0) {
                    room_exists = 1;
                    index = i;
                    break;
                }
            }
            if (room_exists == 1) {
                printf("room already exists\n");
                room->west = rooms_done[index];
                rooms_done[index]->east = room;
            } else {
                printf("room doesn't exist\n");
                char new_room_path[30] = "";
                strncpy(new_room_path, room_path, strlen(room_path) - strlen(room->name));
                strcat(new_room_path, neighbor_name);
                room->west = create_room_from_file(new_room_path, rooms_done, rooms_done_amount);
            }
        } else if (strncmp(line, "Nord : ", 7) == 0 && strlen(line) > 7 && line[7] != '\n') {
            char neighbor_name[30] = "";
            strncpy(neighbor_name, line + 7, strlen(line) - 7);
            neighbor_name[strlen(neighbor_name) - 1] = '\0';
            // if room already exists in rooms_done, link it, else create it
            int room_exists = 0;
            int index = 0;
            for (int i = 0; i < rooms_done_amount; i++) {
                if (strcmp(rooms_done[i]->name, neighbor_name) == 0) {
                    room_exists = 1;
                    index = i;
                    break;
                }
            }
            if (room_exists == 1) {
                printf("room already exists\n");
                room->north = rooms_done[index];
                rooms_done[index]->south = room;
            } else {
                printf("room doesn't exist\n");
                char new_room_path[30] = "";
                strncpy(new_room_path, room_path, strlen(room_path) - strlen(room->name));
                strcat(new_room_path, neighbor_name);
                room->north = create_room_from_file(new_room_path, rooms_done, rooms_done_amount);
            }
        /* Tiles */
        }  else if (actual_line < 30){ 
            strncpy(room->tiles[actual_line], line, 30);
            actual_line++;
        /* Monsters */
        } else if (strncmp(line, "A ", 1) == 0) {
            fgets(line, sizeof(line), file);
            sscanf(line, "Pv : %d", &hp);
            fgets(line, sizeof(line), file);
            sscanf(line, "Force : %d", &force);
            fgets(line, sizeof(line), file);
            sscanf(line, "Armure : %d", &armor);
            /* TODO: populate hashtable */
        } else if (strncmp(line, "B : ", 1) == 0) {
            fgets(line, sizeof(line), file);
            sscanf(line, "Pv : %d", &hp);
            fgets(line, sizeof(line), file);
            sscanf(line, "Force : %d", &force);
            fgets(line, sizeof(line), file);
            sscanf(line, "Armure : %d", &armor);
            /* TODO: populate hashtable */
        } else if (strncmp(line, "C : ", 1) == 0) {
            fgets(line, sizeof(line), file);
            sscanf(line, "Pv : %d", &hp);
            fgets(line, sizeof(line), file);
            sscanf(line, "Force : %d", &force);
            fgets(line, sizeof(line), file);
            sscanf(line, "Armure : %d", &armor);
            /* TODO: populate hashtable */
        }
    }
    fclose(file);
    
    /* format file to replace 'P' with '§' */
    replace_character_in_file(room_path, L'§', L'P');
    
    return room;
}

void free_room(Room *room) {
    free(room);
    room = NULL;
}

void replace_character_in_file(const char* file_path, wchar_t target_char, wchar_t replacement_char) {
    // Set the locale to use the system's default encoding
    setlocale(LC_ALL, ""); 

    // Open the input file
    FILE* input_file = fopen(file_path, "r");
    if (input_file == NULL) {
        printf("Error opening input file.\n");
        return;
    }

    // Open a temporary file
    FILE* temp_file = fopen("temp.level", "w");
    if (temp_file == NULL) {
        printf("Error opening temporary file.\n");
        fclose(input_file);
        return;
    }

    // Read the input file
    wchar_t line[256];
    while (fgetws(line, sizeof(line), input_file)) {
        // Replace target_char with replacement_char in each line
        for (int i = 0; line[i] != L'\0'; i++) {
            if (line[i] == target_char) {
                line[i] = replacement_char;
            }
        }
        // Write the modified line to the temporary file
        fwprintf(temp_file, L"%ls", line);
    }

    fclose(input_file);
    fclose(temp_file);

    if (rename("temp.level", file_path) != 0) {
        printf("Error renaming file.\n");
        return;
    }
}

void display_room(Room *room) {
    printf("Room :%d | %d\n", room->x, room->y);
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            printf("%c", room->tiles[i][j]);
        }
        printf("\n");
    }
    printf("North : %s\n", room->north->name);
    printf("South : %s\n", room->south->name);
    printf("East : %s\n", room->east->name);
    printf("West : %s\n", room->west->name);
}
