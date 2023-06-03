#include "audio.h"

Sound *create_sounds() {
    Sound *sounds = malloc(sizeof(Sound));

    /* Loading musics */
    sounds->musics[0] = Mix_LoadMUS("audio/music/theme_1.wav");
    sounds->musics[1] = Mix_LoadMUS("audio/music/theme_2.wav");

    /* Loading sounds */
    sounds->attacks[0] = Mix_LoadWAV_RW(SDL_RWFromFile("audio/sfx/attack_1.wav", "rb"), 1);
    sounds->attacks[1] = Mix_LoadWAV_RW(SDL_RWFromFile("audio/sfx/attack_2.wav", "rb"), 1);
    sounds->attacks[2] = Mix_LoadWAV_RW(SDL_RWFromFile("audio/sfx/attack_3.wav", "rb"), 1);
    sounds->player_death = Mix_LoadWAV_RW(SDL_RWFromFile("audio/sfx/player_death.wav", "rb"), 1);
    sounds->enemy_death = Mix_LoadWAV_RW(SDL_RWFromFile("audio/sfx/enemy_death.wav", "rb"), 1);

    return sounds;
}

void sound_step(Sound *sound) {
    if (Mix_PlayingMusic() == 0) {
        play_music(sound);
    }
}

void play_music(Sound *sound) {
    sound->current_music += 1;
    if (sound->current_music >= MUSICS_AMOUNT) { sound->current_music = 0; }
    Mix_PlayMusic(sound->musics[sound->current_music], 0);
}

void play_attack_sound(Sound *sound) {
    int random = rand() % ATTACKS_AMOUNT;
    Mix_PlayChannel(-1, sound->attacks[random], 0);
}

void play_player_death_sound(Sound *sound) {
    Mix_PlayChannel(-1, sound->player_death, 0);
}

void play_enemy_death_sound(Sound *sound) {
    Mix_PlayChannel(-1, sound->enemy_death, 0);
}