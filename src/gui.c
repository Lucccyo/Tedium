#include <stdio.h>
#include "SDL2/SDL.h"
#include "../include/gui.h"
#include "../include/interface.h"

// create and interactable GUI component
GUI_Element *gui_create(SDL_Rect dest_rect, SDL_Rect src_rect, SDL_Texture *texture, void (*callback)(int)) {
    GUI_Element *newGui = malloc(sizeof(GUI_Element));

    newGui->dest_rect = dest_rect;
    newGui->src_rect = src_rect;
    newGui->texture = texture;
    newGui->callback = callback;

    return newGui;
};

// check if the provided GUI has been clicked (returns 1 or 0)
int gui_clicked(SDL_MouseButtonEvent mouse, GUI_Element *element) {
    if (element->displayed == 0) {
        return 0;
    }

    int x = mouse.x;
    int y = mouse.y;
    SDL_Rect rect = element->dest_rect;

    int clicked = (x >= rect.x && y >= rect.y && x <= rect.x + rect.w && y <= rect.y + rect.h);

    return clicked;
};