#ifndef MONSTER_FILE
#define MONSTER_FILE

#include <stdlib.h>

struct monster {
  /* health[0] -> current health
     health[1] -> max health */
  int health[2];
  /* stats[0] -> attack damage
     stats[1] -> defense */
  int stats[2];
  int room_id;
  /* coordinate[0] -> x position in current room
     coordinate[1] -> y position in current room */
  int coordinate[2];
};
typedef struct monster Monster ;

/* initialize a monster */
void reset_monster(Monster * m, int room_id, int x, int y);

/* stats functions */
void update_health_monster(int* health, int update);

/* display debug */
void display_monster(Monster * m);

#endif
