#include <stdio.h>
#include "../include/maze.h"

void reset_maze(Maze * m, Player * p, Hashtbl * monsters){
  m->p = p;
  m->monsters = monsters;
  m->max_floor = 0
}

void add_floor(Maze * m, Floor * f){
  m->floors[m->max_floor] = f;
  (m->max_floor)++;
}
