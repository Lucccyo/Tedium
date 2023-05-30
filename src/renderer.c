#include<../include/renderer.h>

void draw_game(SDL_Renderer* renderer, Floor *floor, Room *target_room, Player *player, Texture * texture) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    draw_room(renderer, target_room, texture);
    draw_minimap(renderer, floor, target_room);
    draw_player(renderer, player, texture);
}

void draw_room(SDL_Renderer* renderer, Room *room, Texture * texture) {
    SDL_Rect Rect_dest;
    Rect_dest.w = DRAW_TILE_SIZE;
    Rect_dest.h = DRAW_TILE_SIZE;

    SDL_Rect Rect_source;
    Rect_source.w = TILE_SIZE;
    Rect_source.h = TILE_SIZE;
    Rect_source.x = 0;
    Rect_source.y = 0;
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            Rect_dest.x = i * DRAW_TILE_SIZE;
            Rect_dest.y = j * DRAW_TILE_SIZE;
            switch (room->tiles[j][i]) {
                case '#':
                    if (j - 1 >= 0 && room->tiles[j-1][i] != '#') {
                        SDL_RenderCopy(renderer, texture->wall, &Rect_source, &Rect_dest);
                    } else { SDL_RenderCopy(renderer, texture->noir, &Rect_source, &Rect_dest); }
                    break;
                case '!':
                    SDL_RenderCopy(renderer, texture->floor, &Rect_source, &Rect_dest);
                    SDL_RenderCopy(renderer, texture->key, &Rect_source, &Rect_dest);
                    break;
                case '1':
                    SDL_RenderCopy(renderer, texture->floor, &Rect_source, &Rect_dest);
                    SDL_RenderCopy(renderer, texture->sword, &Rect_source, &Rect_dest);
                    break;
                case '2':
                    SDL_RenderCopy(renderer, texture->floor, &Rect_source, &Rect_dest);
                    SDL_RenderCopy(renderer, texture->shield, &Rect_source, &Rect_dest);
                    break;
                case '3':
                    SDL_RenderCopy(renderer, texture->floor, &Rect_source, &Rect_dest);
                    SDL_RenderCopy(renderer, texture->heart, &Rect_source, &Rect_dest);
                    break;
                default:
                    SDL_RenderCopy(renderer, texture->floor, &Rect_source, &Rect_dest);
                    break;
            }
        }
    }
}

void draw_light(SDL_Renderer* renderer, int x, int y) {
    SDL_Surface *light_surface = SDL_LoadBMP("img/light.bmp");
    SDL_Texture *light = SDL_CreateTextureFromSurface(renderer, light_surface);
    SDL_SetTextureBlendMode(light, SDL_BLENDMODE_ADD);
    SDL_Rect Rect_dest;
    Rect_dest.w = TILE_SIZE * 5;
    Rect_dest.h = TILE_SIZE * 5;
    Rect_dest.x = x;
    Rect_dest.y = y;
    SDL_RenderCopy(renderer, light, NULL, &Rect_dest);
}

void draw_minimap(SDL_Renderer* renderer, Floor *floor, Room *target_room) {
    SDL_Rect Rect_dest;
    Rect_dest.w = DRAW_TILE_SIZE/2;
    Rect_dest.h = DRAW_TILE_SIZE/2;
    for (int i = 0; i < FLOOR_SIZE; i++) {
        if (floor->rooms[i] == NULL) { break; }
        if (floor->rooms[i]->x == target_room->x && floor->rooms[i]->y == target_room->y) {
            SDL_SetRenderDrawColor(renderer, 76, 0, 153, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 0, 0, 102, 255);
        }
        Rect_dest.x = WINDOW_WIDTH - 100 + floor->rooms[i]->x * DRAW_TILE_SIZE;
        Rect_dest.y = floor->rooms[i]->y * DRAW_TILE_SIZE + 10;
        SDL_RenderDrawRect(renderer, &Rect_dest);
    }
}

void draw_player(SDL_Renderer *renderer, Player *player, Texture * texture) {
    SDL_Rect newRect = {player->coordinate[0]*TILE_SIZE, player->coordinate[1]*TILE_SIZE, 24, 24};
    SDL_RenderCopy(renderer, texture->player, NULL, &newRect);
}
