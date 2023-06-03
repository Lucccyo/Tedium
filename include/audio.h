#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_rwops.h>

#define MUSICS_AMOUNT 2
#define ATTACKS_AMOUNT 3

typedef struct Sound {
    /* Loading musics */
    Mix_Music *musics[2];
    int current_music;

    /* Loading sounds */
    Mix_Chunk *attacks[3];
    Mix_Chunk *player_death;
    Mix_Chunk *enemy_death;
    Mix_Chunk *heal;

} Sound;

Sound *create_sounds();
void play_music(Sound *sound);
void play_attack_sound(Sound *sound);
void play_player_death_sound(Sound *sound);
void play_enemy_death_sound(Sound *sound);
void play_heal_sound(Sound *sound);

#endif
