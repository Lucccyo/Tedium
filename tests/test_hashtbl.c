#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "monster_hashtbl.h"
#include "monster.h"

int main(int argc, char const *argv[]) {

  Hashtbl * h = create_hashtbl();
  insert_monster(h, 1, 1, "bonj", 1, 14, 2, 3);
  insert_monster(h, 0, 1, "bosnj", 2, 9, 45, 38);
  display_monster(find_monster(h, 1, 1, "bonj", 1));
  display_monster(find_monster(h, 0, 1, "bosnj", 2));

  return 0;
}
