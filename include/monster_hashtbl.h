#ifndef HASHTBL_FILE
#define HASHTBL_FILE

#include "monster.h"
#define MAX_SIZE 1024

struct elem {
  /* the sum of x,y and room_id */
  int key;
  int x;
  int y;
  int room_id;
  Monster * value;
};
typedef struct elem Elem;

struct hashtbl {
  Elem * array[MAX_SIZE];
  int cap;
  int size;
};
typedef struct hashtbl Hashtbl;

Hashtbl * create_hashtbl ();
void reset_elem (Elem * e, int x, int y, int room_id, struct monster * m);
void insert_monster (Hashtbl * h, int x, int y, int room_id, struct monster * m);
void display_h (Hashtbl * h);
void display_e (Elem * h);

Monster * find_monster(Hashtbl * h, int x, int y, int room_id);
void remove_monster (Hashtbl * h, int x, int y, int room_id);

#endif
