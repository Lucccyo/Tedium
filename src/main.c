#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720
#define COLUMNS 30
#define ROWS 30
#define TILE_WIDTH WINDOW_WIDTH / COLUMNS
#define TILE_HEIGHT WINDOW_HEIGHT / ROWS

#include <../include/SDL2/SDL.h>

void Afficher(SDL_Renderer *renderer, SDL_Texture *texture, int textureIndex)
{
    int i, j;

    SDL_Rect Rect_dest;
    Rect_dest.w = TILE_WIDTH;
    Rect_dest.h = TILE_HEIGHT;

    SDL_Rect Rect_source;
    Rect_source.w = 20;
    Rect_source.h = 20;

    for (i = 0; i < COLUMNS; i++)
    {
        for (j = 0; j < ROWS; j++)
        {
            Rect_dest.x = i * TILE_WIDTH;
            Rect_dest.y = j * TILE_HEIGHT;

            Rect_source.x = textureIndex % 16 * 20;
            Rect_source.y = (int)(textureIndex / 16) * 20;

            SDL_RenderCopy(renderer, texture, &Rect_source, &Rect_dest);
        }
    }
}

int main()
{
    SDL_Surface *screen;
    SDL_Event event;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    int quit = 0;
    int index = 1;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Error inititializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Tedium", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Error creating window: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Error creating renderer: %s\n", SDL_GetError());
        return 1;
    }

    // load assets
    SDL_Surface *tileset = SDL_LoadBMP("gfx/tilemap.bmp");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, tileset);

    while (!quit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = 1;
                break;
            }

            switch (event.type)
            {
            /* Look for a keypress */
            case SDL_KEYDOWN:
                /* Check the SDLKey values and move change the coords */
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                    index -= 1;
                    break;
                case SDLK_RIGHT:
                    index += 1;
                    break;
                default:
                    break;
                }
            }
        }

        // listen for keyboard events

        // display graphics
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 225);

        Afficher(renderer, texture, index);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(tileset);

    SDL_Quit();
    return 0;
}