#include <stdio.h>
#include "SDL2/SDL.h"
#include "../include/interface.h"
#include "../include/gui.h"
#include "../include/renderer.h"
#include "../include/maze.h"
#include "../include/SDL2/SDL_ttf.h"
#include "../include/texture.h"

int current_screen = 3;
SDL_Texture *heart_texture;
SDL_Texture *icons_texture;

/* need to be put in texture.c */
SDL_Texture *hearts_texture[5];

int snapshot[5];
SDL_Color ui_color_white = {214, 245, 248, 255};
SDL_Color ui_color = {200, 200, 200, 255};
SDL_Texture *texts[5];
SDL_Rect rects[5];

int get_current_screen()
{
    return current_screen;
}

void set_current_screen(int screen)
{
    current_screen = screen;
}

void onPlayClick(int index)
{
    SDL_Log("click me clicked %i", index);
    current_screen = 2;
}

void onDefaultClick(int index)
{
    SDL_Log("empty click");
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

void goToMainMenu(int index) {
    current_screen = 3;
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

void (*callback)(int);

Interface *load_interfaces(SDL_Renderer *renderer, Maze *maze)
{
    Interface *interface = (Interface *)malloc(sizeof(Interface));
    interface->maze = maze;

    interface->font = TTF_OpenFont("./gfx/nokiafc22.ttf", 12);
    interface->font_b = TTF_OpenFont("./gfx/nokiafc22.ttf", 48);
    printf("Opened font: %d\n", interface->font != NULL);

    // todo: interface groups

    /* gui textures */
    SDL_Surface *menu_asset = SDL_LoadBMP("gfx/menu.bmp");
    SDL_Surface *quit_btn_asset = SDL_LoadBMP("gfx/quit_btn.bmp");
    SDL_Surface *restart_btn_asset = SDL_LoadBMP("gfx/restart_btn.bmp");
    SDL_Surface *resume_btn_asset = SDL_LoadBMP("gfx/resume_btn.bmp");
    SDL_Surface *credits_btn_asset = SDL_LoadBMP("gfx/credits_btn.bmp");
    SDL_Surface *title_background_asset = SDL_LoadBMP("gfx/mainmenubg.bmp");

    SDL_Texture *menu = SDL_CreateTextureFromSurface(renderer, menu_asset);
    SDL_Texture *quit = SDL_CreateTextureFromSurface(renderer, quit_btn_asset);
    SDL_Texture *restart = SDL_CreateTextureFromSurface(renderer, restart_btn_asset);
    SDL_Texture *resume = SDL_CreateTextureFromSurface(renderer, resume_btn_asset);
    SDL_Texture *credits = SDL_CreateTextureFromSurface(renderer, credits_btn_asset);
    SDL_Texture *background = SDL_CreateTextureFromSurface(renderer, title_background_asset);

    // load assets
    SDL_Surface *heart_asset = SDL_LoadBMP("gfx/heart-Sheet.bmp");
    heart_texture = SDL_CreateTextureFromSurface(renderer, heart_asset);

    /* need to move to texture.c and use a tileset for all interface sprites */
    SDL_Surface *heart1_asset = SDL_LoadBMP("img/heart1.bmp");
    SDL_Surface *heart2_asset = SDL_LoadBMP("img/heart2.bmp");
    SDL_Surface *heart3_asset = SDL_LoadBMP("img/heart3.bmp");
    SDL_Surface *heart4_asset = SDL_LoadBMP("img/heart4.bmp");
    SDL_Surface *heart5_asset = SDL_LoadBMP("img/heart5.bmp");

    hearts_texture[0] = SDL_CreateTextureFromSurface(renderer, heart1_asset);
    hearts_texture[1] = SDL_CreateTextureFromSurface(renderer, heart2_asset);
    hearts_texture[2] = SDL_CreateTextureFromSurface(renderer, heart3_asset);
    hearts_texture[3] = SDL_CreateTextureFromSurface(renderer, heart4_asset);
    hearts_texture[4] = SDL_CreateTextureFromSurface(renderer, heart5_asset);

    SDL_Surface *icons_asset = SDL_LoadBMP("gfx/ui_tileset.bmp");
    icons_texture = SDL_CreateTextureFromSurface(renderer, icons_asset);
    SDL_FreeSurface(icons_asset);

    printf("clearing surfaces \n");
    SDL_FreeSurface(menu_asset);
    SDL_FreeSurface(quit_btn_asset);
    SDL_FreeSurface(restart_btn_asset);
    SDL_FreeSurface(resume_btn_asset);
    SDL_FreeSurface(credits_btn_asset);
    SDL_FreeSurface(heart_asset);
    SDL_FreeSurface(title_background_asset);

    SDL_FreeSurface(heart1_asset);
    SDL_FreeSurface(heart2_asset);
    SDL_FreeSurface(heart3_asset);
    SDL_FreeSurface(heart4_asset);
    SDL_FreeSurface(heart5_asset);

    // main menu
    GUI_Element *background_el = gui_create(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, background, &onDefaultClick);
    interface->main_menu[0] = background_el;

    char *options[] = {"Play", "Credits", "Quit"};
    for (int i = 0; i < 3; i++)
    {
        char str[16];
        sprintf(str, "%s", options[i]);
        SDL_Surface *surface = TTF_RenderText_Blended(interface->font_b, str, ui_color_white);
        SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, surface);

        int x = WINDOW_WIDTH/2 - surface->w/2;
        int y = (int)((WINDOW_HEIGHT * 2 / 5) + i * (surface->h + 24));

        if (i == 0)
        {
            callback = &onPlayClick;
        }
        else if (i == 1)
        {
            callback = &onDefaultClick;
        }
        else if (i == 2)
        {
            callback = &onQuitClick;
        }

        GUI_Element *new_el = gui_create(x, y, surface->w, surface->h, text, callback);
        interface->main_menu[i + 1] = new_el;

        SDL_FreeSurface(surface);
    }

    //
    int posx = (int)(WINDOW_WIDTH / 2 - 161 * 2 / 2);
    int posy = (int)(WINDOW_HEIGHT / 2 - 220 * 2 / 2);
    GUI_Element *menu_el = gui_create(posx, posy, 161 * 2, 220 * 2, menu, &onClick);
    GUI_Element *resume_el = gui_create((int)(posx + 161 - 81), (int)(posy + 220 / 2 + 26), 81 * 2, 26 * 2, resume, &onCloseClick);
    GUI_Element *quit_el = gui_create((int)(posx + 161 - 81), (int)(posy + 220 / 2 + 26 + 26 * 2.5), 81 * 2, 26 * 2, quit, &goToMainMenu);
    // GUI_Element *play_btn_el = gui_create(WINDOW_)

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
    SDL_Rect stencil;
    stencil.w = 24;
    stencil.h = 24;
    stencil.x = 0;
    stencil.y = 0;

    SDL_Rect dest;
    dest.w = 24;
    dest.h = 24;

    // display health bar
    int player_life = (int)(interface->maze->state->player->health[health]);
    int max_health = (int)(interface->maze->state->player->health[1]);
    int full_hearts = (int)(player_life / 4);
    int half_hearts = (int)(player_life % 4);
    int i;
    for (i = 0; i < full_hearts; i++)
    {
        dest.x = 24 + i * 24 + (i - 1) * 8;
        dest.y = 16;
        SDL_RenderCopy(renderer, hearts_texture[4], &stencil, &dest);
    }
    if (half_hearts > 0)
    {
        dest.x = 24 + i * 24 + (i - 1) * 8;
        dest.y = 16;
        SDL_RenderCopy(renderer, hearts_texture[half_hearts], &stencil, &dest);
    }

    // get current int values
    Player *player = interface->maze->state->player;
    int values[] = {
        // player->health[0], // health
        // player->health[1], // max health
        player->stats[0],   // attack
        player->stats[1],   // defense
        player->key_number, // keys
    };

    // display text hud
    // TODO update with HUD icons
    for (int i = 0; i < 3; i++)
    {
        char str[32];
        sprintf(str, "%d", values[i]);

        SDL_Rect nr = {12, 56 + i * 32 - 8, 24, 24};
        SDL_Rect stencil = create_rect(12 * i, 0, 12, 12);
        SDL_RenderCopy(renderer, icons_texture, &stencil, &nr);

        // update texures only if the value changed
        if (snapshot[i] != values[i] || texts[i] == NULL)
        {
            SDL_DestroyTexture(texts[i]);

            SDL_Surface *surface = TTF_RenderText_Blended(interface->font, str, ui_color);
            SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_Rect nr = {24 + 16, 56 + i * 32, surface->w, surface->h};
            texts[i] = text;
            rects[i] = nr;

            SDL_FreeSurface(surface);
            snapshot[i] = values[i];
        }

        SDL_RenderCopy(renderer, texts[i], NULL, &rects[i]);
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

void draw_main_menu(SDL_Renderer *renderer, Interface *interface)
{
    for (int i = 0; i < (int)sizeof(interface->main_menu) / sizeof(interface->main_menu[0]); i++)
    {
        gui_display(renderer, interface->main_menu[i]);
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

    for (int i = 0; i < (int)sizeof(interface->main_menu) / sizeof(interface->main_menu[0]); i++)
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
    case 3: // main meun screen
        draw_main_menu(renderer, interface);
        break;

    default:
        break;
    }
}

void destroy_interface(Interface *interface)
{
    for (int i = 0; i < 5; i++)
    {
        SDL_DestroyTexture(texts[i]);
    }
    SDL_DestroyTexture(icons_texture);

    // todo : destroy interface textures

    TTF_CloseFont(interface->font);
    TTF_CloseFont(interface->font_b);
};