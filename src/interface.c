#include <stdio.h>
#include "SDL2/SDL.h"
#include "../include/interface.h"
#include "../include/gui.h"
#include "../include/renderer.h"
#include "../include/maze.h"

int current_screen = 2;
SDL_Texture *heart_texture;

int get_current_screen()
{
    return current_screen;
}

void set_current_screen(int screen)
{
    current_screen = screen;
}

void onClick(int index)
{
    SDL_Log("click me clicked %i", index);
    current_screen = 1; // open menu
}

void onCloseClick(int index)
{
    SDL_Log("closing clicked %i", index);
    current_screen = 2;
}

void onQuitClick(int index)
{
    SDL_Log("quit clicked %i", index);
    current_screen = 0; // quit game
}

void onMenuButtonClick(int index)
{
    SDL_Log("menu clicked %i", index);
    current_screen = 1; // open menu
}

Interface *load_interfaces(SDL_Renderer *renderer, Maze *maze)
{
    Interface *interface = (Interface *)malloc(sizeof(Interface));
    interface->maze = maze;

    // todo: interface groups

    /* gui textures */
    SDL_Surface *menu_asset = SDL_LoadBMP("gfx/menu.bmp");
    SDL_Surface *quit_btn_asset = SDL_LoadBMP("gfx/quit_btn.bmp");
    SDL_Surface *restart_btn_asset = SDL_LoadBMP("gfx/restart_btn.bmp");
    SDL_Surface *resume_btn_asset = SDL_LoadBMP("gfx/resume_btn.bmp");
    SDL_Surface *credits_btn_asset = SDL_LoadBMP("gfx/credits_btn.bmp");

    SDL_Texture *menu = SDL_CreateTextureFromSurface(renderer, menu_asset);
    SDL_Texture *quit = SDL_CreateTextureFromSurface(renderer, quit_btn_asset);
    SDL_Texture *restart = SDL_CreateTextureFromSurface(renderer, restart_btn_asset);
    SDL_Texture *resume = SDL_CreateTextureFromSurface(renderer, resume_btn_asset);
    SDL_Texture *credits = SDL_CreateTextureFromSurface(renderer, credits_btn_asset);

    // load assets
    SDL_Surface *heart_asset = SDL_LoadBMP("gfx/heart-Sheet.bmp");
    heart_texture = SDL_CreateTextureFromSurface(renderer, heart_asset);

    printf("clearing surfaces \n");
    SDL_FreeSurface(menu_asset);
    SDL_FreeSurface(quit_btn_asset);
    SDL_FreeSurface(restart_btn_asset);
    SDL_FreeSurface(resume_btn_asset);
    SDL_FreeSurface(credits_btn_asset);
    SDL_FreeSurface(heart_asset);

    //
    int posx = (int)(WINDOW_WIDTH / 2 - 161 * 2 / 2);
    int posy = (int)(WINDOW_HEIGHT / 2 - 220 * 2 / 2);
    GUI_Element *menu_el = gui_create(posx, posy, 161 * 2, 220 * 2, menu, &onClick);
    GUI_Element *resume_el = gui_create((int)(posx + 161 - 81), (int)(posy + 220 / 2 + 26), 81 * 2, 26 * 2, resume, &onCloseClick);
    GUI_Element *quit_el = gui_create((int)(posx + 161 - 81), (int)(posy + 220 / 2 + 26 + 26 * 2.5), 81 * 2, 26 * 2, quit, &onQuitClick);

    interface->menu[0] = menu_el;
    interface->menu[1] = resume_el;
    interface->menu[2] = quit_el;

    printf("interface generated\n");
    return interface;
}

void gui_display(SDL_Renderer *renderer, GUI_Element *element)
{
    SDL_RenderCopy(renderer, element->texture, NULL, &element->rect);
    element->displayed = 1;
};

void draw_hud(SDL_Renderer *renderer, Interface *interface)
{
    // for (int i = 0; i < (int)sizeof(interface->hud) / sizeof(interface->hud[0]); i++)
    // {
    //     gui_display(renderer, interface->hud[i]);
    // }

    SDL_Rect stencil;
    stencil.w = 24;
    stencil.h = 24;

    SDL_Rect dest;
    dest.w = 24;
    dest.h = 24;

    // display health bar
    int player_life = (int)(interface->maze->state->player->health[0] / 2);
    for (int i = 0; i < player_life; i++)
    {
        stencil.x = 24;
        stencil.y = 0;

        dest.x = 24 + i * 24 + (i - 1) * 8;
        dest.y = 16;
        SDL_RenderCopy(renderer, heart_texture, &stencil, &dest);
    }
}

void draw_menu(SDL_Renderer *renderer, Interface *interface)
{
    draw_hud(renderer, interface);
    for (int i = 0; i < (int)sizeof(interface->menu) / sizeof(interface->menu[0]); i++)
    {
        gui_display(renderer, interface->menu[i]);
    }
}

void draw_gui(SDL_Renderer *renderer, Interface *interface)
{
    // set all the frames to hidden
    for (int i = 0; i < (int)sizeof(interface->menu) / sizeof(interface->menu[0]); i++)
    {
        interface->menu[i]->displayed = 0;
    }
    for (int i = 0; i < (int)sizeof(interface->hud) / sizeof(interface->hud[0]); i++)
    {
        interface->hud[i]->displayed = 0;
    }

    // show the correct interfaces depending on the state
    switch (current_screen)
    {
    case 1: // menu screen
        draw_menu(renderer, interface);
        break;
    case 2: // hud
        draw_hud(renderer, interface);
        break;

    default:
        break;
    }
}