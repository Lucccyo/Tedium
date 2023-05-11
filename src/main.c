#include "../include/room.h"
#include "../include/floor.h"

int main() {
    /* room creation test */
    Room room = create_room("rooms/blank.level");
    display_room(room);

    /* floor creation test */
    Floor floor = create_floor("rooms/level1");
    display_floor(floor);
    return 0;
}