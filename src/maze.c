#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include "../include/player.h"
#include "../include/floor.h"
#include "../include/maze.h"
#include "../include/monster_hashtbl.h"

void create_maze(char path_to_dir[]) {
  Maze * maze = (Maze*) malloc(sizeof(Maze));
  Player * player = (Player*) malloc(sizeof(Player));
  reset_player(player);
  Hashtbl * monsters = (Hashtbl*) malloc(sizeof(Hashtbl));
  reset_hashtbl(monsters);
  maze->player = player;
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
        Floor *floor = create_floor(path, maze->monsters);
        maze->floors[maze->max_floor] = floor;
        (maze->max_floor)++;
        printf("%s\n", path);
      }
    }
  }
  closedir(fd);
}

void add_floor(Maze * m, Floor * f){
  m->floors[m->max_floor] = f;
  (m->max_floor)++;
}

int main(){
  create_maze("maze/");
}
