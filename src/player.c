#include <stdio.h>
#include "../include/player.h"

// c'est bien d'avoir une fonction free pour la fin ou ça sert a rien?
// maniere plus simple de faire en une fois le create des tableaux?
// est-ce que je mets des erreurs quand les acces sont interdits?

/* initialize a player */
Player * create() {
  Player * p = (Player*) malloc(sizeof(Player));
  p->health[0] = 10; p->health[1] = 10;
  p->stats[0] = 2; p->stats[1] = 1;
  p->key_number = 0;
  p->room_id = 1;
  p->coordinate[0] = 0; p->coordinate[1] = 0;
  return p;
}

/* moving functions */
void go_left  (int* coordinate) { (*coordinate)--; }
void go_right (int* coordinate) { (*coordinate)++; }
void go_up   (int* coordinate) { (*(coordinate+1))--; }
void go_down  (int* coordinate) { (*(coordinate+1))++; }

/* stats functions */
void full_health(int* health) { *health = *(health+1); }
void update_max_health(int* health, int update) { (*(health+1))+=update; }
void update_stats(int* stats, int branch) { (*(stats+branch))++; }
void update_key(int* key_number, int update) { (*key_number)+=update; }

/* display debug */
void display(Player * p) {
  printf("\nhealth  : (%d/%d)\nattack  : %d\ndefense : %d\nkey_number : %d\nroom_id : %d\ncoordinates : (%d;%d)\n\n",
  p->health[0],
  p->health[1],
  p->stats[0],
  p->stats[1],
  p->key_number,
  p->room_id,
  p->coordinate[0],
  p->coordinate[1]);
}
