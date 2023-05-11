#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/player.h"

int main(int argc, char const *argv[])
{
    Player * p = create();
    display(p);
    go_right(p->coordinate);
    update_max_health(p->health, 3);
    update_key(&(p->key_number), 3);
    update_key(&(p->key_number), -2);
    display(p);
    return 0;
}
