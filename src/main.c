#include <stdio.h>
#include <string.h>
#include <../include/SDL2/SDL.h>
#include "../include/renderer.h"
#include "../include/texture.h"
/* will be replaced with main game struct when it is done */
#include "../include/room.h"
#include "../include/floor.h"
#include "../include/player.h"
#include "../include/monster_hashtbl.h"
#include "../include/maze.h"
#include "../include/gui.h"
#include "../include/interface.h"

int event_on_tiles(char *tile, State *state, Direction dir)
{
  /* return 1 if the player can go on this tile and 0 otherwise */
  /* operates here events of special tiles */
  switch (*tile)
  {
  case '#': // empty
    return 0;
    break;
  case '?': // exit
    *(state->current_room) = *(state->current_room->neighbors[dir]);
    switch (dir)
    {
    case NORTH:
      state->player->coordinate[y] = ROOM_SIZE - 1;
      break;
    case SOUTH:
      state->player->coordinate[y] = 0;
      break;
    case EAST:
      state->player->coordinate[x] = 0;
      break;
    case WEST:
      state->player->coordinate[x] = ROOM_SIZE - 1;
      break;
    }
    return 1;
    break;
  case '!': // key
    update_key(&(state->player->key_number), 1);
    *tile = ' ';
    return 1;
    break;
  case '1':
    // attack powerup
    // increase by one the attack of the player
    update_stats((state->player->stats), attack);
    *tile = ' ';
    return 1;
    break;
  case '2':
    // defense powerup
    // increase by one the defense of the player
    update_stats((state->player->stats), defense);
    *tile = ' ';
    return 1;
    break;
  case '3':
    // health powerup
    // increase by three health and max_health
    update_max_health((state->player->health), 3);
    *tile = ' ';
    return 1;
    break;
  default:
    return 1;
    break;
  }
  return 0;
}

void move(State *state, char *next_tile, void (*pf)(int *), Direction d)
{
  if (event_on_tiles(next_tile, state, d))
    (*pf)(state->player->coordinate);
}

int main()
{
  SDL_Event event;
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  Uint32 last_update = SDL_GetTicks();

  int quit = 0;
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

  /* Creation of main structure and initialize player at coordinate (15;15) */
  Maze *maze = create_maze("maze/", 15, 15);

  /* Overload certain maze declarations to reduce later code */
  Room *c_room = maze->state->current_room;
  Floor *c_floor = maze->state->current_floor;
  Player *player = maze->state->player;

  Texture *texture = load_textures(renderer);

  Interface *interface = load_interfaces(renderer);

  while (!quit)
  {
    if (get_current_screen() == 0)
    {
      quit = 1;
      break;
    }

    while (SDL_PollEvent(&event) != 0)
    {
      switch (event.type)
      {
      case SDL_QUIT:
        quit = 1;
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_a:
        case SDLK_q:
        case SDLK_LEFT:
          move(maze->state, &(c_room->tiles[player->coordinate[1]][(player->coordinate[0] - 1)]), &go_left, WEST);
          break;
        case SDLK_d:
        case SDLK_RIGHT:
          move(maze->state, &(c_room->tiles[player->coordinate[1]][(player->coordinate[0] + 1)]), &go_right, EAST);
          break;
        case SDLK_w:
        case SDLK_z:
        case SDLK_UP:
          move(maze->state, &(c_room->tiles[(player->coordinate[1]) - 1][player->coordinate[0]]), &go_up, NORTH);
          break;
        case SDLK_s:
        case SDLK_DOWN:
          move(maze->state, &(c_room->tiles[(player->coordinate[1]) + 1][player->coordinate[0]]), &go_down, SOUTH);
          break;
        case SDLK_p:
          display_player(player);
          break;
        case SDLK_ESCAPE:
          if (get_current_screen() == 2) {
            set_current_screen(1);
          } else {
            set_current_screen(2);
          }  
        default:
          break;
        }
        break;
      case SDL_MOUSEBUTTONDOWN:
        for (int i = 0; i < (int)sizeof(interface->menu) / sizeof(interface->menu[0]); i++)
        {
          if (gui_clicked(event.button, interface->menu[i]))
          {
            interface->menu[i]->callback(i);
          }
        }
        for (int i = 0; i < (int)sizeof(interface->hud) / sizeof(interface->hud[0]); i++)
        {
          if (gui_clicked(event.button, interface->hud[i]))
          {
            interface->menu[i]->callback(i);
          }
        }
        break;
      default:
        break;
      }
    }

    /* drawing */
    SDL_RenderClear(renderer);
    draw_game(renderer, c_floor, c_room, player, texture);
    draw_gui(renderer, interface);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();
  return 0;
}
