#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "../include/monster_hashtbl.h"

void reset_elem (Elem * e, int x, int y, char room_name[], int floor_num, Monster * m) {
  e->key = x + y + floor_num;
  e->x_tile = x;
  e->y_tile = y;
  strcpy(e->room_name, room_name);
  e->floor_num = floor_num;
  e->value = m;
}

Hashtbl * create_hashtbl(){
  Hashtbl * h = malloc(sizeof(Hashtbl));
  for (int i = 0 ; i < MAX_SIZE ; i++) {
    Elem * e = (Elem*) malloc(sizeof(Elem));
    e->key = -1;
    h->array[i] = e;
  }
  h->cap = MAX_SIZE;
  h->size = 0;
  return h;
}

int hash(int x, int y, int floor_num, char room_name[], int array_cap) {
  int i = room_name[4] + room_name[5];
  return (x + y + floor_num + i) % array_cap;
}

void insert_monster (Hashtbl * h,
                     int x_tile, int y_tile,
                     char room_name[], int floor_num,
                     int health_max, int attack, int defense) {
  int i = hash(x_tile, y_tile, floor_num, room_name, h->cap);
  /* if the slot is already filled, we check for the next one (open addressing)*/
  while (h->array[i]->key != -1 || i >= h->cap) {
    i++;
    if (i >= h->cap){
      assert(false);
      /* We resize by multiplying the hashtable by two, to store more values */
      // h->array[0] = (Elem *) realloc((void*) h->array, sizeof(Elem)*2*h->cap);
      // (h->cap)*=2;
    }
  }
  Monster * m = create_monster(health_max, attack, defense, x_tile, y_tile);
  reset_elem(h->array[i], x_tile, y_tile, room_name, floor_num, m);
  (h->size)++;
}

Monster * linear_search(Hashtbl * h, int x, int y, char room_name[], int floor_num, int *i){
  if (*i >= h->cap || *i < 0) return NULL;
  if (h->array[*i]->x_tile == x &&
      h->array[*i]->y_tile == y &&
      (strcmp(h->array[*i]->room_name, room_name) == 0) &&
      h->array[*i]->floor_num == floor_num)
    return h->array[*i]->value;
  else { (*i)++;
    return(linear_search(h, x, y, room_name, floor_num, i)); }
}

Monster * find_monster(Hashtbl * h, int y, int x, char room_name[], int floor_num) {
  int i = hash(x, y, floor_num, room_name, h->cap);
  return(linear_search(h, y, x, room_name, floor_num, &i));
}

void remove_monster (Hashtbl * h, int x, int y, char room_name[], int floor_num) {
  int i = hash(x, y, floor_num, room_name, h->cap);
  while (h->array[i]->x_tile != x ||
         h->array[i]->y_tile != y ||
         h->array[i]->floor_num != floor_num ||
         (strcmp(h->array[i]->room_name, room_name) != 0)) {
    if (i >= h->cap) return;
    i++;
  }
  Monster * m = h->array[i]->value;
  h->array[i]->key = -1;
  (h->size)--;
  free(m);
}

void display_hashtbl(Hashtbl * h){
  printf(
    "cap  = %d\n"
    "size = %d\n",
    h->cap,
    h->size);
  for (int i = 0; i < h->cap ; i++) {
    if (h->array[i]->key != -1)
      printf("   [%d] -> (%d;%d)   ", i, h->array[i]->value->health[0], h->array[i]->value->health[1]);
  }
  printf("\n");
}
