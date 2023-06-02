#include "../include/room.h"
#include "../include/floor.h"
#include "../include/monster_hashtbl.h"

int main() {
    Hashtbl * h = create_hashtbl();

    /* floor creation test */
    printf("Floor creation test\n");
    Floor *test_floor = create_floor("maze/floor1/", h);
    printf("Floor created succesfully !\n");

    /* display floor test */
    display_floor(test_floor);

    /* display east neighbor of entry room test */
    display_room(test_floor->rooms[0]->neighbors[EAST]);
    free(test_floor);

    return 0;
}
