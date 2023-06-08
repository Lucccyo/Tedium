#include "player.h"

/* create a player */
Player * create_player(int x_grid, int y_grid) {
  Player *p = malloc(sizeof(Player));
  p->health[health] = 10; p->health[max_health] = 10;
  p->stats[attack] = 2; p->stats[defense] = 1;
  p->key_number = 0;
  p->room_id = 1;
  p->coordinate[0] = x_grid; p->coordinate[1] = y_grid;
  p->direction = front;
  return p;
}

/* moving functions */
void go_left  (int* coordinate) {(*coordinate)--;}
void go_right (int* coordinate) {(*coordinate)++;}
void go_up    (int* coordinate) {(*(coordinate+1))--;}
void go_down  (int* coordinate) {(*(coordinate+1))++;}

/* stats functions */
void full_health (int* health) {*health = *(health+1);}
void update_health (int* health, int update) {(*health)+=update;}
void update_max_health (int* health, int update) {(*(health+1))+=update;}
void update_stats (int* stats, int index) {(*(stats+index))++;}
void update_key (int* key_number, int update) {(*key_number)+=update;}
void enable_cheat (Player *player) {
  player->health[1] = 1000;
  player->health[0] = player->health[1];
  player->stats[0] = 1000;
  player->stats[1] = 1000;
  player->key_number = 1000;
}

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
