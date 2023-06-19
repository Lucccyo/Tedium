#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL2/SDL.h"

#define RECTS_AMOUNT 21
#define RECTS_UI_AMOUNT 8

/* Used to reduce code later when dealing with tilesets */
enum {
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

enum {
    RECT_ATTACK_ICON,
    RECT_DEFENSE_ICON,
    RECT_KEY_ICON,
    RECT_HEART_ICON,
    RECT_PAUSE_TEXT,
    RECT_RESTART_BUTTON,
    RECT_RESUME_BUTTON,
    RECT_QUIT_BUTTON,
};

/* Contains all SDL_Textures used in the game */
typedef struct {
    SDL_Texture *tileset;
    SDL_Texture *tileset_ui;
    /* Rects list */
    SDL_Rect rects[RECTS_AMOUNT];
    SDL_Rect rects_ui[RECTS_UI_AMOUNT];

    SDL_Texture *hearts_texture[5];
    SDL_Texture *background;
} Texture;

/* Load img as surface, transform them to textures and free priviously created surfaces */
Texture * load_textures(SDL_Renderer* renderer);


/* Return a SDL_Rect object created with his parameters */
SDL_Rect create_rect(int x, int y, int w, int h);

#endif
