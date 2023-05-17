#include "../include/room.h"

Room* create_room_from_file(char *room_path) {
    /* format file to remove '§' */
    replace_character_in_file(room_path, L'§', L'P');

    /* Room initialization */
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

    /* Used as temp variable for monsters stats */
    int hp, force, armor;

    char line[31];
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
    return room;
}

Room* generate_room(int direction[4], char name[30]) {
    /* Room initialization */
    Room *room = malloc(sizeof(Room));
    room->empty = 0;

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
    printf("North : %s\n", room->north_name);
    printf("South : %s\n", room->south_name);
    printf("East : %s\n", room->east_name);
    printf("West : %s\n", room->west_name);
}
