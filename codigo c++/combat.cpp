#include "combat.h"
#include <algorithm>
#include <random>
#include <chrono>

static std::mt19937 rng((unsigned)std::chrono::system_clock::now().time_since_epoch().count());

std::mt19937& get_rng() {
    return rng;
}

bool calculateHit(const Character& atk, const Character& def) {
    double base = 0.75 + (atk.lck - def.lck) * 0.005;
    std::uniform_real_distribution<> d(0.0, 1.0);
    double roll = d(get_rng()), chance = std::min(0.95, std::max(0.1, base));
    return roll < chance;
}

int calculateDamage(const Character& atk, const Character& def) {
    return std::max(1, atk.atk - def.def);
}