#include <stdio.h>
#include "../include/monster.h"
#include "../include/player.h"

void do_attack_cycle(Player *player, Monster *monster) {
    int plrDamage = player->stats[attack] - monster->stats[defense];
    plrDamage = plrDamage < 1 ? 1 : plrDamage; // at least one hp is lost every time
    update_health_monster(monster->health, -plrDamage);

    int monsterDamage = monster->stats[attack] - player->stats[defense];
    monsterDamage = monsterDamage < 1 ? 1 : monsterDamage;
    update_health(player->health, -monsterDamage);

    // si le monstre est mort, le joueur gagne un bonus
    if (monster->health[0] <= 0) {
        update_max_health(player->health, 1);
        update_stats(player->stats, attack);
    }
}