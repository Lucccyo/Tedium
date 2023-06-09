#ifndef PLAYER_FILE
#define PLAYER_FILE

#include <stdio.h>
#include <stdlib.h>

enum {left, right, back, front};
enum {x, y};
enum {attack, defense};
enum {health, max_health};

struct player {
  /* health[0] -> current health
     health[1] -> max health */
  int health[2];
  /* stats[0] -> attack damage
     stats[1] -> defense */
  int stats[2];
  int key_number;
  int room_id;
  /* coordinate[0] -> x position in current room
     coordinate[1] -> y position in current room */
  int coordinate[2];
  int direction;
};
typedef struct player Player ;

/* create a player starting at (x_grid, y_grid) */
Player * create_player(int x_grid, int y_grid);

/* moving functions */
void go_left  (int* coordinate);
void go_right (int* coordinate);
void go_up    (int* coordinate);
void go_down  (int* coordinate);

/* stats functions */
void full_health (int* health);
void update_health (int* health, int update);
void update_max_health (int* health, int update);
void update_stats (int* stats, int branch);
void update_key (int* key_number, int update);
void enable_cheat (Player *player);

/* display debug */
void display_player(Player *p);

#endif
