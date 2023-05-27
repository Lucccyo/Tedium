#ifndef MAZE_FILE
#define MAZE_FILE
#include <stdlib.h>
#include "../include/player.h"
#include "../include/room.h"
#include "../include/floor.h"
#include "../include/monster.h"
#include "../include/monster_hashtbl.h"

struct state {
  Player * player;
  Floor  * current_floor;
  Room   * current_room;
};
typedef struct state State;

struct maze {
  int max_floor;
  Floor * floors[34];
  Hashtbl * monsters;
  State * state;

};
typedef struct maze Maze;

Maze * create_maze(char path[], int x_player, int y_player);

#endif
