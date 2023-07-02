#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "SDL2/SDL.h"
#include "texture.h"

#define FRAME_DURATION 250 // ms
#define ANIMATIONS_AMOUNT 22

/* Amount of frames of every animation
Innanimated sprites have only 1 frame */
enum {
    FLOOR_ANIMATION_FRAMES = 1,
    VOID_ANIMATION_FRAMES = 1,
    WALL_ANIMATION_FRAMES = 1,
    DOOR_ANIMATION_FRAMES = 2,
    ATTACK_POWERUP_ANIMATION_FRAMES = 4,
    DEFENSE_POWERUP_ANIMATION_FRAMES = 4,
    HEALTH_POWERUP_ANIMATION_FRAMES = 4,
    KEY_ANIMATION_FRAMES = 4,
    POTION_ANIMATION_FRAMES = 4,
    FIRE_ANIMATION_FRAMES = 3,
    BLOOD1_ANIMATION_FRAMES = 1,
    BLOOD2_ANIMATION_FRAMES = 1,
    CRACKED_ANIMATION_FRAMES = 1,
    LIGHT_ANIMATION_FRAMES = 2,
    MONSTER_A_ANIMATION_FRAMES = 1,
    MONSTER_B_ANIMATION_FRAMES = 1,
    MONSTER_C_ANIMATION_FRAMES = 1,
    PLAYER_FRONT_ANIMATION_FRAMES = 1,
    PLAYER_BACK_ANIMATION_FRAMES = 1,
    PLAYER_LEFT_ANIMATION_FRAMES = 1,
    PLAYER_RIGHT_ANIMATION_FRAMES = 1,
    PORTAL_ANIMATION_FRAMES = 1,
};

typedef struct {
    Uint32 last_update;
    /* Used to stop all the animations */
    int update;
    /* actual animation state of every objects */
    int animation_states[ANIMATIONS_AMOUNT];
} Animator;

/* Return an animator struct pointer wich handle all animation states of the game */
Animator* create_animator();

/* Incresase the animation states depending on the time elapsed since the last step call */
void animation_step(Animator *animator, Texture *texture);

void toggle_animation(Animator *animator, int val);

void free_animator(Animator* animator);

#endif
