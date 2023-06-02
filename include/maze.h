#ifndef MAZE_FILE
#define MAZE_FILE
#include <stdlib.h>

#define MAX_FLOOR 30

#include "player.h"
#include "room.h"
#include "floor.h"
#include "monster.h"
#include "monster_hashtbl.h"

struct state {
  Player * player;
  Floor  * current_floor;
  Room   * current_room;
};
typedef struct state State;

struct maze {
  int max_floor;
  Floor * floors[MAX_FLOOR];
  Hashtbl * monsters;
  State * state;

};
typedef struct maze Maze;

Maze * create_maze(char path[], int x_player, int y_player);

#endif
