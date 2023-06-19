#ifndef RENDERER_H
#define RENDERER_H

#include "SDL2/SDL.h"
#include "animator.h"
#include "texture.h"
#include "floor.h"
#include "room.h"
#include "player.h"
#include "monster.h"
#include "player.h"

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720
#define TILE_SIZE 24
#define DRAW_TILE_SIZE 24
#define LIGHT_SIZE 72

typedef enum {
    EMPTY = '#',
    FLOOR = ' ',
    EXIT = '?',
    KEY = '!',
    POTION = 'Z',
    DOOR = 'o',
    ATTACK_POWERUP = '1',
    DEFENSE_POWERUP = '2',
    HEALTH_POWERUP = '3',
    MONSTER_A = 'A',
    MONSTER_B = 'B',
    MONSTER_C = 'C',
    PORTAL = '@'
} Tiles;

typedef enum {
    CRACKED = '4',
    BLOOD1 = '5',
    BLOOD2 = '6',
    FIRE = '7'
} Decoration;



/* Call all the draw function in correct order */
/* Probably going to replace all args with a maze struct once it's done */
void draw_game(SDL_Renderer* renderer, Floor *floor, Room *target_room, Player *player, Texture *texture);

/* Draw the provided room on the screen */
void draw_room(SDL_Renderer* renderer, Room *room, Texture *texture);

/* Draw light.bmp on the provided coordinates */
void draw_lights(SDL_Renderer* renderer, Room *room, Texture *texture);

/* Draw the minimap of the floor in the top right corner of the screen */
void draw_minimap(SDL_Renderer* renderer, Floor *floor, Room *target_room);

/* Draw the provided monster on the screen */
void draw_monster(SDL_Renderer *renderer, int x, int y, char monster_type, Texture *texture);

/* Draw the player (test sprite actually) */
void draw_player(SDL_Renderer *renderer, Player *player, Texture *texture);

/* Draw all the doors of the room (must be caled after draw_player to prevent overlap) */
void draw_doors(SDL_Renderer *renderer, Room *room, Texture *texture);

#endif
