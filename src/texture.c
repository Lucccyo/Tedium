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
    SDL_Surface *health_powerup_image = SDL_LoadBMP("img/health_powerup.bmp");
    SDL_Surface *attack_powerup_image = SDL_LoadBMP("img/attack_powerup.bmp");
    SDL_Surface *defense_powerup_image = SDL_LoadBMP("img/defense_powerup.bmp");
    SDL_Surface *key_image = SDL_LoadBMP("img/key.bmp");
    SDL_Surface *player_image = SDL_LoadBMP("img/player.bmp");
    SDL_Surface *skull_image = SDL_LoadBMP("img/skull.bmp");
    SDL_Surface *torch_image = SDL_LoadBMP("img/torch.bmp");
    SDL_Surface *light_image = SDL_LoadBMP("img/light.bmp");
    SDL_Surface *potion_image = SDL_LoadBMP("img/potion.bmp");
    SDL_Surface *blood_image = SDL_LoadBMP("img/blood.bmp");
    /* potion anim test */
    SDL_Surface *potion_animation0_image = SDL_LoadBMP("img/potiontest/sh_potion1.bmp");
    SDL_Surface *potion_animation1_image = SDL_LoadBMP("img/potiontest/sh_potion2.bmp");
    SDL_Surface *potion_animation2_image = SDL_LoadBMP("img/potiontest/sh_potion3.bmp");
    SDL_Surface *potion_animation3_image = SDL_LoadBMP("img/potiontest/sh_potion4.bmp");
    /* fire anim test */
    SDL_Surface *fire_animation0_image = SDL_LoadBMP("img/fire_0.bmp");
    SDL_Surface *fire_animation1_image = SDL_LoadBMP("img/fire_1.bmp");
    SDL_Surface *fire_animation2_image = SDL_LoadBMP("img/fire_2.bmp");
    /* fire light anim test */
    SDL_Surface *fire_light_animation0_image = SDL_LoadBMP("img/fire_light_0.bmp");
    SDL_Surface *fire_light_animation1_image = SDL_LoadBMP("img/fire_light_1.bmp");
    /* key anim test */
    SDL_Surface *key_animation0_image = SDL_LoadBMP("img/clee1.bmp");
    SDL_Surface *key_animation1_image = SDL_LoadBMP("img/clee2.bmp");
    SDL_Surface *key_animation2_image = SDL_LoadBMP("img/clee3.bmp");
    SDL_Surface *key_animation3_image = SDL_LoadBMP("img/clee4.bmp");

    textures->floor = SDL_CreateTextureFromSurface(renderer, floor_image);
    textures->wall = SDL_CreateTextureFromSurface(renderer, wall_image);
    textures->noir = SDL_CreateTextureFromSurface(renderer, noir_image);
    textures->health_powerup = SDL_CreateTextureFromSurface(renderer, health_powerup_image);
    textures->attack_powerup = SDL_CreateTextureFromSurface(renderer, attack_powerup_image);
    textures->defense_powerup = SDL_CreateTextureFromSurface(renderer, defense_powerup_image);
    textures->key = SDL_CreateTextureFromSurface(renderer, key_image);
    textures->player = SDL_CreateTextureFromSurface(renderer, player_image);
    textures->skull = SDL_CreateTextureFromSurface(renderer, skull_image);
    textures->torch = SDL_CreateTextureFromSurface(renderer, torch_image);
    textures->light = SDL_CreateTextureFromSurface(renderer, light_image);
    textures->potion = SDL_CreateTextureFromSurface(renderer, potion_image);
    textures->blood = SDL_CreateTextureFromSurface(renderer, blood_image);
    /* potion anim test */
    textures->potion_animation0 = SDL_CreateTextureFromSurface(renderer, potion_animation0_image);
    textures->potion_animation1 = SDL_CreateTextureFromSurface(renderer, potion_animation1_image);
    textures->potion_animation2 = SDL_CreateTextureFromSurface(renderer, potion_animation2_image);
    textures->potion_animation3 = SDL_CreateTextureFromSurface(renderer, potion_animation3_image);
    /* fire anim test */
    textures->fire_animation0 = SDL_CreateTextureFromSurface(renderer, fire_animation0_image);
    textures->fire_animation1 = SDL_CreateTextureFromSurface(renderer, fire_animation1_image);
    textures->fire_animation2 = SDL_CreateTextureFromSurface(renderer, fire_animation2_image);
    /* fire light anim test */
    textures->fire_light_animation0 = SDL_CreateTextureFromSurface(renderer, fire_light_animation0_image);
    textures->fire_light_animation1 = SDL_CreateTextureFromSurface(renderer, fire_light_animation1_image);
    /* key anim test */
    textures->key_animation0 = SDL_CreateTextureFromSurface(renderer, key_animation0_image);
    textures->key_animation1 = SDL_CreateTextureFromSurface(renderer, key_animation1_image);
    textures->key_animation2 = SDL_CreateTextureFromSurface(renderer, key_animation2_image);
    textures->key_animation3 = SDL_CreateTextureFromSurface(renderer, key_animation3_image);

    /* set texture blend mode for all textures */
    SDL_SetTextureBlendMode(textures->light, SDL_BLENDMODE_ADD);

    SDL_FreeSurface(floor_image);
    SDL_FreeSurface(wall_image);
    SDL_FreeSurface(noir_image);
    SDL_FreeSurface(health_powerup_image);
    SDL_FreeSurface(attack_powerup_image);
    SDL_FreeSurface(defense_powerup_image);
    SDL_FreeSurface(key_image);
    SDL_FreeSurface(player_image);
    SDL_FreeSurface(skull_image);
    SDL_FreeSurface(torch_image);
    SDL_FreeSurface(light_image);
    SDL_FreeSurface(potion_image);
    SDL_FreeSurface(blood_image);
    /* potion anim test */
    SDL_FreeSurface(potion_animation0_image);
    SDL_FreeSurface(potion_animation1_image);
    SDL_FreeSurface(potion_animation2_image);
    SDL_FreeSurface(potion_animation3_image);
    /* fire anim test */
    SDL_FreeSurface(fire_animation0_image);
    SDL_FreeSurface(fire_animation1_image);
    SDL_FreeSurface(fire_animation2_image);
    /* fire light anim test */
    SDL_FreeSurface(fire_light_animation0_image);
    SDL_FreeSurface(fire_light_animation1_image);
    /* key anim test */
    SDL_FreeSurface(key_animation0_image);
    SDL_FreeSurface(key_animation1_image);
    SDL_FreeSurface(key_animation2_image);
    SDL_FreeSurface(key_animation3_image);

    return textures;
}
