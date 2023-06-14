#ifndef GUI_H
#define GUI_H

#include "SDL2/SDL.h"

typedef struct {
    SDL_Rect dest_rect;
    SDL_Rect src_rect;
    SDL_Texture *texture;
    int displayed;
    void (*callback)(int);
} GUI_Element;

GUI_Element *gui_create(SDL_Rect dest_rect, SDL_Rect src_rect, SDL_Texture *texture, void (*callback)(int));

int gui_clicked(SDL_MouseButtonEvent mouse, GUI_Element *element);

#endif