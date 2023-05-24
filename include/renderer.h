#ifndef RENDERER_H
#define RENDERER_H

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720
#define TILE_SIZE 24
#define DRAW_TILE_SIZE 24
#define LIGHT_SIZE 120

#include "../include/SDL2/SDL.h"
#include "../include/texture.h"
#include "../include/floor.h"
#include "../include/room.h"
#include "../include/player.h"
#include "../include/monster.h"
#include "../include/player.h"

/* Call all the draw function in correct order */
/* Probably going to replace all args with a maze struct once it's done */
void draw_game(SDL_Renderer* renderer, Floor *floor, Room *target_room, Player *player, Texture * texture);

/* Draw the provided room on the screen */
void draw_room(SDL_Renderer* renderer, Room *room, Texture * texture);

/* Draw light.bmp on the provided coordinates */
void draw_light(SDL_Renderer* renderer, int x, int y);

/* Draw the minimap of the floor in the top right corner of the screen */
void draw_minimap(SDL_Renderer* renderer, Floor *floor, Room *target_room);

/* Draw the player (test sprite actually) */
void draw_player(SDL_Renderer *renderer, Player *player, Texture * texture);

#endif
