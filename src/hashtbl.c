#include <stdlib.h>
#include "hashtbl.h"

void ht_init(Hashtbl * h, unsigned int cap) {
  h->capacity = cap;
  h->size = 0;
  h->keys = calloc(cap, sizeof(unsigned int));
  h->values = calloc(cap, sizeof(void *));
}

void ht_destroy(Hashtbl * h) {
  free(h->keys);
  free(h->values);
  h->capacity = 0;
  h->size = 0;
  h->keys = NULL;
  h->values = NULL;
}

void * ht_insert(Hashtbl * h, unsigned int key, void * value);

static void resize(Hashtbl * h) {
  Hashtbl nh = {0};
  unsigned int c = h->capacity;
  ht_init(&nh, c * 2);
  for (int i = 0; i < c; i++) {
    unsigned int k = h->keys[i];
    if (k) ht_insert(&nh, k, h->values[i]);
  }
  free(h->keys);
  free(h->values);
  *h = nh;
}

void * ht_delete(Hashtbl * h, unsigned int key);

void * ht_insert(Hashtbl * h, unsigned int key, void * value) {
  if (!key) return NULL;
  if (!value) return ht_delete(h, key);
  unsigned int c = h->capacity;
  if (h->size * 2 >= c) resize(h);
  unsigned int i = key % c;
  for (;;) {
    unsigned int k = h->keys[i];
    if (k == 0) { h->keys[i] = key; break; }
    if (k == key) break;
    i = (i + 1) % c;
  }
  void * v = h->values[i];
  h->values[i] = value;
  h->size++;
  return v;
}

void * ht_lookup(Hashtbl * h, unsigned int key) {
  if (!key) return NULL;
  unsigned int c = h->capacity;
  unsigned int i = key % c;
  for (;;) {
    unsigned int k = h->keys[i];
    if (k == 0) return NULL;
    if (k == key) return h->values[i];
    i = (i + 1) % c;
  } 
}

void * ht_delete(Hashtbl * h, unsigned int key) {
  if (!key) return NULL;
  unsigned int c = h->capacity;
  unsigned int i = key % c;
  for (;;) {
    unsigned int k = h->keys[i];
    if (k == 0) return NULL;
    if (k == key) break;
    i = (i + 1) % c;
  }
  void * v = h->values[i];
  unsigned int j = (i + 1) % c;
  for(;;){
    unsigned int k = h->keys[j];
    if (k == 0) break;
    unsigned int d = k % c;
    if ((d <= i) ? (i < j || j < d)
		 : (i < j && j < d)) {
      h->keys[i] = k;
      h->values[i] = h->values[j];
      i = j;
    } 
    j = (j + 1) % c;
  }
  h->size--;
  h->keys[i] = 0;
  h->values[i] = NULL;
  return v;
}
