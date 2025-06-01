#ifndef DUNGEON_H
#define DUNGEON_H

#include <string>
#include <vector>
#include "hero.h"        // Using Hero
#include "enemy.h"       // Using Enemy
#include "item.h"        // Using Item
#include "scoremanager.h" // Using ScoreManager

class Dungeon {
    std::vector<Hero>& heroes;
    std::vector<Enemy>& bosses;
    std::vector<Item> itemPool;
    int room;
    int hp_lost;
public:
    Dungeon(std::vector<Hero>&h, std::vector<Enemy>&b);
    void run(const std::string& alias);
private:
    Enemy spawnEnemy();
    void handleEvents();
    void battle(Enemy enemy);
    std::string currentDateTime();
};

#endif // DUNGEON_H