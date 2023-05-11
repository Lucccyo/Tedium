#include <stdio.h>
#include "../include/player.h"

/* moving functions */
void go_left  (int* coordinate) { (*coordinate)--; }
void go_right (int* coordinate) { (*coordinate)++; }
void go_top   (int* coordinate) { (*(coordinate+1))--; }
void go_down  (int* coordinate) { (*(coordinate+1))++; }

/* stats functions */
void full_health(int* health) { *health = *(health+1); }
void update_max_health(int* health, int update) { (*(health+1))+=update; }
void update_stats(int* stats, int branch) { (*(stats+branch))++; }
void update_key(int* key_number, int update) { (*key_number)+=update; }

void display(Player p) {
  printf("\nhealth  : (%d/%d)\nattack  : %d\ndefense : %d\nkey_number : %d\nroom_id : %d\ncoordinates : (%d ; %d)\n\n",
  p.health[0],
  p.health[1],
  p.stats[0],
  p.stats[1],
  p.key_number,
  p.room_id,
  p.coordinate[0],
  p.coordinate[1]);
}