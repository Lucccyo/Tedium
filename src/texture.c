#include "texture.h"

Texture * load_textures(SDL_Renderer* renderer) {
    /* Load the tileset files into a texture */
    Texture * textures = (Texture *) malloc(sizeof(Texture));
    SDL_Surface *tileset_surface = SDL_LoadBMP("img/tileset.bmp");
    SDL_Surface *tileset_ui_surface = SDL_LoadBMP("img/ui_tileset.bmp");
    textures->tileset = SDL_CreateTextureFromSurface(renderer, tileset_surface);
    textures->tileset_ui = SDL_CreateTextureFromSurface(renderer, tileset_ui_surface);
    SDL_FreeSurface(tileset_surface);
    SDL_FreeSurface(tileset_ui_surface);

    /* Set each rect position to the first frame of each tile */
    textures->rects[RECT_WALL] = create_rect(0, 0, 24, 24);
    textures->rects[RECT_VOID] = create_rect(24, 0, 24, 24);
    textures->rects[RECT_FLOOR] = create_rect(48, 0, 24, 24);
    textures->rects[RECT_BLOOD1] = create_rect(72, 0, 24, 24);
    textures->rects[RECT_BLOOD2] = create_rect(96, 0, 24, 24);
    textures->rects[RECT_CRACKED] = create_rect(120, 0, 24, 24);
    textures->rects[RECT_FIRE] = create_rect(0, 24, 24, 24);
    textures->rects[RECT_KEY] = create_rect(0, 48, 24, 24);
    textures->rects[RECT_POTION] = create_rect(0, 72, 24, 24);
    textures->rects[RECT_ATTACK_POWERUP] = create_rect(0, 96, 24, 24);
    textures->rects[RECT_DEFENSE_POWERUP] = create_rect(0, 120, 24, 24);
    textures->rects[RECT_HEALTH_POWERUP] = create_rect(0, 144, 24, 24);
    textures->rects[RECT_PLAYER_FRONT] = create_rect(0, 168, 24, 24);
    textures->rects[RECT_PLAYER_BACK] = create_rect(48, 168, 24, 24);
    textures->rects[RECT_PLAYER_LEFT] = create_rect(96, 168, 24, 24);
    textures->rects[RECT_PLAYER_RIGHT] = create_rect(144, 168, 24, 24);
    textures->rects[RECT_MONSTER_A] = create_rect(0, 288, 24, 24);
    textures->rects[RECT_MONSTER_B] = create_rect(0, 312, 24, 24);
    textures->rects[RECT_MONSTER_C] = create_rect(0, 336, 24, 24);
    textures->rects[RECT_DOOR] = create_rect(0, 384, 24, 48);
    textures->rects[RECT_LIGHT] = create_rect(0, 432, 72, 72);
    textures->rects[RECT_PORTAL] = create_rect(48, 384, 24, 48);

    /* same with the ui rects */
    textures->rects_ui[RECT_ATTACK_ICON] = create_rect(0, 0, 12, 12);
    textures->rects_ui[RECT_DEFENSE_ICON] = create_rect(12, 0, 12, 12);
    textures->rects_ui[RECT_KEY_ICON] = create_rect(24, 0, 12, 12);
    textures->rects_ui[RECT_HEART_ICON] = create_rect(36, 0, 12, 12);
    textures->rects_ui[RECT_PAUSE_TEXT] = create_rect(0, 24, 240, 72);
    textures->rects_ui[RECT_RESTART_BUTTON] = create_rect(0, 96, 240, 72);
    textures->rects_ui[RECT_RESUME_BUTTON] = create_rect(0, 192, 240, 72);
    textures->rects_ui[RECT_QUIT_BUTTON] = create_rect(0, 288, 240, 72);

    /* load heart textures and main menu background (not in a tileset) */
     /* need to move to texture.c and use a tileset for all interface sprites */
    SDL_Surface *heart1_surface = SDL_LoadBMP("img/heart1.bmp");
    SDL_Surface *heart2_surface = SDL_LoadBMP("img/heart2.bmp");
    SDL_Surface *heart3_surface = SDL_LoadBMP("img/heart3.bmp");
    SDL_Surface *heart4_surface = SDL_LoadBMP("img/heart4.bmp");
    SDL_Surface *heart5_surface = SDL_LoadBMP("img/heart5.bmp");

    textures->hearts_texture[0] = SDL_CreateTextureFromSurface(renderer, heart1_surface);
    textures->hearts_texture[1] = SDL_CreateTextureFromSurface(renderer, heart2_surface);
    textures->hearts_texture[2] = SDL_CreateTextureFromSurface(renderer, heart3_surface);
    textures->hearts_texture[3] = SDL_CreateTextureFromSurface(renderer, heart4_surface);
    textures->hearts_texture[4] = SDL_CreateTextureFromSurface(renderer, heart5_surface);

    SDL_FreeSurface(heart1_surface);
    SDL_FreeSurface(heart2_surface);
    SDL_FreeSurface(heart3_surface);
    SDL_FreeSurface(heart4_surface);
    SDL_FreeSurface(heart5_surface);

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

void free_texture(Texture * texture){
    free(texture);
}