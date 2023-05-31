#ifndef HASHTBL_FILE
#define HASHTBL_FILE

#include "monster.h"
#define MAX_SIZE 1024

struct elem {
  /* the sum of x, y, room_name and floor_num */
  int key;
  Monster * value;
  int x_tile;
  int y_tile;
  char room_name[15];
  int floor_num;
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

#endif
