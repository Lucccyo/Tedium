#include "../include/room.h"
#include "../include/floor.h"

int main() {
    /* room creation test
    Room room = create_room("rooms/empty.level");
    display_room(room); */

    /* floor creation test */
    Floor test_floor = create_floor("rooms/level1");
    display_floor(test_floor);

    printf("Room in y1 | x0 is : %s\n", test_floor.rooms[1][0].name);
    Room *east_neighbor = test_floor.rooms[1][0].east;
    printf("east neighbor is : %s\n", east_neighbor->name);
    /* Seg fault car pas de voisin 
       A voir comment on gere les salles vides
       pointeur vers empty.level ? 
    Room *south_neighbor = test_floor.rooms[1][0].south;
    printf("south neighbor is : %s\n", south_neighbor->name); */
    return 0;
}
