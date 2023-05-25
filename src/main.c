#include <stdio.h>
#include <string.h>
#include <../include/SDL2/SDL.h>
#include "../include/renderer.h"
#include "../include/texture.h"
/* will be replaced with main game struct when it is done */
#include "../include/room.h"
#include "../include/floor.h"
#include "../include/player.h"
#include "../include/monster_hashtbl.h"
#include "../include/player.h"
#include "../include/animator.h"

int main() {
    SDL_Event event;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    Uint32 last_update = SDL_GetTicks();

    int quit = 0;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error inititializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Tedium", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Error creating window: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Error creating renderer: %s\n", SDL_GetError());
        return 1;
    }

    /* Temporary objects tests */
    Hashtbl * h = (Hashtbl*) malloc(sizeof(Hashtbl));
    reset_hashtbl(h);
    Floor *test_floor = create_floor("maze/floor1/", h);
    Room *target_room = test_floor->rooms[0];

    Player *player = create_player();
    player->coordinate[0] = WINDOW_WIDTH / 2;
    player->coordinate[1] = WINDOW_HEIGHT / 2;
    int speed = 10;

    /* input states array */
    int key_states[SDL_NUM_SCANCODES];
    for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
        key_states[i] = 0;
    }

    Texture * texture = load_textures(renderer);

    /* animator creation */
    Animator *animator = create_animator();

    while (!quit) {
        Uint32 current_time = SDL_GetTicks();
        float delta_time = (current_time - last_update) / 500.0f;

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
                break;
            }
            switch (event.type) {
                /* Look for a keypress */
                case SDL_KEYDOWN:
                    if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
                        if (target_room->neighbors[NORTH] != NULL) {
                            target_room = target_room->neighbors[NORTH];
                        }
                    } else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                        if (target_room->neighbors[SOUTH] != NULL) {
                            target_room = target_room->neighbors[SOUTH];
                        }
                    } else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                        if (target_room->neighbors[WEST] != NULL) {
                            target_room = target_room->neighbors[WEST];
                        }
                    } else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                        if (target_room->neighbors[EAST] != NULL) {
                            target_room = target_room->neighbors[EAST];
                        }
                    }
                    key_states[event.key.keysym.scancode] = 1;
                    SDL_Log("active : %u", event.key.keysym.scancode);
                    break;
                case SDL_KEYUP:
                    key_states[event.key.keysym.scancode] = 0;
                    SDL_Log("inactive : %u", event.key.keysym.scancode);
                    break;
                default:
                    break;
            }
        }
        
        /* movements tests will probably be moved to maze with
         a function that take a pointer to key_states 
         will need to use trigo to move correctly, actually, moving in diagonal is faster */
        if (key_states[SDL_SCANCODE_W]) 
        {
            player->coordinate[1] -= speed * delta_time;
            SDL_Log("player up");
        }
        if (key_states[SDL_SCANCODE_A])
        {
            player->coordinate[0] -= speed * delta_time;
            SDL_Log("player left");
        }
        if (key_states[SDL_SCANCODE_S])
        {
            player->coordinate[1] += speed * delta_time;
            SDL_Log("player down");
        }
        if (key_states[SDL_SCANCODE_D])
        {
            player->coordinate[0] += speed * delta_time;
            SDL_Log("player right");
        }

        last_update = SDL_GetTicks();

        /* drawing */
        SDL_RenderClear(renderer);
        animation_step(animator);
        draw_game(renderer, test_floor, target_room, player, texture, animator);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
