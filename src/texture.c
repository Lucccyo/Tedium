#include "texture.h"

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
    textures->rects[RECT_DOOR] = create_rect(0, 408, 24, 48);
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
    textures->rects[RECT_MONSTER_A] = create_rect(0, 336, 24, 48);
    textures->rects[RECT_MONSTER_B] = create_rect(48, 336, 24, 48);
    textures->rects[RECT_MONSTER_C] = create_rect(96, 336, 24, 48);
    textures->rects[RECT_PLAYER_FRONT] = create_rect(96, 0, 24, 48);
    textures->rects[RECT_PLAYER_BACK] = create_rect(120, 0, 24, 48);
    textures->rects[RECT_PLAYER_LEFT] = create_rect(144, 0, 24, 48);
    textures->rects[RECT_PLAYER_RIGHT] = create_rect(168, 0, 24, 48);

    /* gui textures */
    SDL_Surface *menu_asset = SDL_LoadBMP("gfx/menu.bmp");
    SDL_Surface *close_btn_asset = SDL_LoadBMP("gfx/close_btn.bmp");
    SDL_Surface *quit_btn_asset = SDL_LoadBMP("gfx/quit_btn.bmp");
    SDL_Surface *restart_btn_asset = SDL_LoadBMP("gfx/restart_btn.bmp");
    SDL_Surface *resume_btn_asset = SDL_LoadBMP("gfx/resume_btn.bmp");
    SDL_Surface *credits_btn_asset = SDL_LoadBMP("gfx/credits_btn.bmp");

    textures->menu = SDL_CreateTextureFromSurface(renderer, menu_asset);
    textures->close = SDL_CreateTextureFromSurface(renderer, close_btn_asset);
    textures->quit = SDL_CreateTextureFromSurface(renderer, quit_btn_asset);
    textures->restart = SDL_CreateTextureFromSurface(renderer, restart_btn_asset);
    textures->resume = SDL_CreateTextureFromSurface(renderer, resume_btn_asset);
    textures->credits = SDL_CreateTextureFromSurface(renderer, credits_btn_asset);

    SDL_FreeSurface(menu_asset);
    SDL_FreeSurface(close_btn_asset);
    SDL_FreeSurface(quit_btn_asset);
    SDL_FreeSurface(restart_btn_asset);
    SDL_FreeSurface(resume_btn_asset);
    SDL_FreeSurface(credits_btn_asset);
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
