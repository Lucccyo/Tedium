#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <SDL2/SDL_mixer.h>
#include <time.h>
#include "renderer.h"
#include "texture.h"
/* will be replaced with main game struct when it is done */
#include "room.h"
#include "floor.h"
#include "player.h"
#include "monster_hashtbl.h"
#include "monster.h"
#include "maze.h"
#include "animator.h"
#include "../include/gui.h"
#include "../include/interface.h"

#include "SDL2/SDL_ttf.h"
#include "audio.h"

// Redefine main on windows
#ifdef __WIN32__
#undef main
#endif
int event_on_tiles(int x_tile, int y_tile, Maze *maze, Direction dir, Sound *sounds)
{
  /* return 1 if the player can go on this tile and 0 otherwise */
  /* operates here events of special tiles */
  srand(time(NULL));
  char *tile = &(maze->state->current_room->tiles[x_tile][y_tile]);
  Monster *monster;
  switch (*tile)
  {
  case '#':
    // empty
    return 0;
    break;
  case '?':
    // exit
    maze->state->current_room = maze->state->current_room->neighbors[dir];
    switch (dir)
    {
    case NORTH:
      maze->state->player->coordinate[y] = ROOM_SIZE - 1;
      break;
    case SOUTH:
      maze->state->player->coordinate[y] = 0;
      break;
    case EAST:
      maze->state->player->coordinate[x] = 0;
      break;
    case WEST:
      maze->state->player->coordinate[x] = ROOM_SIZE - 1;
      break;
    }
    return 1;
    break;
  case '!':
    // key
      play_key_pickup_sound(sounds);
    update_key(&(maze->state->player->key_number), 1);
    *tile = ' ';
    return 1;
    break;
  case '1':
    // attack powerup
    // increase by one the attack of the player
      play_powerup_pickup_sound(sounds);
    update_stats((maze->state->player->stats), attack);
    *tile = ' ';
    return 1;
    break;
  case '2':
    // defense powerup
    // increase by one the defense of the player
      play_powerup_pickup_sound(sounds);
    update_stats((maze->state->player->stats), defense);
    *tile = ' ';
    return 1;
    break;
  case '3':
    // health powerup
    // increase by three health and max_health
      play_powerup_pickup_sound(sounds);
    update_max_health((maze->state->player->health), 3);
    *tile = ' ';
    return 1;
    case '7':
    // Fire decoration
    // Block the player
      return 0;
      break;
  case 'Z':
    // potion
      play_heal_sound(sounds);
    full_health(maze->state->player->health);
    *tile = ' ';
    return 1;
  case 'A' ... 'Y': // 'Z' is used for keys
      play_attack_sound(sounds);
    monster = find_monster(maze->monsters,
                           y_tile, x_tile,
                           maze->state->current_room->name,
                           maze->state->current_floor->id);
    int delta_atk = maze->state->player->stats[attack] - monster->stats[defense];
    update_health_monster(monster->health, ((delta_atk > 0) ? -delta_atk : -1));
    if (monster->health[0] <= 0)
    {
        play_enemy_death_sound(sounds);
      printf("\033[1;31mle monstre est mort\033[0m\n");
      remove_monster(maze->monsters,
                     y_tile, x_tile,
                     maze->state->current_room->name,
                     maze->state->current_floor->id);
      /* When defeated, the monster drops a random powerup. */
      update_max_health(maze->state->player->health, 1);
      update_stats(maze->state->player->stats, attack);
      *tile = (rand() % 3) + '1';
      return 0;
      break;
    }
    delta_atk = monster->stats[attack] - maze->state->player->stats[defense];
    update_health(maze->state->player->health, ((delta_atk > 0) ? -delta_atk : -1));
    if (maze->state->player->health[0] <= 0)
    {
        play_player_death_sound(sounds);
      printf("\033[1;31mGAME OVER\033[0m\n");
    }
    display_player(maze->state->player);
    return 0;
    break;
  case 'o':
    // door
    if (maze->state->player->key_number > 0)
    {
        play_open_door_sound(sounds);
      update_key(&(maze->state->player->key_number), -1);
      printf("\033[1;31mLa porte est ouverte.\033[0m\n");
      *tile = ' ';
    }
    return 0;
    break;
  default:
    return 1;
    break;
  }
  return 0;
}

void move(Maze * maze, int x, int y, void (*pf)(int *), Direction d, Sound *sounds) {
  if (event_on_tiles(x, y, maze, d, sounds))
    (*pf)(maze->state->player->coordinate);
}

int main()
{
  SDL_Event event;
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;

  int quit = 0;
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("Error inititializing SDL: %s\n", SDL_GetError());
    return 1;
  }

  if (TTF_Init() < 0)
  {
    // Error handling code
    printf("Error inititializing TTF: %s\n", TTF_GetError());
    return 1;
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
  {
    printf("Error initializing SDL_mixer: %s\n", Mix_GetError());
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

  if (Mix_Init(0) < 0) {
    printf("Error initializing SDL_mixer: %s\n", Mix_GetError());
    return 1;
  }

  /* Creation of main structure and initialize player at coordinate (15;15) */
  Maze *maze = create_maze("maze/", 15, 15);
  Animator *animator = create_animator();
  Texture *texture = load_textures(renderer);
  Interface *interface = load_interfaces(renderer, maze);

  /* musics tests */
  Sound *sounds = create_sounds();
  while (!quit)
  {
    // Quit game on quit button clicked
    if (get_current_screen() == 0)
    {
      quit = 1;
      break;
    }

    while (SDL_PollEvent(&event) != 0) {
      switch (event.type) {
        case SDL_QUIT:
          quit = 1;
          break;
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
            case SDLK_a:
            case SDLK_q:
            case SDLK_LEFT:
            move(maze, maze->state->player->coordinate[1],
                 maze->state->player->coordinate[0] - 1, &go_left, WEST, sounds);
            break;
            case SDLK_d:
            case SDLK_RIGHT:
              move(maze, maze->state->player->coordinate[1],
                   maze->state->player->coordinate[0] + 1, &go_right, EAST, sounds);
              break;
            case SDLK_w:
            case SDLK_z:
            case SDLK_UP:
              move(maze, maze->state->player->coordinate[1] - 1,
                   maze->state->player->coordinate[0], &go_up, NORTH, sounds);
              break;
            case SDLK_s:
            case SDLK_DOWN:
              move(maze, maze->state->player->coordinate[1] + 1,
                   maze->state->player->coordinate[0], &go_down, SOUTH, sounds);
              break;
            case SDLK_p:
              display_player(maze->state->player);
              break;
            /* debug purpose */
            case SDLK_v:
              Mix_PlayMusic(sounds->musics[1], -1);
            default:
              break;
          } break;
        default: break;
      }
    }
    /* drawing */
    SDL_RenderClear(renderer);
    animation_step(animator, texture);
    play_music(sounds);
    draw_game(renderer, maze->state->current_floor, maze->state->current_room, maze->state->player, texture);
    draw_gui(renderer, interface);

    SDL_RenderPresent(renderer);
  }

  Mix_CloseAudio();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  destroy_interface(interface);

  TTF_Quit();

  SDL_Quit();
  return 0;
}
