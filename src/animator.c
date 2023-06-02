#include "animator.h"

const int FRAME_AMOUNTS[ANIMATIONS_AMOUNT] = {
    FLOOR_ANIMATION_FRAMES,
    VOID_ANIMATION_FRAMES,
    WALL_ANIMATION_FRAMES,
    DOOR_ANIMATION_FRAMES,
    PLAYER_ANIMATION_FRAMES,
    ATTACK_POWERUP_ANIMATION_FRAMES,
    DEFENSE_POWERUP_ANIMATION_FRAMES,
    HEALTH_POWERUP_ANIMATION_FRAMES,
    KEY_ANIMATION_FRAMES,
    POTION_ANIMATION_FRAMES,
    FIRE_ANIMATION_FRAMES,
    BLOOD_ANIMATION_FRAMES,
    SKULL_ANIMATION_FRAMES,
    TORCH_ANIMATION_FRAMES,
    LIGHT_ANIMATION_FRAMES,
};

Animator* create_animator() {
    Animator *animator = (Animator*) malloc(sizeof(Animator));
    animator->update = 1;
    animator->last_update = SDL_GetTicks();
    for (int i = 0; i < ANIMATIONS_AMOUNT; i++) {
        animator->animation_states[i] = 0;
    }
    return animator;
}

void animation_step(Animator *animator, Texture *texture) {
    if (animator->update == 0) { return; }

    Uint32 current_time = SDL_GetTicks();
    float delta_time = (current_time - animator->last_update);
    if (delta_time < FRAME_DURATION) { return; }
    for (int i = 0; i < ANIMATIONS_AMOUNT; i++) {
        animator->animation_states[i] += 1;
        texture->rects[i].x += texture->rects[i].w;
        if (animator->animation_states[i] >= FRAME_AMOUNTS[i]) {
            animator->animation_states[i] = 0;
            texture->rects[i].x -= texture->rects[i].w * (FRAME_AMOUNTS[i]);
        }
    }
    animator->last_update = current_time;
}

void activate_animation(Animator *animator) {
    animator->update = 1;
}

void deactivate_animation(Animator *animator) {
    animator->update = 0;
}