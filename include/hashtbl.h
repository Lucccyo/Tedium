#ifndef HASHTBL_FILE
#define HASHTBL_FILE

typedef struct hashtbl {
  unsigned int capacity;
  unsigned int size;
  unsigned int * keys;
  void ** values;
} Hashtbl;

void ht_init(Hashtbl * h, unsigned int cap);
void ht_destroy(Hashtbl * h); 
void * ht_insert(Hashtbl * h, unsigned int key, void * value);
void * ht_lookup(Hashtbl * h, unsigned int key);
void * ht_delete(Hashtbl * h, unsigned int key);

#endif
