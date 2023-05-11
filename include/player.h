#ifndef HEADER_FILE
#define HEADER_FILE

struct Player {
  /* health[0] -> current health
     health[1] -> max health */
  int health[2];
  /* stats[0] -> attack damage
     stats[1] -> defense */
  int stats[2];
  int key_number;
  int room_id;
  /* coordinate[0] -> x position in current room
     coordinate[1] -> y position in current room */
  int coordinate[2];
} player;

/* moving functions */
void go_left(int* coordinate[]);
void go_right(int* coordinate[]);
void go_top(int* coordinate[]);
void go_down(int* coordinate[]);

/* stats functions */
void set_max_health(int* health[]);
void update_max_health(int* health[]);
void update_stats(int* stats[]);
void update_key(int* key_number, int update);

#endif
