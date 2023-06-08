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
    sounds->heal = Mix_LoadWAV_RW(SDL_RWFromFile("audio/sfx/heal.wav", "rb"), 1);
    sounds->open_door = Mix_LoadWAV_RW(SDL_RWFromFile("audio/sfx/open_door.wav", "rb"), 1);
    sounds->key_pickup = Mix_LoadWAV_RW(SDL_RWFromFile("audio/sfx/key_pickup.wav", "rb"), 1);
    sounds->powerup_pickup = Mix_LoadWAV_RW(SDL_RWFromFile("audio/sfx/powerup_pickup.wav", "rb"), 1);

    return sounds;
}

void play_music(Sound *sound) {
    if (Mix_PlayingMusic() == 0) {
        sound->current_music += 1;
        if (sound->current_music >= MUSICS_AMOUNT) { sound->current_music = 0; }
        Mix_PlayMusic(sound->musics[sound->current_music], 0);
    }
}


/* Maybe just call Mix_PlayChannel instead of making a useless function each time ... */
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

void play_heal_sound(Sound *sound) {
    Mix_PlayChannel(-1, sound->heal, 0);
}

void play_open_door_sound(Sound *sound) {
    Mix_PlayChannel(-1, sound->open_door, 0);
}

void play_key_pickup_sound(Sound *sound) {
    Mix_PlayChannel(-1, sound->key_pickup, 0);
}

void play_powerup_pickup_sound(Sound *sound) {
    Mix_PlayChannel(-1, sound->powerup_pickup, 0);
}
