#include "../include/texture.h"

Texture * load_textures(SDL_Renderer* renderer) {
    /* Load the tileset.bmp file into a texture */
    Texture * textures = (Texture *) malloc(sizeof(Texture));
    SDL_Surface *tileset_surface = SDL_LoadBMP("img/tileset.bmp");
    textures->tileset = SDL_CreateTextureFromSurface(renderer, tileset_surface);
    SDL_FreeSurface(tileset_surface);

    /* Set each rect position to the first frame of each tile */
    textures->rects[RECT_FLOOR] = create_rect(0, 0, 24, 24);
    textures->rects[RECT_VOID] = create_rect(24, 0, 24, 24);
    textures->rects[RECT_WALL] = create_rect(48, 0, 24, 24);
    textures->rects[RECT_DOOR] = create_rect(72, 0, 24, 24);
    textures->rects[RECT_PLAYER] = create_rect(0, 24, 24, 24);
    textures->rects[RECT_ATTACK_POWERUP] = create_rect(0, 48, 24, 24);
    textures->rects[RECT_DEFENSE_POWERUP] = create_rect(0, 72, 24, 24);
    textures->rects[RECT_HEALTH_POWERUP] = create_rect(0, 96, 24, 24);
    textures->rects[RECT_KEY] = create_rect(0, 120, 24, 24);
    textures->rects[RECT_POTION] = create_rect(0, 144, 24, 24);
    textures->rects[RECT_FIRE] = create_rect(0, 168, 24, 24);
    textures->rects[RECT_BLOOD] = create_rect(0, 192, 24, 24);
    textures->rects[RECT_SKULL] = create_rect(0, 216, 24, 24);
    textures->rects[RECT_TORCH] = create_rect(0, 240, 24, 24);
    textures->rects[RECT_LIGHT] = create_rect(0, 264, 72, 72);

    return textures;
}

SDL_Rect create_rect(int x, int y, int w, int h) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    return rect;
}
