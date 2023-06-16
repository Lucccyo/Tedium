#include "interface.h"

int current_screen = MAIN_MENU;
SDL_Texture *icons_texture;

/* need to be put in texture.c */
SDL_Texture *hearts_texture[5];

int snapshot[5];
SDL_Color ui_color_main = {214, 245, 248, 255};
SDL_Color ui_color_red = {225, 255, 255, 255};
SDL_Color ui_color_green = {255, 225, 255, 255};
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

void onPlayClick()
{
    current_screen = GAME;
}

void onDefaultClick()
{
}

void onClick()
{
    current_screen = PAUSE_MENU; // open menu
}

void onCloseClick()
{
    current_screen = GAME;
}

void goToMainMenu()
{
    current_screen = MAIN_MENU;
}

void onQuitClick()
{
    current_screen = QUIT; // quit game
}

void (*callback)(int);

Interface *load_interfaces(SDL_Renderer *renderer, Maze *maze, Texture *texture)
{
    Interface *interface = (Interface *)malloc(sizeof(Interface));
    interface->maze = maze;

    interface->font = TTF_OpenFont("./gfx/nokiafc22.ttf", 12);
    interface->font_b = TTF_OpenFont("./gfx/nokiafc22.ttf", 48);

    SDL_Surface *title_background_asset = SDL_LoadBMP("gfx/mainmenubg.bmp");
    SDL_Surface *icons_asset = SDL_LoadBMP("gfx/ui_tileset.bmp");

    SDL_Texture *background = SDL_CreateTextureFromSurface(renderer, title_background_asset);
    icons_texture = SDL_CreateTextureFromSurface(renderer, icons_asset);

    SDL_FreeSurface(icons_asset);
    SDL_FreeSurface(title_background_asset);

    // main display
    interface->main_menu[0] = gui_create(create_rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT),
                                         create_rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT),
                                         background, &onDefaultClick);

    char str[16];
    char *options[] = {"Play", "Credits", "Quit"};
    for (int i = 0; i < 3; i++)
    {
        sprintf(str, "%s", options[i]);
        SDL_Surface *surface = TTF_RenderText_Blended(interface->font_b, str, ui_color_main);
        SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, surface);

        int x = WINDOW_WIDTH / 2 - surface->w / 2;
        int y = (int)((WINDOW_HEIGHT * 2 / 5) + i * (surface->h + 24));

        if (i == 0)
            callback = &onPlayClick;
        else if (i == 1)
            callback = &onDefaultClick;
        else if (i == 2)
            callback = &onQuitClick;

        interface->main_menu[i + 1] = gui_create(create_rect(x, y, surface->w, surface->h),
                                                 create_rect(0, 0, surface->w, surface->h),
                                                 text,
                                                 callback);

        SDL_FreeSurface(surface);
    }

    int posx = (int)(WINDOW_WIDTH / 2 - 161 * 2 / 2);
    int posy = (int)(WINDOW_HEIGHT * 1 / 4);

    GUI_Element *pause_el = gui_create(
        create_rect((int)(posx + 161 - 81), (int)(posy + 72 * 1), 81 * 2, 26 * 2),
        texture->rects_ui[RECT_PAUSE_TEXT],
        texture->tileset_ui, &onDefaultClick);

    GUI_Element *resume_el = gui_create(
        create_rect((int)(posx + 161 - 81), (int)(posy + 72 * 2), 81 * 2, 26 * 2),
        texture->rects_ui[RECT_RESUME_BUTTON],
        texture->tileset_ui, &onCloseClick);

    GUI_Element *quit_el = gui_create(
        create_rect((int)(posx + 161 - 81), (int)(posy + 72 * 3), 81 * 2, 26 * 2),
        texture->rects_ui[RECT_QUIT_BUTTON],
        texture->tileset_ui, &goToMainMenu);

    interface->menu[0] = pause_el;
    interface->menu[1] = resume_el;
    interface->menu[2] = quit_el;

    // end screen stuff
    char str2[16];
    char *options2[] = {"You lost!", "You won!"};
    for (int i = 0; i < 2; i++)
    {
        sprintf(str2, "%s", options2[i]);
        SDL_Color color = i == 0 ? ui_color_red : ui_color_green;
        SDL_Surface *surface = TTF_RenderText_Blended(interface->font_b, str2, color);
        SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, surface);

        int x = WINDOW_WIDTH / 2 - surface->w / 2;
        int y = (int)((WINDOW_HEIGHT * 2 / 5));

        interface->end_screen[i + 1] = gui_create(create_rect(x, y, surface->w, surface->h),
                                                 create_rect(0, 0, surface->w, surface->h),
                                                 text,
                                                 &onDefaultClick);

        SDL_FreeSurface(surface);
    }

    interface->end_screen[0] = quit_el;

    printf("interface generated\n");
    return interface;
}

