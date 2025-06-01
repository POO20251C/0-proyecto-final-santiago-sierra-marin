#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

class Character {
public:
    std::string name;
    int max_hp;
    int hp;
    int atk;
    int def;
    int spd;
    int lck;

    Character(const std::string& n, int hp_, int atk_, int def_, int spd_, int lck_);
    virtual ~Character() = default;
    bool isAlive() const;
};

#endif // CHARACTER_H#ifndef CHARACTER_H
