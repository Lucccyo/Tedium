#ifndef MAZE_FILE
#define MAZE_FILE

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "player.h"
#include "room.h"
#include "floor.h"
#include "monster.h"
#include "monster_hashtbl.h"

#define MAX_FLOOR 30

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
