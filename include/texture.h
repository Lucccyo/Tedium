#ifndef TEXTURE_H
#define TEXTURE_H

#include <../include/SDL2/SDL.h>

/* Contains all SDL_Textures used in the game */
typedef struct {
    SDL_Texture* tileset;

    SDL_Texture* floor;
    SDL_Texture* wall;
    SDL_Texture* noir;
    SDL_Texture* defense_powerup;
    SDL_Texture* health_powerup;
    SDL_Texture* key;
    SDL_Texture* potion;
    SDL_Texture* player;
    SDL_Texture* skull;
    SDL_Texture* torch;
    SDL_Texture* light;
    SDL_Texture* blood;

    /* potion animation test */
    SDL_Texture* potion_animation0;
    SDL_Texture* potion_animation1;
    SDL_Texture* potion_animation2;
    SDL_Texture* potion_animation3;

    /* fire animation test */
    SDL_Texture* fire_animation0;
    SDL_Texture* fire_animation1;
    SDL_Texture* fire_animation2;

    /* fire light animation test */
    SDL_Texture* fire_light_animation0;
    SDL_Texture* fire_light_animation1;

    /* key animation test */
    SDL_Texture* key_animation0;
    SDL_Texture* key_animation1;
    SDL_Texture* key_animation2;
    SDL_Texture* key_animation3;

    /* attack power up animation test */
    SDL_Texture* attack_powerup_animation0;
    SDL_Texture* attack_powerup_animation1;
    SDL_Texture* attack_powerup_animation2;
    SDL_Texture* attack_powerup_animation3;
    SDL_Texture* attack_powerup_animation4;
    SDL_Texture* attack_powerup_animation5;
    SDL_Texture* attack_powerup_animation6;
    SDL_Texture* attack_powerup_animation7;

    /* defense power up animation test */
    SDL_Texture* defense_powerup_animation0;
    SDL_Texture* defense_powerup_animation1;
    SDL_Texture* defense_powerup_animation2;
    SDL_Texture* defense_powerup_animation3;
    SDL_Texture* defense_powerup_animation4;
    SDL_Texture* defense_powerup_animation5;
    SDL_Texture* defense_powerup_animation6;
    SDL_Texture* defense_powerup_animation7;

} Texture;

Texture * load_textures(SDL_Renderer* renderer);

#endif
