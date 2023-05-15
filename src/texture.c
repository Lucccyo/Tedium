#include "../include/texture.h"   
   
Texture load_textures(SDL_Renderer* renderer) {
    Texture textures;
    SDL_Surface *floor_image = SDL_LoadBMP("img/floor.bmp");
    SDL_Surface *wall_image = SDL_LoadBMP("img/wall.bmp");
    SDL_Surface *heart_image = SDL_LoadBMP("img/heart.bmp");

    /* Replacement of cyan with tranparent color */
    Uint32 colorkey = SDL_MapRGB(heart_image->format, 0, 255, 255);
    SDL_SetColorKey(heart_image, SDL_TRUE, colorkey);

    textures.floor = SDL_CreateTextureFromSurface(renderer, floor_image);
    textures.wall = SDL_CreateTextureFromSurface(renderer, wall_image);
    textures.heart = SDL_CreateTextureFromSurface(renderer, heart_image);

    SDL_FreeSurface(floor_image);
    SDL_FreeSurface(wall_image);
    SDL_FreeSurface(heart_image);
    return textures;
}
