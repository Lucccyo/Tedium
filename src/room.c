#include <time.h>
#include "room.h"

Room* generate_rooms_from_file(char *room_path, Room *rooms_done[], int *rooms_done_amount, Hashtbl *monsters) {
    /* format file to replace '§' with 'Z' */
    replace_character_in_file(room_path, L'§', L'Z');

    /* format room_path to keep only the level name and extract level id */
    char level_name[30];
    char *str = strchr(room_path + 1, '/');
    strcpy(level_name, str + 1);
    char *str2 = strchr(level_name + 1, '/');
    *str2 = '\0';
    int level_id = atoi(level_name + 5);

    /* Room initialization */
    Room *room = calloc(1, sizeof(Room));
    for (int i = 0; i < ROOM_SIZE; i++) {
        for (int j = 0; j < ROOM_SIZE; j++) {
            room->tiles[i][j] = ' ';
        }
    }

    /* Absurd values so the set_coordinates function can check if they have been modified */
    room->x = -100;
    room->y = -100;

    /* format room_path to keep only the level name */
    char *name = strchr(room_path + 1, '/');
    name = strchr(name + 1, '/');
    strcpy(room->name, name + 1);

    /* fill the floor room list */
    rooms_done[*rooms_done_amount] = room;
    (*rooms_done_amount)++;

    /* Used as temp variable for monsters stats */
    int health_a, attack_a, defense_a;
    int health_b, attack_b, defense_b;
    int health_c, attack_c, defense_c;
    health_a = health_b = health_c = attack_a = attack_b = attack_c = defense_a = defense_b = defense_c = 0;

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
        /* Tiles */
        if (actual_line < 30){
            strncpy(room->tiles[actual_line], line, 30);
            actual_line++;
        /* Neigbors */
        } else if (strncmp(line, "Est : ", 6) == 0 && strlen(line) > 6 && line[6] != '\n') {
            handle_neighbor(room, room_path, line, EAST, rooms_done, rooms_done_amount, monsters);
        } else if (strncmp(line, "Sud : ", 6) == 0 && strlen(line) > 6 && line[6] != '\n') {
            handle_neighbor(room, room_path, line, SOUTH, rooms_done, rooms_done_amount, monsters);
        } else if (strncmp(line, "Ouest : ", 8) == 0 && strlen(line) > 8 && line[8] != '\n') {
            handle_neighbor(room, room_path, line, WEST, rooms_done, rooms_done_amount, monsters);
        } else if (strncmp(line, "Nord : ", 7) == 0 && strlen(line) > 7 && line[7] != '\n') {
            handle_neighbor(room, room_path, line, NORTH, rooms_done, rooms_done_amount, monsters);
        /* Monsters */
        } else if (strncmp(line, "A ", 1) == 0) {
            fgets(line, sizeof(line), file);
            sscanf(line, "Pv : %d", &health_a);
            fgets(line, sizeof(line), file);
            sscanf(line, "Force : %d", &attack_a);
            fgets(line, sizeof(line), file);
            sscanf(line, "Armure : %d", &defense_a);
            /* TODO: populate hashtable */
        } else if (strncmp(line, "B : ", 1) == 0) {
            fgets(line, sizeof(line), file);
            sscanf(line, "Pv : %d", &health_b);
            fgets(line, sizeof(line), file);
            sscanf(line, "Force : %d", &attack_b);
            fgets(line, sizeof(line), file);
            sscanf(line, "Armure : %d", &defense_b);
            /* TODO: populate hashtable */
        } else if (strncmp(line, "C : ", 1) == 0) {
            fgets(line, sizeof(line), file);
            sscanf(line, "Pv : %d", &health_c);
            fgets(line, sizeof(line), file);
            sscanf(line, "Force : %d", &attack_b);
            fgets(line, sizeof(line), file);
            sscanf(line, "Armure : %d", &defense_c);
            /* TODO: populate hashtable */
        }
    }
    fclose(file);

    for (int i = 0; i < ROOM_SIZE; i++) {
        for (int j = 0; j < ROOM_SIZE; j++) {
            if (room->tiles[i][j] == 'A' || room->tiles[i][j] == 'B' || room->tiles[i][j] == 'C') {
                switch (room->tiles[i][j]) {
                    case 'A':
                        insert_monster(monsters, j, i, room->name, level_id, health_a, attack_a, defense_a);
                        break;
                    case 'B':
                        insert_monster(monsters, j, i, room->name, level_id, health_b, attack_b, defense_b);
                        break;
                    case 'C':
                        insert_monster(monsters, j, i, room->name, level_id, health_c, attack_c, defense_c);
                        break;
                    default:
                        break;
                }
            }
        }
    }
    /* format file again to replace 'Z' with '§' */
    replace_character_in_file(room_path, L'Z', L'§');

    add_decorations(room);
    return room;
}

