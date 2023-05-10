#include <stdio.h>
#include <stdlib.h>
#include "../include/room.h"

int main() {
    Room room = create_room();
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            printf("%c", room.tiles[i][j]);
        }
        printf("\n");
    }
    printf("North : %s\n", room.north);
    printf("South : %s\n", room.south);
    printf("East : %s\n", room.east);
    printf("West : %s\n", room.west);

    return 0;
}
