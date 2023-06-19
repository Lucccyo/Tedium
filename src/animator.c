#include "animator.h"

/* Fill an array with all the amounts of frames per animations to reduce code later */
const int FRAME_AMOUNTS[ANIMATIONS_AMOUNT] = {
    FLOOR_ANIMATION_FRAMES,
    VOID_ANIMATION_FRAMES,
    WALL_ANIMATION_FRAMES,
    DOOR_ANIMATION_FRAMES,
    ATTACK_POWERUP_ANIMATION_FRAMES,
    DEFENSE_POWERUP_ANIMATION_FRAMES,
    HEALTH_POWERUP_ANIMATION_FRAMES,
    KEY_ANIMATION_FRAMES,
    POTION_ANIMATION_FRAMES,
    FIRE_ANIMATION_FRAMES,
    BLOOD1_ANIMATION_FRAMES,
    BLOOD2_ANIMATION_FRAMES,
    CRACKED_ANIMATION_FRAMES,
    LIGHT_ANIMATION_FRAMES,
    MONSTER_A_ANIMATION_FRAMES,
    MONSTER_B_ANIMATION_FRAMES,
    MONSTER_C_ANIMATION_FRAMES,
    PLAYER_FRONT_ANIMATION_FRAMES,
    PLAYER_BACK_ANIMATION_FRAMES,
    PLAYER_LEFT_ANIMATION_FRAMES,
    PLAYER_RIGHT_ANIMATION_FRAMES,
    PORTAL_ANIMATION_FRAMES,
};

Animator* create_animator() {
    Animator *animator = (Animator*) malloc(sizeof(Animator));
    /* Activate animations */
    animator->update = 1;
    animator->last_update = SDL_GetTicks();
    /* Set all animatiobs states to 0 */
    for (int i = 0; i < ANIMATIONS_AMOUNT; i++) {
        animator->animation_states[i] = 0;
    }
    return animator;
}

void animation_step(Animator *animator, Texture *texture) {
    /* If the time elapsed is not enought, stop the step function here */
    if (animator->update == 0) { return; }

    Uint32 current_time = SDL_GetTicks();
    float delta_time = (current_time - animator->last_update);
    if (delta_time < FRAME_DURATION) { return; }
    /* Increment all states by 1 and reset them if the last frame is reached */
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

void toggle_animation(Animator *animator, int val) {
    animator->update = val;
}
