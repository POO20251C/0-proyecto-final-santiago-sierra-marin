#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include "character.h" // Inheritance from Character

class Enemy : public Character {
public:
    std::string category;
    Enemy(const std::string& n, int hp_, int atk_, int def_, int spd_, int lck_, const std::string& cat);
};

#endif // ENEMY_H