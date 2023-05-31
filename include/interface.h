#ifndef INTERFACE_H
#define INTERFACE_H

#include "SDL2/SDL.h"
#include "gui.h"

/* Contains all SDL_Textures used in the game */
struct interface
{
    GUI_Element *menu[3];
    GUI_Element *hud[1];
    // SDL_Texture *close;
    // SDL_Texture *quit;
    // SDL_Texture *restart;
    // SDL_Texture *resume;
    // SDL_Texture *credits;
};

typedef struct interface Interface;

Interface *load_interfaces(SDL_Renderer *renderer);

void gui_display(SDL_Renderer *renderer, GUI_Element *element);
void draw_gui(SDL_Renderer *renderer, Interface *interface);

int get_current_screen();
int current_screen;

#endif