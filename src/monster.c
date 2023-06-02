#include <stdio.h>
#include "monster.h"

/* create a monster */
Monster * create_monster(int health_max, int attack, int defense, int x, int y){
  Monster * m = malloc(sizeof(Monster));
  m->health[0] = health_max; m->health[1] = health_max;
  m->stats[0] = attack; m->stats[1] = defense;
  m->coordinate[0] = x; m->coordinate[1] = y;
  return m;
}

/* stats functions */
void update_health_monster(int* health, int update) {
  (*health)+=update;
}

/* display debug */
void display_monster(Monster * m) {
  printf("\n"
  "health  : (%d/%d)\n"
  "attack  : %d\n"
  "defense : %d\n"
  "coordinates : (%d;%d)\n\n",
  m->health[0],
  m->health[1],
  m->stats[0],
  m->stats[1],
  m->coordinate[0],
  m->coordinate[1]);
}
