#include <stdio.h>
#include "SDL2/SDL.h"
#include "../include/gui.h"
#include "../include/interface.h"

GUI_Element *gui_create(int x, int y, int w, int h, SDL_Texture *texture, void (*callback)(int)) {
    GUI_Element *newGui = malloc(sizeof(GUI_Element));

    SDL_Rect newRect = {x, y, w, h};
    newGui->rect = newRect;
    newGui->texture = texture;
    newGui->callback = callback;

    return newGui;
};

int gui_clicked(SDL_MouseButtonEvent mouse, GUI_Element *element) {
    if (element->displayed == 0) {
        return 0;
    }

    int x = mouse.x;
    int y = mouse.y;
    SDL_Rect rect = element->rect;

    int clicked = (x >= rect.x && y >= rect.y && x <= rect.x + rect.w && y <= rect.y + rect.h);

    return clicked;
};