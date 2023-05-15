#include <stdio.h>
#include "../include/monster.h"

/* initialize a monster */
void reset_monster(Monster * m, int x, int y, int room_id) {
  m->health[0] = 10; m->health[1] = 10;
  m->stats[0] = 2; m->stats[1] = 1;
  m->room_id = room_id;
  m->coordinate[0] = x; m->coordinate[1] = y;
}

/* stats functions */
void update_health_monster(int* health, int update) { (*health)+=update; }

/* display debug */
void display_monster(Monster * m) {
  printf("\n"
  "health  : (%d/%d)\n"
  "attack  : %d\n"
  "defense : %d\n"
  "room_id : %d\n"
  "coordinates : (%d;%d)\n\n",
  m->health[0],
  m->health[1],
  m->stats[0],
  m->stats[1],
  m->room_id,
  m->coordinate[0],
  m->coordinate[1]);
}
