#ifndef TEXTURE_H
#define TEXTURE_H

#include <../include/SDL2/SDL.h>

#define RECTS_AMOUNT 15

enum {
    RECT_FLOOR,
    RECT_VOID,
    RECT_WALL,
    RECT_DOOR,
    RECT_PLAYER,
    RECT_ATTACK_POWERUP,
    RECT_DEFENSE_POWERUP,
    RECT_HEALTH_POWERUP,
    RECT_KEY,
    RECT_POTION,
    RECT_FIRE,
    RECT_BLOOD,
    RECT_SKULL,
    RECT_TORCH,
    RECT_LIGHT,
};

/* Contains all SDL_Textures used in the game */
typedef struct {
    SDL_Texture* tileset;

    /* Rects list */
    SDL_Rect rects[RECTS_AMOUNT];


    SDL_Texture* player;



    /* fire light animation test */
    SDL_Texture* fire_light_animation0;
    SDL_Texture* fire_light_animation1;


} Texture;

Texture * load_textures(SDL_Renderer* renderer);

SDL_Rect create_rect(int x, int y, int w, int h);


#endif
