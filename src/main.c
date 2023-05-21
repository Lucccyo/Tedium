#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720
#define TILE_SIZE 24
#define DRAW_TILE_SIZE 24

#include <stdio.h>
#include <string.h>
#include <../include/SDL2/SDL.h>
#include "../include/texture.h"
#include "../include/gui.h"
#include "../include/gui.h"
/* will be replaced with main game struct when it is done */
#include "../include/room.h"
#include "../include/floor.h"
#include "../include/monster_hashtbl.h"
#include "../include/player.h"

void draw_room(SDL_Renderer *renderer, Room *room, Texture texture)
{
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

    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            Rect_dest.x = i * DRAW_TILE_SIZE;
            Rect_dest.y = j * DRAW_TILE_SIZE;
            switch (room->tiles[j][i])
            {
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
void onClick(int num)
{
    SDL_Log("click me clicked %i", num);
}

int main()
{
    SDL_Event event;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    Uint32 lastUpdate = SDL_GetTicks();

    int quit = 0;
    int clicked = 0;
    int clicked = 0;

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

    Hashtbl *h = (Hashtbl *)malloc(sizeof(Hashtbl));
    reset_hashtbl(h);

    Floor *test_floor = create_floor("maze/floor1/", h);
    Room *target_room = test_floor->rooms[0];

    SDL_Surface *plrimg = SDL_LoadBMP("gfx/player.bmp");
    SDL_Texture *plrtexture = SDL_CreateTextureFromSurface(renderer, plrimg);
    SDL_FreeSurface(plrimg);

    Player *player = init_player();
    player->coordinate[0] = (int)WINDOW_WIDTH / 2;
    player->coordinate[1] = (int)WINDOW_HEIGHT / 2;
    int speed = 50;

    int ZDown = 0;
    int QDown = 0;
    int SDown = 0;
    int DDown = 0;

    Texture texture = load_textures(renderer);
    while (!quit)
    {
        // physics
        Uint32 current = SDL_GetTicks();
        float dT = (current - lastUpdate) / 500.0f;

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
            if (event.type == SDL_QUIT)
            {

                // gui test
                SDL_Surface *clickme = SDL_LoadBMP("gfx/clickme.bmp");
                SDL_Texture *clickmebtn = SDL_CreateTextureFromSurface(renderer, clickme);
                SDL_FreeSurface(clickme);

                Button *newButton = create_button(16, 16, 200, 100, clickmebtn, &onClick);
                SDL_Rect *current;

                // display_room(test_room);

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
                    }

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
                            if (target_room->neighbors[WEST] != NULL)
                            {
                                target_room = target_room->neighbors[WEST];
                            }
                            break;
                        case SDLK_RIGHT:
                            if (target_room->neighbors[EAST] != NULL)
                            {
                                target_room = target_room->neighbors[EAST];
                            }
                            break;
                        case SDLK_UP:
                            if (target_room->neighbors[NORTH] != NULL)
                            {
                                target_room = target_room->neighbors[NORTH];
                            }
                            break;
                        case SDLK_DOWN:
                            if (target_room->neighbors[SOUTH] != NULL)
                            {
                                target_room = target_room->neighbors[SOUTH];
                            }
                            break;

                        case SDLK_z:
                            ZDown = 1;
                            break;
                        case SDLK_q:
                            QDown = 1;
                            break;
                        case SDLK_s:
                            SDown = 1;
                            break;
                        case SDLK_d:
                            DDown = 1;
                            break;
                        default:
                            break;
                        }
                    case SDL_KEYUP:
                        /* Check the SDLKey values and change room if neighbor exists */
                        switch (event.key.keysym.sym)
                        {
                        case SDLK_z:
                            ZDown = 0;
                            break;
                        case SDLK_q:
                            QDown = 0;
                            break;
                        case SDLK_s:
                            SDown = 0;
                            break;
                        case SDLK_d:
                            DDown = 0;
                            break;
                        default:
                            break;
                        }
                    default:
                        break;
                    }
                }
            }
        }

        if (ZDown)
        {
            player->coordinate[1] -= speed * dT;
            if (player->coordinate[1] > 0)
                break;
            player->coordinate[1] = 0;
            if (target_room->neighbors[NORTH] == NULL)
                break;

            target_room = target_room->neighbors[NORTH];
            player->coordinate[1] = WINDOW_HEIGHT - 32;
        }

        if (QDown)
        {
            player->coordinate[0] -= speed * dT;

            if (player->coordinate[0] > 0)
                break;

            player->coordinate[0] = 0;
            if (target_room->neighbors[WEST] == NULL)
                break;

            target_room = target_room->neighbors[WEST];
            player->coordinate[0] = WINDOW_WIDTH - 32;
        }

        if (SDown)
        {
            player->coordinate[1] += speed * dT;
            if (player->coordinate[1] + 32 < WINDOW_HEIGHT)
                break;
            player->coordinate[1] = WINDOW_HEIGHT - 32;
            if (target_room->neighbors[SOUTH] == NULL)
                break;

            target_room = target_room->neighbors[SOUTH];
            player->coordinate[1] = 0;
        }

        if (DDown)
        {
            player->coordinate[0] += speed * dT;

            if (player->coordinate[0] + 32 < WINDOW_WIDTH)
                break;
            player->coordinate[0] = WINDOW_WIDTH - 32;
            if (target_room->neighbors[EAST] == NULL)
                break;

            target_room = target_room->neighbors[EAST];
            player->coordinate[0] = 0;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // display stuff here
        draw_room(renderer, test_room, texture);
        draw_player(renderer, player, plrtexture);


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
