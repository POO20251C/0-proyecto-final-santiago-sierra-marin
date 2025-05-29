#include "enemy.h"

Enemy::Enemy(const std::string& n, int hp_, int atk_, int def_, int spd_, int lck_, const std::string& cat)
    : Character(n, hp_, atk_, def_, spd_, lck_), category(cat) {}