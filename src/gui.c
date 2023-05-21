#include "SDL2/SDL.h"
#include "../include/gui.h"

Button *create_button(int x, int y, int width, int height, SDL_Texture *texture, void (*callback)(int))
{
    Button *newButton = malloc(sizeof(Button));

    SDL_Rect newRect = {x, y, width, height};
    newButton->rect = newRect;
    newButton->texture = texture;
    newButton->callback = callback;

    return newButton;
}

void display_button(SDL_Renderer *renderer, Button *button)
{
    SDL_RenderCopy(renderer, button->texture, NULL, &button->rect);
}

int button_clicked(SDL_MouseButtonEvent mouse, Button *button)
{
    int x = mouse.x;
    int y = mouse.y;
    SDL_Rect rect = button->rect;

    int clicked = (x >= rect.x && y >= rect.y && x <= rect.x + rect.w && y <= rect.y + rect.h);

    return clicked;
}