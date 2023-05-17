#ifndef MAZE_FILE
#define MAZE_FILE

#include <stdlib.h>
#include "../include/player.h"
#include "../include/room.h"
#include "../include/floor.h"
#include "../include/monster.h"
#include "../include/monster_hashtbl.h"


struct maze {
  Player * p;
  int max_floor;
  Floor * floors[3];
  Hashtbl * monsters;
};
typedef struct maze Maze;

void reset_maze(Maze * m, Player * p, Hashtbl * monsters);


#endif
