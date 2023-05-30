#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/monster_hashtbl.h"
#include "../include/monster.h"

int main(int argc, char const *argv[])
{
  Monster * m = create_monster(0, 0, 1);
  Elem * e = (Elem *) malloc(sizeof(Elem));
  reset_elem(e, 0, 0, 1, m);

  Monster * m1 = create_monster(1, 2, 1);
  Elem * e1 = (Elem *) malloc(sizeof(Elem));
  reset_elem(e1, 1, 2, 1, m1);

  Monster * m2 = create_monster(2, 1, 1);
  Elem * e2 = (Elem *) malloc(sizeof(Elem));
  reset_elem(e2, 2, 1, 1, m2);

  Monster * m3 = create_monster(0, 3, 1);
  Elem * e3 = (Elem *) malloc(sizeof(Elem));
  reset_elem(e3, 0, 3, 1, m3);


  Hashtbl * h = create_hashtbl();

  display_h(h);
  printf("_____\n\n");

  insert_monster(h, 0, 0, 1, m);
  display_h(h);
  printf("_____\n\n");

  insert_monster(h, 1, 2, 1, m1);
  display_h(h);
  printf("_____\n\n");

  insert_monster(h, 2, 1, 1, m2);
  display_h(h);
  printf("_____\n\n");

  insert_monster(h, 0, 3, 1, m3);
  display_h(h);
  printf("_____\n\n");

  display_monster(find_monster(h, 0, 0, 1));
  display_h(h);
  printf("_____\n\n");
  remove_monster(h, 0, 0, 1);
  display_h(h);
  printf("_____\n\n");
  insert_monster(h, 0, 0, 1, m);
  display_h(h);
  printf("_____\n\n");

  if (find_monster(h, 0, 0, 1) == NULL) printf("m existe pas\n");
  else printf("m existe\n");
  printf("_____\n\n");

  insert_monster(h, 0, 0, 9, m3);
  display_h(h);
  printf("_____\n\n");

  insert_monster(h, 0, 0, 9, m3);
  display_h(h);
  printf("_____\n\n");

  return 0;
}
