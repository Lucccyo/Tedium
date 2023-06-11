#ifndef INTERFACE_H
#define INTERFACE_H

#include "SDL2/SDL.h"
#include "gui.h"
#include "maze.h"
#include "SDL2/SDL_ttf.h"

/* Contains all SDL_Textures used in the game */
struct interface
{
    Maze *maze;
    TTF_Font *font;
    GUI_Element *menu[3];
    GUI_Element *hud[0];
    GUI_Element *main_menu[1];
    // SDL_Texture *close;
    // SDL_Texture *quit;
    // SDL_Texture *restart;
    // SDL_Texture *resume;
    // SDL_Texture *credits;
};

typedef struct interface Interface;

Interface *load_interfaces(SDL_Renderer *renderer, Maze *maze);
void destroy_interface(Interface *interface);

void gui_display(SDL_Renderer *renderer, GUI_Element *element);
void draw_gui(SDL_Renderer *renderer, Interface *interface);

void set_current_screen(int screen);
int get_current_screen();

#endif