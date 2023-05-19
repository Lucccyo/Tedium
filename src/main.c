#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720
#define TILE_SIZE 24
#define DRAW_TILE_SIZE 24

#include <stdio.h>
#include <string.h>
#include <../include/SDL2/SDL.h>
#include "../include/texture.h"
#include "../include/gui.h"
/* will be replaced with main game struct when it is done */
#include "../include/room.h"
#include "../include/floor.h"
#include "../include/monster_hashtbl.h"

void draw_room(SDL_Renderer *renderer, Room *room, Texture texture)
{
    SDL_Rect Rect_dest;
    Rect_dest.w = DRAW_TILE_SIZE;
    Rect_dest.h = DRAW_TILE_SIZE;

    SDL_Rect Rect_source;
    Rect_source.w = TILE_SIZE;
    Rect_source.h = TILE_SIZE;
    Rect_source.x = 0;
    Rect_source.y = 0;

    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            Rect_dest.x = i * DRAW_TILE_SIZE;
            Rect_dest.y = j * DRAW_TILE_SIZE;
            switch (room->tiles[j][i]) {
                case '#':
                    SDL_RenderCopy(renderer, texture.wall, &Rect_source, &Rect_dest);
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

void onClick(int num)
{
    SDL_Log("click me clicked %i", num);
}

int main()
{
    SDL_Event event;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    int quit = 0;
    int clicked = 0;

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

    // gui test
    SDL_Surface *clickme = SDL_LoadBMP("gfx/clickme.bmp");
    SDL_Texture *clickmebtn = SDL_CreateTextureFromSurface(renderer, clickme);
    SDL_FreeSurface(clickme);

    Button *newButton = create_button(16, 16, 200, 100, clickmebtn, &onClick);
    SDL_Rect *current;

    // display_room(test_room);

    while (!quit)
    {

        while (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
            case SDL_MOUSEBUTTONDOWN:
                clicked = button_clicked(event.button, newButton);
                if (clicked)
                {
                    (*newButton->callback)(1);
                    current = &newButton->rect;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                current = NULL;
                break;
            case SDL_QUIT:
                quit = 1;
                break;
            default:
                continue;
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
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        draw_room(renderer, test_room, texture);

        // draw button test
        display_button(renderer, newButton);

        if (current != NULL)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(renderer, current);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // set background black before presenting
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
