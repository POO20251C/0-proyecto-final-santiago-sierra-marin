#ifndef COMBAT_H
#define COMBAT_H

#include "character.h" // Forward declaration needed in .h
#include <random>

std::mt19937& get_rng();
bool calculateHit(const Character& atk, const Character& def);
int calculateDamage(const Character& atk, const Character& def);

#endif // COMBAT_H#ifndef COMBAT_H
