#include <stdio.h>
#include "SDL2/SDL.h"
#include "../include/interface.h"
#include "../include/gui.h"
#include "../include/renderer.h"

int current_screen = 1;

int get_current_screen() {
    return current_screen;
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

Interface *load_interfaces(SDL_Renderer *renderer)
{
    Interface *interface = (Interface *)malloc(sizeof(Interface));

    // todo: interface groups

    /* gui textures */
    SDL_Surface *menu_asset = SDL_LoadBMP("gfx/menu.bmp");
    SDL_Surface *close_btn_asset = SDL_LoadBMP("gfx/close_btn.bmp");
    SDL_Surface *quit_btn_asset = SDL_LoadBMP("gfx/quit_btn.bmp");
    SDL_Surface *restart_btn_asset = SDL_LoadBMP("gfx/restart_btn.bmp");
    SDL_Surface *resume_btn_asset = SDL_LoadBMP("gfx/resume_btn.bmp");
    SDL_Surface *credits_btn_asset = SDL_LoadBMP("gfx/credits_btn.bmp");
    SDL_Surface *button_asset = SDL_LoadBMP("gfx/button.bmp");

    SDL_Texture *menu = SDL_CreateTextureFromSurface(renderer, menu_asset);
    SDL_Texture *close = SDL_CreateTextureFromSurface(renderer, close_btn_asset);
    SDL_Texture *quit = SDL_CreateTextureFromSurface(renderer, quit_btn_asset);
    SDL_Texture *restart = SDL_CreateTextureFromSurface(renderer, restart_btn_asset);
    SDL_Texture *resume = SDL_CreateTextureFromSurface(renderer, resume_btn_asset);
    SDL_Texture *credits = SDL_CreateTextureFromSurface(renderer, credits_btn_asset);
    SDL_Texture *button = SDL_CreateTextureFromSurface(renderer, button_asset);

    SDL_FreeSurface(menu_asset);
    SDL_FreeSurface(close_btn_asset);
    SDL_FreeSurface(quit_btn_asset);
    SDL_FreeSurface(restart_btn_asset);
    SDL_FreeSurface(resume_btn_asset);
    SDL_FreeSurface(credits_btn_asset);
    SDL_FreeSurface(button_asset);

    //
    int posx = (int)(WINDOW_WIDTH / 2 - 161*2 / 2);
    int posy = (int)(WINDOW_HEIGHT / 2 - 220*2 / 2);
    GUI_Element *menu_el = gui_create(posx, posy, 161*2, 220*2, menu, &onClick);
    GUI_Element *close_el = gui_create((int)(posx + 161*2 - 23*2), (int)(posy), 23*2, 23*2, close, &onCloseClick);
    GUI_Element *quit_el = gui_create((int)(posx + 161 - 81), (int)(posy + 220 / 2 + 26), 81 * 2, 26 * 2, quit, &onQuitClick);

    interface->menu[0] = menu_el;
    interface->menu[1] = close_el;
    interface->menu[2] = quit_el;

    GUI_Element *button_el = gui_create(16, (int)(WINDOW_HEIGHT / 2 - 75 / 2), 75, 75, button, &onMenuButtonClick);
    interface->hud[0] = button_el;

    return interface;
}

void gui_display(SDL_Renderer *renderer, GUI_Element *element)
{
    SDL_RenderCopy(renderer, element->texture, NULL, &element->rect);
    element->displayed = 1;
};

void draw_gui(SDL_Renderer *renderer, Interface *interface)
{
    for (int i = 0; i < (int)sizeof(interface->menu) / sizeof(interface->menu[0]); i++)
    {
        interface->menu[i]->displayed = 0;
    }
    for (int i = 0; i < (int)sizeof(interface->hud) / sizeof(interface->hud[0]); i++)
    {
        interface->hud[i]->displayed = 0;
    }

    switch (current_screen)
    {
    case 1:
        for (int i = 0; i < (int)sizeof(interface->menu) / sizeof(interface->menu[0]); i++)
        {
            gui_display(renderer, interface->menu[i]);
        }
        break;
    case 2:
        for (int i = 0; i < (int)sizeof(interface->hud) / sizeof(interface->hud[0]); i++)
        {
            gui_display(renderer, interface->hud[i]);
        }
        break;

    default:
        break;
    }
}