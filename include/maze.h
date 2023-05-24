#ifndef MAZE_FILE
#define MAZE_FILE
#include <stdlib.h>
#include "../include/player.h"
#include "../include/room.h"
#include "../include/floor.h"
#include "../include/monster.h"
#include "../include/monster_hashtbl.h"


struct maze {
  Player * player;
  int max_floor;
  Floor * floors[34];
  Hashtbl * monsters;
};
typedef struct maze Maze;

Maze * create_maze(char path[]);
void add_floor(Maze * m, Floor * f);

#endif
