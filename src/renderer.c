#include<renderer.h>

void draw_game(SDL_Renderer* renderer, Floor *floor, Room *target_room, Player *player, Texture *texture) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    draw_room(renderer, target_room, texture);
    draw_minimap(renderer, floor, target_room);
    draw_player(renderer, player, texture);
    draw_doors(renderer, target_room, texture);
    draw_lights(renderer, target_room, texture);
}

void draw_room(SDL_Renderer* renderer, Room *room, Texture *texture) {
    SDL_Rect rect_dest;
    rect_dest.w = DRAW_TILE_SIZE;
    rect_dest.h = DRAW_TILE_SIZE;

    SDL_Rect upper_rect_dest;
    upper_rect_dest.w = DRAW_TILE_SIZE;
    upper_rect_dest.h = DRAW_TILE_SIZE;
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            rect_dest.x = i * DRAW_TILE_SIZE;
            rect_dest.y = j * DRAW_TILE_SIZE;
            upper_rect_dest.x = i * DRAW_TILE_SIZE;
            upper_rect_dest.y = j * DRAW_TILE_SIZE - TILE_SIZE / 4;
            switch (room->tiles[j][i]) {
                case EMPTY:
                    if (j - 1 >= 0 && room->tiles[j-1][i] != '#') {
                        SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_WALL], &rect_dest);
                    } else { SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_VOID], &rect_dest); }
                    break;
                case KEY:
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_FLOOR], &rect_dest);
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_KEY], &upper_rect_dest);
                    break;
                case POTION:
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_FLOOR], &rect_dest);
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_POTION], &upper_rect_dest);
                    break;
                case ATTACK_POWERUP:
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_FLOOR], &rect_dest);
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_ATTACK_POWERUP], &upper_rect_dest);
                    break;
                case DEFENSE_POWERUP:
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_FLOOR], &rect_dest);
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_DEFENSE_POWERUP], &upper_rect_dest);
                    break;
                case HEALTH_POWERUP:
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_FLOOR], &rect_dest);
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_HEALTH_POWERUP], &upper_rect_dest);
                    break;
                case BLOOD1:
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_BLOOD1], &rect_dest);
                    break;
                case BLOOD2:
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_BLOOD2], &rect_dest);
                    break;
                case CRACKED:
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_CRACKED], &rect_dest);
                    break;
                case FIRE:
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_FLOOR], &rect_dest);
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_FIRE], &rect_dest);
                    break;
                case MONSTER_A:
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_FLOOR], &rect_dest);
                    draw_monster(renderer, i, j, room->tiles[j][i], texture);
                    break;
                case MONSTER_B:
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_FLOOR], &rect_dest);
                    draw_monster(renderer, i, j, room->tiles[j][i], texture);
                    break;
                case MONSTER_C:
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_FLOOR], &rect_dest);
                    draw_monster(renderer, i, j, room->tiles[j][i], texture);
                    break;
                default:
                    SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_FLOOR], &rect_dest);
                    break;
            }
        }
    }
}

void draw_lights(SDL_Renderer* renderer, Room *room, Texture *texture) {
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
        if (floor->rooms[i] == target_room) {
            SDL_SetRenderDrawColor(renderer, 124, 123, 171, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 80, 79, 110, 255);
        }
        Rect_dest.x = WINDOW_WIDTH - 100 + floor->rooms[i]->x * DRAW_TILE_SIZE;
        Rect_dest.y = floor->rooms[i]->y * DRAW_TILE_SIZE + 10;
        SDL_RenderDrawRect(renderer, &Rect_dest);
    }
}

void draw_monster(SDL_Renderer *renderer, int x, int y, char monster_type, Texture *texture) {
    SDL_Rect rect_dest = {x * TILE_SIZE, y * TILE_SIZE - TILE_SIZE / 4, 24, 24};
    switch (monster_type) {
        case 'A':
            SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_MONSTER_A], &rect_dest);
            break;
        case 'B':
            SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_MONSTER_B], &rect_dest);
            break;
        case 'C':
            SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_MONSTER_C], &rect_dest);
            break;
        default:
            break;
    }
}

void draw_player(SDL_Renderer *renderer, Player *player, Texture * texture) {
    SDL_Rect rect_dest = {player->coordinate[0] * TILE_SIZE, player->coordinate[1] * TILE_SIZE - TILE_SIZE / 4, 24, 24};
    switch (player->direction) {
        case left:
            SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_PLAYER_LEFT], &rect_dest);
            break;
        case right:
            SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_PLAYER_RIGHT], &rect_dest);
            break;
        case back:
            SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_PLAYER_BACK], &rect_dest);
            break;
        case front:
            SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_PLAYER_FRONT], &rect_dest);
            break;
        default:
            break;
        }
}

void draw_doors(SDL_Renderer *renderer, Room *room, Texture *texture) {
    SDL_Rect rect_dest;
    rect_dest.w = TILE_SIZE;
    rect_dest.h = TILE_SIZE * 2;
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            rect_dest.x = i * DRAW_TILE_SIZE;
            rect_dest.y = (j-1) * DRAW_TILE_SIZE;
            if (room->tiles[j][i] == DOOR) {
                SDL_RenderCopy(renderer, texture->tileset, &texture->rects[RECT_DOOR], &rect_dest);
            }
        }
    }
}
