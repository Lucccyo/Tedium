#include "../include/room.h"
#include "../include/floor.h"

int main() {

    /* floor creation test */
    printf("Floor creation test\n");
    Floor *test_floor = create_floor("maze/floor1");
    printf("Floor created succesfully !\n");

    display_rooms_names(test_floor);
    free(test_floor);
    return 0;
}
