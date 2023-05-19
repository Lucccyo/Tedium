#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720
#define TILE_SIZE 24
#define DRAW_TILE_SIZE 24

#include <stdio.h>
#include <string.h>
#include <../include/SDL2/SDL.h>
#include "../include/texture.h"
/* will be replaced with main game struct when it is done */
#include "../include/room.h"
#include "../include/floor.h"
#include "../include/monster_hashtbl.h"

void draw_room(SDL_Renderer* renderer, Room *room, Texture texture) {
    SDL_Rect Rect_dest;
    Rect_dest.w = DRAW_TILE_SIZE;
    Rect_dest.h = DRAW_TILE_SIZE;

    SDL_Rect Rect_source;
    Rect_source.w = TILE_SIZE;
    Rect_source.h = TILE_SIZE;
    Rect_source.x = 0;
    Rect_source.y = 0;
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            Rect_dest.x = i * DRAW_TILE_SIZE;
            Rect_dest.y = j * DRAW_TILE_SIZE;
            /* Wall drawing */
            if (room->tiles[j][i] == '#') {
                SDL_RenderCopy(renderer, texture.wall, &Rect_source, &Rect_dest);
            /* Heart drawing (with floor behind) */
            } else if (room->tiles[j][i] == '3') {
                SDL_RenderCopy(renderer, texture.floor, &Rect_source, &Rect_dest);
                SDL_RenderCopy(renderer, texture.heart, &Rect_source, &Rect_dest);
            /* Floor drawing */
            } else {
                SDL_RenderCopy(renderer, texture.floor, &Rect_source, &Rect_dest);
            }
        }
    }
}

int main() {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

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

    SDL_Event event;
    int quit = 0;

    Hashtbl * h = (Hashtbl*) malloc(sizeof(Hashtbl));
    reset_hashtbl(h);

    Floor *test_floor = create_floor("maze/floor1", h);
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
                    if (target_room->west != NULL) {
                        target_room = target_room->west;
                    }
                    break;
                case SDLK_RIGHT:
                    if (target_room->east != NULL) {
                        target_room = target_room->east;
                    }
                    break;
                case SDLK_UP:
                    if (target_room->north != NULL) {
                        target_room = target_room->north;
                    }
                    break;
                case SDLK_DOWN:
                    if (target_room->south != NULL) {
                        target_room = target_room->south;
                    }
                    break;
                default:
                    break;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        draw_room(renderer, target_room, texture);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
