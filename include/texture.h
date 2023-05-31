#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL2/SDL.h"

/* Contains all SDL_Textures used in the game */
typedef struct {
    SDL_Texture* tileset;
    SDL_Texture* floor;
    SDL_Texture* wall;
    SDL_Texture* noir;
    SDL_Texture* sword;
    SDL_Texture* shield;
    SDL_Texture* heart;
    SDL_Texture* key;
    SDL_Texture* player;
    SDL_Texture* monster_a;
    SDL_Texture* monster_b;
    SDL_Texture* monster_c;
    SDL_Texture* door;

} Texture;

Texture * load_textures(SDL_Renderer* renderer);

#endif
