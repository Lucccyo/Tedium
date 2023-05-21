#ifndef BUTTON_H
#define BUTTON_H

#include "SDL2/SDL.h"

struct button {
    SDL_Rect rect;
    SDL_Texture *texture;
    void (*callback)(int);
};

typedef struct button Button;

Button *create_button(int x, int y, int width, int height, SDL_Texture *texture, void (*callback)(int));

void display_button(SDL_Renderer *renderer, Button *button);
int button_clicked(SDL_MouseButtonEvent mouse, Button *button);

#endif