#ifndef HASHTBL_FILE
#define HASHTBL_FILE

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "monster.h"

/* initializing the Hashtbl capacity to 1024 */
#define MAX_SIZE 1024

struct elem {
  /* the sum of x, y, room_name and floor_num */
  int key;
  int x_tile;
  int y_tile;
  char room_name[15];
  int floor_num;
  Monster * value;
};
typedef struct elem Elem;

struct hashtbl {
  Elem * array[MAX_SIZE];
  int cap;
  int size;
};
typedef struct hashtbl Hashtbl;

Hashtbl * create_hashtbl();

void insert_monster (
    Hashtbl * h,
    int x_tile, int y_tile,
    char room_name[],
    int floor_num,
    int health_max,
    int attack, int defense);

void reset_elem (
    Elem * e,
    int x_tile, int y_tile,
    char room_name[],
    int floor_num,
    Monster * m);

Monster * find_monster (Hashtbl * h, int x, int y, char room_name[], int floor_num);
void remove_monster    (Hashtbl * h, int x, int y, char room_name[], int floor_num);

void display_hashtbl(Hashtbl * h);

void free_elem(Elem * elem);

void free_hashtbl(Hashtbl * hashtbl);

#endif
