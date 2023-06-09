#ifndef INTERFACE_H
#define INTERFACE_H

#include "SDL2/SDL.h"
#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_ttf.h"
#include "gui.h"
#include "maze.h"
#include "gui.h"
#include "renderer.h"
#include "texture.h"

enum
{
    QUIT,
    GAME,
    PAUSE_MENU,
    MAIN_MENU,
    END_SCREEN,
    CREDITS,
};

/* Contains all SDL_Textures used in the game */
struct interface {
    Maze *maze;
    TTF_Font *font;
    TTF_Font *font_b;
    GUI_Element *menu[3];
    GUI_Element *hud[0];
    GUI_Element *main_menu[4];
    GUI_Element *end_screen[3];
    GUI_Element *credits[2];
};

typedef struct interface Interface;

Interface *load_interfaces(SDL_Renderer *renderer, Maze *maze, Texture * texture);
void destroy_interface(Interface *interface);

void gui_display(SDL_Renderer *renderer, GUI_Element *element);
void draw_gui(SDL_Renderer *renderer, Interface *interface, Texture *texture);

void set_current_screen(int screen);
int get_current_screen();

#endif