#ifndef HERO_H
#define HERO_H

#include <string>
#include <vector>
#include "character.h" // Inheritance from Character
#include "item.h"      // Using Item in inventory

class Hero : public Character {
public:
    std::vector<Item> inventory;
    int potions;
    Hero(const std::string& n, int hp_, int atk_, int def_, int spd_, int lck_);
    void equip(const Item& item);
    void heal();
};

#endif // HERO_H