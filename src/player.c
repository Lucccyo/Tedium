#include <stdio.h>
#include "../include/player.h"

/* initialize a player */
void reset_player(Player * player) {
  player->health[0] = 10; player->health[1] = 10;
  player->stats[0] = 2; player->stats[1] = 1;
  player->key_number = 0;
  player->room_id = 1;
  player->coordinate[0] = 0; player->coordinate[1] = 0;
}

/* moving functions */
void go_left  (int* coordinate) { (*coordinate)--; }
void go_right (int* coordinate) { (*coordinate)++; }
void go_up    (int* coordinate) { (*(coordinate+1))--; }
void go_down  (int* coordinate) { (*(coordinate+1))++; }

/* stats functions */
void full_health(int* health) { *health = *(health+1); }
void update_health(int* health, int update) { (*health)+=update; }
void update_max_health(int* health, int update) { (*(health+1))+=update; }
void update_stats(int* stats, int branch) { (*(stats+branch))++; }
void update_key(int* key_number, int update) { (*key_number)+=update; }

/* display debug */
void display_player(Player * p) {
  printf("\n"
  "health  : (%d/%d)\n"
  "attack  : %d\n"
  "defense : %d\n"
  "key_number : %d\n"
  "room_id : %d\n"
  "coordinates : (%d;%d)\n\n",
  p->health[0],
  p->health[1],
  p->stats[0],
  p->stats[1],
  p->key_number,
  p->room_id,
  p->coordinate[0],
  p->coordinate[1]);
}
