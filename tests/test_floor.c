#include "../include/room.h"
#include "../include/floor.h"

int main() {

    /* floor creation test */
    printf("Floor creation test\n");
    Floor *test_floor = create_floor("maze/floor1");
    printf("Floor created succesfully !\n");

    /* display floor test */
    display_rooms_names(test_floor);

    /* display east neighbor of entry room test */
    display_room(test_floor->rooms[0]->east);
    free(test_floor);

    return 0;
}
