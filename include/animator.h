#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "SDL2/SDL.h"
#include "texture.h"

#define FRAME_DURATION 250 // ms
#define ANIMATIONS_AMOUNT 15

enum {
    FLOOR_ANIMATION_FRAMES = 1,
    VOID_ANIMATION_FRAMES = 1,
    WALL_ANIMATION_FRAMES = 1,
    DOOR_ANIMATION_FRAMES = 1,
    PLAYER_ANIMATION_FRAMES = 1,
    ATTACK_POWERUP_ANIMATION_FRAMES = 8,
    DEFENSE_POWERUP_ANIMATION_FRAMES = 8,
    HEALTH_POWERUP_ANIMATION_FRAMES = 1,
    KEY_ANIMATION_FRAMES = 4,
    POTION_ANIMATION_FRAMES = 4,
    FIRE_ANIMATION_FRAMES = 3,
    BLOOD_ANIMATION_FRAMES = 1,
    SKULL_ANIMATION_FRAMES = 1,
    TORCH_ANIMATION_FRAMES = 1,
    LIGHT_ANIMATION_FRAMES = 2,
};

const int FRAME_AMOUNTS[ANIMATIONS_AMOUNT];

typedef enum {
    FLOOR_STATE,
    VOID_STATE,
    WALL_STATE,
    DOOR_STATE,
    PLAYER_STATE,
    ATTACK_POWERUP_STATE,
    DEFENSE_POWERUP_STATE,
    HEALTH_POWERUP_STATE,
    KEY_STATE,
    POTION_STATE,
    FIRE_STATE,
    BLOOD_STATE,
    SKULL_STATE,
    TORCH_STATE,
    LIGHT_STATE,
} AnimationStates;

typedef struct {
    Uint32 last_update;
    int update;
    /* actual animation state of every objects */
    int animation_states[ANIMATIONS_AMOUNT];
    // int animation_frames[ANIMATIONS_AMOUNT];
} Animator;

Animator* create_animator();

void animation_step(Animator *animator, Texture *texture);

void activate_animation(Animator *animator);

void deactivate_animation(Animator *animator);

#endif