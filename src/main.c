#include <stdio.h>
#include <string.h>
#include <../include/SDL2/SDL.h>
#include "../include/renderer.h"
#include "../include/texture.h"
/* will be replaced with main game struct when it is done */
#include "../include/room.h"
#include "../include/floor.h"
#include "../include/monster_hashtbl.h"

int main() {
    SDL_Event event;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    int quit = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
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

    Hashtbl * h = (Hashtbl*) malloc(sizeof(Hashtbl));
    reset_hashtbl(h);

    Floor *test_floor = create_floor("maze/floor1/", h);
    Room *target_room = test_floor->rooms[0];

    Texture texture = load_textures(renderer);
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
                break;
            }

            switch (event.type)
            {
            /* Look for a keypress */
            case SDL_KEYDOWN:
                /* Check the SDLKey values and change room if neighbor exists */
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                    if (target_room->neighbors[WEST] != NULL) {
                        target_room = target_room->neighbors[WEST];
                    }
                    break;
                case SDLK_RIGHT:
                    if (target_room->neighbors[EAST] != NULL) {
                        target_room = target_room->neighbors[EAST];
                    }
                    break;
                case SDLK_UP:
                    if (target_room->neighbors[NORTH] != NULL) {
                        target_room = target_room->neighbors[NORTH];
                    }
                    break;
                case SDLK_DOWN:
                    if (target_room->neighbors[SOUTH] != NULL) {
                        target_room = target_room->neighbors[SOUTH];
                    }
                    break;
                default:
                    break;
                }
            }
        }
        SDL_RenderClear(renderer);
        draw_game(renderer, test_floor, target_room, texture);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
