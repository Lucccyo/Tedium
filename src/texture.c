#include "../include/texture.h"

Texture * load_textures(SDL_Renderer* renderer) {
    /* need complete rework, only one texture will be used in the future */

    Texture * textures = (Texture *) malloc(sizeof(Texture));
    SDL_Surface *tileset_surface = SDL_LoadBMP("img/floor.bmp");

    Uint32 colorkey = SDL_MapRGB(tileset_surface->format, 0, 255, 255);
    SDL_SetColorKey(tileset_surface, SDL_TRUE, colorkey);

    textures->tileset = SDL_CreateTextureFromSurface(renderer, tileset_surface);

    SDL_FreeSurface(tileset_surface);

    /* everything after must be removed once we use a tilset */
    SDL_Surface *floor_image = SDL_LoadBMP("img/floor.bmp");
    SDL_Surface *wall_image = SDL_LoadBMP("img/wall.bmp");
    SDL_Surface *noir_image = SDL_LoadBMP("img/noir.bmp");
    SDL_Surface *heart_image = SDL_LoadBMP("img/heart.bmp");
    SDL_Surface *sword_image = SDL_LoadBMP("img/sword.bmp");
    SDL_Surface *shield_image = SDL_LoadBMP("img/shield.bmp");
    SDL_Surface *key_image = SDL_LoadBMP("img/key.bmp");
    SDL_Surface *player_image = SDL_LoadBMP("img/player.bmp");

    textures->floor = SDL_CreateTextureFromSurface(renderer, floor_image);
    textures->wall = SDL_CreateTextureFromSurface(renderer, wall_image);
    textures->noir = SDL_CreateTextureFromSurface(renderer, noir_image);
    textures->heart = SDL_CreateTextureFromSurface(renderer, heart_image);
    textures->sword = SDL_CreateTextureFromSurface(renderer, sword_image);
    textures->shield = SDL_CreateTextureFromSurface(renderer, shield_image);
    textures->key = SDL_CreateTextureFromSurface(renderer, key_image);
    textures->player = SDL_CreateTextureFromSurface(renderer, player_image);

    SDL_FreeSurface(floor_image);
    SDL_FreeSurface(wall_image);
    SDL_FreeSurface(noir_image);
    SDL_FreeSurface(heart_image);
    SDL_FreeSurface(sword_image);
    SDL_FreeSurface(shield_image);
    SDL_FreeSurface(key_image);
    SDL_FreeSurface(player_image);

    return textures;
}
