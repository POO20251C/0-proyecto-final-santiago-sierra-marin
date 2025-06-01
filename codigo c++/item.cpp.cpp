#include "item.h"
#include <string>

Item::Item(const std::string& n, int ba, int bd, int bl, int bs, int bh)
    : name(n), bonus_atk(ba), bonus_def(bd), bonus_lck(bl), bonus_spd(bs), bonus_hp(bh) {}
void Item::apply(Character& c) const {
    c.atk += bonus_atk;
    c.def += bonus_def;
    c.lck += bonus_lck;
    c.spd += bonus_spd;
    c.max_hp += bonus_hp;
    c.hp += bonus_hp;
}
std::string Item::description() const {
    std::string desc = name + ": ";
    if(bonus_atk) desc += "+" + std::to_string(bonus_atk) + " ATK ";
    if(bonus_def) desc += "+" + std::to_string(bonus_def) + " DEF ";
    if(bonus_lck) desc += "+" + std::to_string(bonus_lck) + " LCK ";
    if(bonus_spd) desc += "+" + std::to_string(bonus_spd) + " SPD ";
    if(bonus_hp)  desc += "+" + std::to_string(bonus_hp)  + " HP ";
    return desc;
}