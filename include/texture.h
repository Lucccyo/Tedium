#ifndef TEXTURE_H
#define TEXTURE_H

#include <../include/SDL2/SDL.h>

/* Contains all SDL_Textures used in the game */
typedef struct {
    SDL_Texture* tileset;
    SDL_Texture* floor;
    SDL_Texture* wall;
    SDL_Texture* sword;
    SDL_Texture* shield;
    SDL_Texture* heart;
    SDL_Texture* key;

} Texture;

Texture load_textures(SDL_Renderer* renderer);

#endif
