#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL2/SDL.h"

#define RECTS_AMOUNT 21

enum
{
    RECT_FLOOR,
    RECT_VOID,
    RECT_WALL,
    RECT_DOOR,
    RECT_ATTACK_POWERUP,
    RECT_DEFENSE_POWERUP,
    RECT_HEALTH_POWERUP,
    RECT_KEY,
    RECT_POTION,
    RECT_FIRE,
    RECT_BLOOD1,
    RECT_BLOOD2,
    RECT_CRACKED,
    RECT_LIGHT,
    RECT_MONSTER_A,
    RECT_MONSTER_B,
    RECT_MONSTER_C,
    RECT_PLAYER_FRONT,
    RECT_PLAYER_BACK,
    RECT_PLAYER_LEFT,
    RECT_PLAYER_RIGHT,
};

/* Contains all SDL_Textures used in the game */
typedef struct
{
    SDL_Texture *tileset;
    /* Rects list */
    SDL_Rect rects[RECTS_AMOUNT];

    SDL_Texture *menu;
    SDL_Texture *close;
    SDL_Texture *quit;
    SDL_Texture *restart;
    SDL_Texture *resume;
    SDL_Texture *credits;
} Texture;

Texture *load_textures(SDL_Renderer *renderer);

SDL_Rect create_rect(int x, int y, int w, int h);

#endif
