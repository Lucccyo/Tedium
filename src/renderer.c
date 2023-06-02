#include<../include/renderer.h>

void draw_game(SDL_Renderer* renderer, Floor *floor, Room *target_room, Player *player, Texture *texture, Animator *animator) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    draw_room(renderer, target_room, texture, animator);
    draw_minimap(renderer, floor, target_room);
    draw_player(renderer, player, texture);
    draw_lights(renderer, target_room, texture, animator);
}

void draw_room(SDL_Renderer* renderer, Room *room, Texture *texture, Animator *animator) {
    SDL_Rect rect_dest;
    rect_dest.w = DRAW_TILE_SIZE;
    rect_dest.h = DRAW_TILE_SIZE;

    SDL_Rect rect_source;
    rect_source.w = TILE_SIZE;
    rect_source.h = TILE_SIZE;
    rect_source.x = 0;
    rect_source.y = 0;

    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            rect_dest.x = i * DRAW_TILE_SIZE;
            rect_dest.y = j * DRAW_TILE_SIZE;
            switch (room->tiles[j][i]) {
                case EMPTY:
                    if (j - 1 >= 0 && room->tiles[j-1][i] != '#') {
                        SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_WALL], &rect_dest);
                    } else { SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_VOID], &rect_dest); }
                    break;
                case KEY:
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_FLOOR], &rect_dest);
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_KEY], &rect_dest);
                    break;
                case POTION:
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_FLOOR], &rect_dest);
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_POTION], &rect_dest);
                    break;
                case ATTACK_POWERUP:
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_FLOOR], &rect_dest);
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_ATTACK_POWERUP], &rect_dest);
                    break;
                case DEFENSE_POWERUP:
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_FLOOR], &rect_dest);
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_DEFENSE_POWERUP], &rect_dest);
                    break;
                case HEALTH_POWERUP:
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_FLOOR], &rect_dest);
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_HEALTH_POWERUP], &rect_dest);
                    break;
                case SKULL:
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_FLOOR], &rect_dest);
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_SKULL], &rect_dest);
                    break;
                case TORCH:
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_FLOOR], &rect_dest);
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_TORCH], &rect_dest);
                    break;
                case FIRE:
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_FLOOR], &rect_dest);
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_FIRE], &rect_dest);
                    break;
                case BLOOD:
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_FLOOR], &rect_dest);
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_BLOOD], &rect_dest);
                    break;
                case 'o':
                    SDL_RenderCopy(renderer, texture->floor, &Rect_source, &Rect_dest);
                    SDL_RenderCopy(renderer, texture->door, &Rect_source, &Rect_dest);
                    break;
                case 'A':
                    SDL_RenderCopy(renderer, texture->floor, &Rect_source, &Rect_dest);
                    SDL_RenderCopy(renderer, texture->monster_a, &Rect_source, &Rect_dest);
                    break;
                case 'B':
                    SDL_RenderCopy(renderer, texture->floor, &Rect_source, &Rect_dest);
                    SDL_RenderCopy(renderer, texture->monster_b, &Rect_source, &Rect_dest);
                    break;
                case 'C':
                    SDL_RenderCopy(renderer, texture->floor, &Rect_source, &Rect_dest);
                    SDL_RenderCopy(renderer, texture->monster_c, &Rect_source, &Rect_dest);
                    break;
                default:
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_FLOOR], &rect_dest);
                    break;
            }
        }
    }
}

void draw_lights(SDL_Renderer* renderer, Room *room, Texture *texture, Animator *animator) {
    SDL_Rect rect_dest;
    rect_dest.w = LIGHT_SIZE;
    rect_dest.h = LIGHT_SIZE;
    /* Draw light over room objects */
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            rect_dest.x = i * DRAW_TILE_SIZE;
            rect_dest.y = j * DRAW_TILE_SIZE;
            switch (room->tiles[j][i]) {
                /* Torch light */
                case FIRE:
                    rect_dest.x = i * TILE_SIZE - LIGHT_SIZE / 2 + TILE_SIZE / 2;
                    rect_dest.y = j * TILE_SIZE - LIGHT_SIZE / 2 + TILE_SIZE / 2;
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_LIGHT], &rect_dest);
                    break;
                default:
                    break;
            }
        }
    }
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
    }
}

void draw_player(SDL_Renderer *renderer, Player *player, Texture * texture) {
    SDL_Rect newRect = {player->coordinate[0]*TILE_SIZE, player->coordinate[1]*TILE_SIZE, 24, 24};
    SDL_RenderCopy(renderer, texture->player, NULL, &newRect);
}