void handle_neighbor(Room* room, char *path, char *line, Direction direction, Room** rooms_done, int* rooms_done_amount, Hashtbl* monsters) {
    char neighbor_name[30] = "";
    switch (direction) {
        case EAST:
            strncpy(neighbor_name, line + 6, strlen(line) - 6);
            break;
        case SOUTH:
            strncpy(neighbor_name, line + 6, strlen(line) - 6);
            break;
        case WEST:
            strncpy(neighbor_name, line + 8, strlen(line) - 8);
            break;
        case NORTH:
            strncpy(neighbor_name, line + 7, strlen(line) - 7);
            break;
        default:
            break;
        }
    neighbor_name[strlen(neighbor_name) - 1] = '\0';
    // if room already exists in rooms_done, link it, else create it
    int room_exists = 0;
    int i;
    for (i = 0; i < *rooms_done_amount; i++) {
        if (strcmp(rooms_done[i]->name, neighbor_name) == 0) {
            room_exists = 1;
            break;
        }
    }
    if (room_exists == 1) {
        room->neighbors[direction] = rooms_done[i];
    } else {
        char new_path[30] = "";
        strncpy(new_path, path, strlen(path) - strlen(room->name));
        strcat(new_path, neighbor_name);
        room->neighbors[direction] = generate_rooms_from_file(new_path, rooms_done, rooms_done_amount, monsters);
    }
}

void add_decorations(Room *room) {
    /* must be set in the maze creation to have the same seed for all rooms */
    srand(time(NULL));
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            /* Tiles decorations */
            if (room->tiles[i][j] == ' ' && rand() % 100 < 15) {
                int decoration_value = rand() % 3 + 4;
                char decoration_char[2];
                sprintf(decoration_char, "%d", decoration_value);
                room->tiles[i][j] = decoration_char[0];
            /* Fire decoration */
            } else if (room->tiles[i][j] == ' ' && rand() % 100 < 2) {
                int can_have_fire = 1;
                for (int dx = -1; dx < 2; dx++) {
                    for (int dy = -1; dy < 2; dy++) {
                        if (i + dx >= 0 && i + dx < 30 && j + dy >= 0 && j + dy < 30 && room->tiles[i + dx][j + dy] == '#') {
                            can_have_fire = 0;
                        }
                    }
                }
                if (can_have_fire == 1) {
                    room->tiles[i][j] = '7';
                }
            }
        }
    }
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
    if (room->neighbors[NORTH] != NULL) { printf("North : %s\n", room->neighbors[NORTH]->name); }
    if (room->neighbors[SOUTH] != NULL) { printf("South : %s\n", room->neighbors[SOUTH]->name); }
    if (room->neighbors[EAST]  != NULL)  { printf("East : %s\n", room->neighbors[EAST]->name); }
    if (room->neighbors[WEST]  != NULL)  { printf("West : %s\n", room->neighbors[WEST]->name); }
}
