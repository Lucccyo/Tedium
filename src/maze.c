#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include "player.h"
#include "floor.h"
#include "maze.h"
#include "monster_hashtbl.h"

Maze * create_maze(char path_to_dir[], int x_player, int y_player) {
  Maze * maze = (Maze*) malloc(sizeof(Maze));
  State * state = (State*) malloc(sizeof(State));
  Player * player = create_player(x_player, y_player);
  Hashtbl * monsters = create_hashtbl();
  maze->state = state;
  maze->monsters = monsters;
  maze->max_floor = 0;
  DIR *fd;
  struct dirent *dir;
  fd = opendir(path_to_dir);
  if(fd != NULL) {
    while ((dir = readdir(fd)) != NULL ) {
      if (strchr(dir->d_name,'.') == NULL) {
        char path[30];
        strcpy(path, path_to_dir);
        strcat(path, dir->d_name);
        strcat(path, "/");
        Floor *floor = create_floor(path, monsters);
        maze->floors[maze->max_floor] = floor;
        (maze->max_floor)++;
      }
    }
  }
  closedir(fd);
  maze->state->current_floor = maze->floors[0];
  maze->state->current_room = maze->floors[0]->rooms[0];
  maze->state->player = player;
  return maze;
}
