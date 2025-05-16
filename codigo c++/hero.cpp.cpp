#include "hero.h"
#include <algorithm>

Hero::Hero(const std::string& n, int hp_, int atk_, int def_, int spd_, int lck_)
    : Character(n, hp_, atk_, def_, spd_, lck_), potions(0) {}
void Hero::equip(const Item& item) { item.apply(*this); inventory.push_back(item); }
void Hero::heal() { if(potions>0){ hp = std::min(max_hp, hp+50); --potions; }}