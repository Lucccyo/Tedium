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
            /* Heart drawing (floor behind) */
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
    SDL_Surface *screen;
    SDL_Event event;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    int quit = 0;
    int index = 1;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Error inititializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Tedium", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Error creating window: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Error creating renderer: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Event event;
    int quit = 0;
    Room *test_room = create_room_from_file("rooms/prof.level");
    Texture texture = load_textures(renderer);
    display_room(test_room);
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
                /* Check the SDLKey values and move change the coords */
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                    index -= 1;
                    break;
                case SDLK_RIGHT:
                    index += 1;
                    break;
                default:
                    break;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        draw_room(renderer, test_room, texture);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
