#ifndef MONSTER_FILE
#define MONSTER_FILE

#include <stdio.h>
#include <stdlib.h>

struct monster {
  /* health[0] -> current health
     health[1] -> max health */
  int health[2];
  /* stats[0] -> attack damage
     stats[1] -> defense */
  int stats[2];
  /* coordinate[0] -> x position in current room
     coordinate[1] -> y position in current room */
  int coordinate[2];
};
typedef struct monster Monster ;

/* create a monster */
Monster * create_monster(int health_max, int attack, int defense, int x, int y);

/* stats functions */
void update_health_monster(int* health, int update);

/* display debug */
void display_monster(Monster * m);

#endif
