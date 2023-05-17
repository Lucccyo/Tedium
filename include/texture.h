#ifndef TEXTURE_H
#define TEXTURE_H

#include <../include/SDL2/SDL.h>

/* Contains all SDL_Textures used in the game */
typedef struct {
    SDL_Texture* tileset;
    SDL_Texture* floor;
    SDL_Texture* wall;
    SDL_Texture* heart;
} Texture;

Texture load_textures(SDL_Renderer* renderer);

#endif
