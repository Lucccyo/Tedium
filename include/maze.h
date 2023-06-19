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

/* Store the displayed environment.
   This part is going to evolve through the game. */
struct state {
  Player * player;
  Floor  * current_floor;
  Room   * current_room;
};
typedef struct state State;

struct maze {
  int max_floor;
  /* We can store several floors connected to the others,
     in order to add more fun to Tedium */
  Floor * floors[MAX_FLOOR];
  Hashtbl * monsters;
  State * state;
};
typedef struct maze Maze;

Maze * create_maze(char path[], int x_player, int y_player);

#endif
