#include "maze.h"

Maze * create_maze(char path_to_dir[], int x_player, int y_player) {
  Maze * maze = (Maze*) malloc(sizeof(Maze));
  State * state = (State*) malloc(sizeof(State));
  Player * player = create_player(x_player, y_player);
  Hashtbl * monsters = create_hashtbl();
  maze->state = state;
  maze->monsters = monsters;
  maze->max_floor = 0;
  /* create floors from `path_to_dir[]` */
  DIR *fd;
  struct dirent *dir;
  fd = opendir(path_to_dir);
  if(fd != NULL) {

    /* we read all directories of the given path */
    while ((dir = readdir(fd)) != NULL ) {
      /* skip if the directory is `.` or `..` */
      if (strchr(dir->d_name,'.') == NULL) {
        char path[30];
        /* construction of the path to the floor directory */
        strcpy(path, path_to_dir);
        strcat(path, dir->d_name);
        strcat(path, "/");
        /* creation of the floor */
        printf("ready to add floor : %s\n", path);
        Floor *floor = create_floor(path, monsters);
        maze->floors[maze->max_floor] = floor;
        (maze->max_floor)++;
        printf("new floor added : %s\n", path);
      }
    }
  }
  /* closing the file descriptor is important :) */
  closedir(fd);
  /* making links to start the game */
  maze->state->current_floor = maze->floors[0];
  maze->state->current_room = maze->floors[0]->rooms[0];
  maze->state->player = player;
  return maze;
}
