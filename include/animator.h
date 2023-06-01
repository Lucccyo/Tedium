#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "SDL2/SDL.h"

#define FRAME_DURATION 250 // ms
#define ANIMATIONS_AMOUNT 6

enum {
    KEY_ANIMATION_FRAMES = 4,
    POTION_ANIMATION_FRAMES = 4,
    FIRE_ANIMATION_FRAMES = 3,
    FIRE_LIGHT_ANIMATION_FRAMES = 2,
    ATTACK_POWERUP_ANIMATION_FRAMES = 8,
    DEFENSE_POWERUP_ANIMATION_FRAMES = 6,
};

const int FRAME_AMOUNTS[ANIMATIONS_AMOUNT];

typedef enum {
    KEY_STATE,
    POTION_STATE,
    FIRE_STATE,
    FIRE_LIGHT_STATE,
    ATTACK_POWERUP_STATE,
    DEFENSE_POWERUP_STATE,
} AnimationStates;

typedef struct {
    Uint32 last_update;
    int update;
    /* actual animation state of every objects */
    int animation_states[ANIMATIONS_AMOUNT];
    // int animation_frames[ANIMATIONS_AMOUNT];
} Animator;

Animator* create_animator();

void animation_step(Animator *animator);

void activate_animation(Animator *animator);

void deactivate_animation(Animator *animator);

#endif