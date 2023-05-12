#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/player.h"

enum {attack, defense};

int main(int argc, char const *argv[])
{
    Player * p = (Player*) malloc(sizeof(Player));
    reset_player(p);
    display(p);
    go_right(p->coordinate);
    update_max_health(p->health, 3);
    update_key(&(p->key_number), 3);
    update_key(&(p->key_number), -2);
    update_stats(p->stats, attack);
    update_stats(p->stats, defense);
    display(p);
    return 0;
}
