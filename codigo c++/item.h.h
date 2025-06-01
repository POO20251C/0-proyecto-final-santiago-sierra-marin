#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "character.h" // Dependency on Character

class Item {
public:
    std::string name;
    int bonus_atk, bonus_def, bonus_lck, bonus_spd, bonus_hp;
    Item(const std::string& n, int ba=0, int bd=0, int bl=0, int bs=0, int bh=0);
    void apply(Character& c) const;
    std::string description() const;
};

#endif // ITEM_H