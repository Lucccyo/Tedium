#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "../include/monster_hashtbl.h"

void reset_elem (Elem * e, int x, int y, int room_id, struct monster * m) {
  e->key = x + y + room_id;
  e->x = x;
  e->y = y;
  e->room_id = room_id;
  e->value = m;
}

Hashtbl * create_hashtbl () {
  Hashtbl * h = (Hashtbl*) malloc(sizeof(Hashtbl));
  for (int i = 0 ; i < MAX_SIZE ; i++) {
    Elem * e = (Elem*) malloc(sizeof(Elem));
    e->key = -1;
    h->array[i] = e;
  }
  h->cap = MAX_SIZE;
  h->size = 0;
  return h;
}

int hash(int x, int y, int room_id, int array_cap) {
  return (x + y + room_id) % array_cap;
}

void display_e(Elem * e){
  printf(
    "key  = %d\n"
    "[monster]\n",
    e->key);
  printf("\n");
}

void display_h(Hashtbl * h){
  printf(
    "cap  = %d\n"
    "size = %d\n",
    h->cap,
    h->size);
  for (int i = 0; i < h->cap ; i++) {
    if (h->array[i]->key != -1)
      printf("[%d] -> %d ", i, h->array[i]->key);
  }
  printf("\n");
}

void insert_monster (Hashtbl * h, int x, int y, int room_id, struct monster * m) {
  int i = hash(x, y, room_id, h->cap);
  /* if the slot is already filled, we check for the next one (open addressing)*/
  while (h->array[i]->key != -1 || i >= h->cap) {
  printf("i = %d\n", i);
    i++;
    if (i >= h->cap){
      assert(false);
      /* We resize by multiplying the hashtable by two, to store more values */
      // h->array[0] = (Elem *) realloc((void*) h->array, sizeof(Elem)*2*h->cap);
      // (h->cap)*=2;
    }
  }
  reset_elem(h->array[i], x, y, room_id, m);
  (h->size)++;
}

Monster * linear_search(Hashtbl * h, int x, int y, int room_id, int *i){
  if (*i >= h->cap || *i < 0) return NULL;
  if (h->array[*i]->x == x &&
      h->array[*i]->y == y &&
      h->array[*i]->room_id == room_id)
    return h->array[*i]->value;
  else { (*i)++;
    return(linear_search(h, x, y, room_id, i)); }
}

Monster * find_monster(Hashtbl * h, int x, int y, int room_id) {
  int i = hash(x, y, room_id, h->cap);
  return(linear_search(h, x, y, room_id, &i));
}

void remove_monster (Hashtbl * h, int x, int y, int room_id) {
  int i = hash(x, y, room_id, h->cap);
  while (h->array[i]->x != x || h->array[i]->y != y || h->array[i]->room_id != room_id) {
    if (i >= h->cap) return;
    i++; }
  Monster * m = h->array[i]->value;
  h->array[i]->key = -1;
  (h->size)--;
  free(m);
}
