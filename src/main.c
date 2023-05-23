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

void draw_light(SDL_Renderer* renderer, int x, int y) {
    SDL_Surface *light_surface = SDL_LoadBMP("img/light.bmp");
    SDL_Texture *light = SDL_CreateTextureFromSurface(renderer, light_surface);
    SDL_SetTextureBlendMode(light, SDL_BLENDMODE_ADD);
    SDL_Rect Rect_dest;
    Rect_dest.w = TILE_SIZE * 3;
    Rect_dest.h = TILE_SIZE * 3;
    Rect_dest.x = x;
    Rect_dest.y = y;
    SDL_RenderCopy(renderer, light, NULL, &Rect_dest);
}

void draw_map(SDL_Renderer* renderer, Floor *floor, Room *target_room) {
    SDL_Rect Rect_dest;
    Rect_dest.w = DRAW_TILE_SIZE/2;
    Rect_dest.h = DRAW_TILE_SIZE/2;
    for (int i = 0; i < FLOOR_SIZE; i++) {
        if (floor->rooms[i] == NULL) { break; }
        if (floor->rooms[i] == target_room) {
            SDL_SetRenderDrawColor(renderer, 76, 0, 153, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 0, 0, 102, 255);
        }
        Rect_dest.x = WINDOW_WIDTH - 100 + floor->rooms[i]->x * DRAW_TILE_SIZE;
        Rect_dest.y = floor->rooms[i]->y * DRAW_TILE_SIZE + 10;
        SDL_RenderDrawRect(renderer, &Rect_dest);
    }
}

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
            switch (room->tiles[j][i]) {
                case '#':
                    if (j - 1 >= 0 && room->tiles[j-1][i] != '#') {
                        SDL_RenderCopy(renderer, texture.wall, &Rect_source, &Rect_dest);
                    } else { SDL_RenderCopy(renderer, texture.noir, &Rect_source, &Rect_dest); }
                    break;
                case '!':
                    SDL_RenderCopy(renderer, texture.floor, &Rect_source, &Rect_dest);
                    SDL_RenderCopy(renderer, texture.key, &Rect_source, &Rect_dest);
                    break;
                case '1':
                    SDL_RenderCopy(renderer, texture.floor, &Rect_source, &Rect_dest);
                    SDL_RenderCopy(renderer, texture.sword, &Rect_source, &Rect_dest);
                    break;
                case '2':
                    SDL_RenderCopy(renderer, texture.floor, &Rect_source, &Rect_dest);
                    SDL_RenderCopy(renderer, texture.shield, &Rect_source, &Rect_dest);
                    break;
                case '3':
                    SDL_RenderCopy(renderer, texture.floor, &Rect_source, &Rect_dest);
                    SDL_RenderCopy(renderer, texture.heart, &Rect_source, &Rect_dest);
                    break;
                default:
                    SDL_RenderCopy(renderer, texture.floor, &Rect_source, &Rect_dest);
                    break;
            }
        }
    }
}

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
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        draw_room(renderer, target_room, texture);
        draw_light(renderer, 250, 250);
        draw_map(renderer, test_floor, target_room);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
