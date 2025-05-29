#include "character.h"

Character::Character(const std::string& n, int hp_, int atk_, int def_, int spd_, int lck_)
    : name(n), max_hp(hp_), hp(hp_), atk(atk_), def(def_), spd(spd_), lck(lck_) {}
bool Character::isAlive() const { return hp > 0; }