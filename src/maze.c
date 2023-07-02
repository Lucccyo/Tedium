#include "maze.h"

Maze * create_maze(char path_to_dir[], int x_player, int y_player) {
  /* initializing everithing to create the maze */
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
        Floor *floor = create_floor(path, monsters);
        maze->floors[maze->max_floor] = floor;
        (maze->max_floor)++;
      }
    }
  }
  /* closing the file descriptor is important :) */
  closedir(fd);

  /* if there is more than one floor, we set up their connection,
     as a double linked list */
  for (int i = 0; i < maze->max_floor - 1; i++) {
    if (i == 0) { continue; }
    maze->floors[i]->previous = maze->floors[i - 1];
  }
  for (int i = maze->max_floor - 1; i > 0; i--) {
    if (i == maze->max_floor) { continue; }
    maze->floors[i]->next = maze->floors[i + 1];
  }

  /* making links to start the game */
  maze->state->current_floor = maze->floors[0];
  maze->state->current_room = maze->floors[0]->rooms[0];
  maze->state->player = player;
  return maze;
}

void free_maze(Maze * maze){
  free_player(maze->state->player);
  free_hashtbl(maze->monsters);
  for (int i = 0 ; i < maze->max_floor; i++ ){
    free_floor(maze->floors[i]);
  }
  free(maze->state);
  free(maze);
}
