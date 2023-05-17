#include <stdio.h>
#include "../include/maze.h"

/* initialize a player */
void reset_maze(Maze * m, Player * p, Hashtbl * monsters){
  m->p = p;
  m->monsters = monsters;
  // m->floors = (Floor *) malloc (sizeof(Floor *));
  m->max_floor = 0
}