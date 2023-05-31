#ifndef GUI_H
#define GUI_H

#include "../include/SDL2/SDL.h"

typedef struct
{
    SDL_Rect rect;
    SDL_Texture *texture;
    int displayed;
    void (*callback)(int);
} GUI_Element;

GUI_Element *gui_create(int x, int y, int w, int h, SDL_Texture *texture, void (*callback)(int));

int gui_clicked(SDL_MouseButtonEvent mouse, GUI_Element *element);

#endif