void gui_display(SDL_Renderer *renderer, GUI_Element *element, Texture *texture)
{
    SDL_RenderCopy(renderer, element->texture, &element->src_rect, &element->dest_rect);
    element->displayed = 1;
};

void draw_hud(SDL_Renderer *renderer, Interface *interface, Texture *texture)
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
    int full_hearts = (int)(player_life / 4);
    int half_hearts = (int)(player_life % 4);
    int i;
    for (i = 0; i < full_hearts; i++)
    {
        dest.x = 24 + i * 24 + (i - 1) * 8;
        dest.y = 16;
        SDL_RenderCopy(renderer, texture->hearts_texture[4], &stencil, &dest);
    }
    if (half_hearts > 0)
    {
        dest.x = 24 + i * 24 + (i - 1) * 8;
        dest.y = 16;
        SDL_RenderCopy(renderer, texture->hearts_texture[half_hearts], &stencil, &dest);
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

        SDL_Rect dstrect = {12, 56 + i * 32 - 8, 24, 24};
        SDL_RenderCopy(renderer, texture->tileset_ui, &texture->rects_ui[i], &dstrect);

        // update textures only if the value changed
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

void draw_menu(SDL_Renderer *renderer, Interface *interface, Texture *texture)
{
    draw_hud(renderer, interface, texture);
    for (int i = 0; i < (int)(sizeof(interface->menu) / sizeof(interface->menu[0])); i++)
    {
        gui_display(renderer, interface->menu[i], texture);
    }
}

void draw_main_menu(SDL_Renderer *renderer, Interface *interface, Texture *texture)
{
    for (int i = 0; i < (int)(sizeof(interface->main_menu) / sizeof(interface->main_menu[0])); i++)
    {
        gui_display(renderer, interface->main_menu[i], texture);
    }
}

void draw_end_screen(SDL_Renderer *renderer, Interface *interface, Texture *texture)
{
    gui_display(renderer, interface->end_screen[0], texture);

    Player *player = interface->maze->state->player;
    if (player->health[0] <= 0) {
        gui_display(renderer, interface->end_screen[1], texture);
    } else {
        gui_display(renderer, interface->end_screen[2], texture);
    }
}

void draw_gui(SDL_Renderer *renderer, Interface *interface, Texture *texture)
{
    // set all the frames to hidden
    for (int i = 0; i < (int)(sizeof(interface->menu) / sizeof(interface->menu[0])); i++)
    {
        interface->menu[i]->displayed = 0;
    }
    for (int i = 0; i < (int)(sizeof(interface->hud) / sizeof(interface->hud[0])); i++)
    {
        interface->hud[i]->displayed = 0;
    }
    for (int i = 0; i < (int)(sizeof(interface->main_menu) / sizeof(interface->main_menu[0])); i++)
    {
        interface->hud[i]->displayed = 0;
    }

    // show the correct interfaces depending on the state
    switch (current_screen)
    {
    case PAUSE_MENU: // menu screen
        draw_menu(renderer, interface, texture);
        break;
    case GAME: // hud
        draw_hud(renderer, interface, texture);
        break;
    case MAIN_MENU: // main meun screen
        draw_main_menu(renderer, interface, texture);
        break;
    case END_SCREEN:
        draw_end_screen(renderer, interface, texture);
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