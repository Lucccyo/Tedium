#include <stdio.h>
#include "SDL2/SDL.h"
#include "../include/player.h"

/* initialize a player */
Player* init_player() {
  Player *p = malloc(sizeof(Player));
  return p;
} 

void reset_player(Player * p) {
  p->health[0] = 10; p->health[1] = 10;
  p->stats[0] = 2; p->stats[1] = 1;
  p->key_number = 0;
  p->room_id = 1;
  p->coordinate[0] = 0; p->coordinate[1] = 0;
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
void draw_player(SDL_Renderer *renderer, Player *player, SDL_Texture *texture) {
  SDL_Rect newRect = {player->coordinate[0], player->coordinate[1], 24, 24};
  SDL_RenderCopy(renderer, texture, NULL, &newRect);
}

void display_player(Player * p)
{
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
