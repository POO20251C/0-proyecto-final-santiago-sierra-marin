#include "dungeon.h"
#include "combat.h"
#include "enumsh.h"
#include "hero.h"
#include "enemy.h"
#include "item.h"
#include "scoremanager.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

Dungeon::Dungeon(vector<Hero>& h, vector<Enemy>& b)
    : heroes(h), bosses(b), room(1), hp_lost(0) {
    vector<string> attrs = {"atk", "def", "lck", "spd", "hp"};
    for (int i = 0; i < 50; ++i) {
        int a = uniform_int_distribution<>(0, 4)(get_rng()), c;
        do {
            c = uniform_int_distribution<>(0, 4)(get_rng());
        } while (c == a);
        int ba = uniform_int_distribution<>(1, 5)(get_rng());
        int bc = uniform_int_distribution<>(1, 5)(get_rng());
        int ia = 0, id = 0, il = 0, is = 0, ih = 0;
        if (attrs[a] == "atk") ia = ba;
        if (attrs[a] == "def") id = ba;
        if (attrs[a] == "lck") il = ba;
        if (attrs[a] == "spd") is = ba;
        if (attrs[a] == "hp") ih = ba;
        if (attrs[c] == "atk") ia += bc;
        if (attrs[c] == "def") id += bc;
        if (attrs[c] == "lck") il += bc;
        if (attrs[c] == "spd") is += bc;
        if (attrs[c] == "hp") ih = ba;
        itemPool.emplace_back("Item_" + to_string(i + 1), ia, id, il, is, ih);
    }
}

void Dungeon::run(const string& alias) {
    ScoreManager::displayTop();
    while (room <= 10 && count_if(heroes.begin(), heroes.end(), [](const Hero& h){ return h.isAlive(); }) > 1) {
        cout << "\n-- Sala " << room << " --\n";
        handleEvents();
        Enemy current_enemy = spawnEnemy();
        cout << "Aparece " << current_enemy.name << " (" << current_enemy.category << ")\n";
        battle(current_enemy);
        bool boss_defeated = false;
        for (const auto& boss : bosses) {
            if (!boss.isAlive() && boss.category == "Gran Jefe") {
                boss_defeated = true;
                break;
            }
        }
        if (boss_defeated) break;
        if (count_if(heroes.begin(), heroes.end(), [](const Hero& h){ return h.isAlive(); }) <= 1) break;

        for (auto& h : heroes)
            if (h.isAlive()) {
                h.atk = int(h.atk * 1.02);
                h.def = int(h.def * 1.02);
            }
        ++room;
    }

    int max_reached_room = room;
    bool all_alive = any_of(heroes.begin(), heroes.end(), [](const Hero& h){ return h.isAlive(); });
    bool boss_defeated = false;
    for (const auto& boss : bosses) {
        if (!boss.isAlive() && boss.category == "Gran Jefe") {
            boss_defeated = true;
            break;
        }
    }

    if (!all_alive && !boss_defeated) {
        max_reached_room--;
    }

    ScoreRecord r{alias, currentDateTime(), max_reached_room, hp_lost};
    ScoreManager::save(r);
    cout << "-- Fin del juego --\n";
    if (boss_defeated) {
        cout << "-- ¡Has derrotado al Gran Jefe! ¡Victoria! --\n";
    } else if (count_if(heroes.begin(), heroes.end(), [](const Hero& h){ return h.isAlive(); }) <= 1) {
        cout << "-- Dos heroes han caido. El viaje termina aqui. --\n";
    }
}

Enemy Dungeon::spawnEnemy() {
    if (room == 8)
        for (auto& e : bosses)
            if (e.category == "Mini Jefe") return e;
    if (room == 10)
        for (auto& e : bosses)
            if (e.category == "Gran Jefe") return e;
    int base_hp = 100 + (room - 1) * 20;
    int base_atk = 20 + (room - 1) * 2;
    int base_def = 10 + (room - 1) * 1;
    int base_spd = 10 + (room - 1) * 1;
    int base_lck = 5;
    uniform_int_distribution<> idist(1, 99999);
    string name = "Soldado_" + to_string(room) + "_" + to_string(idist(get_rng()));
    return Enemy(name, base_hp, base_atk, base_def, base_spd, base_lck, "Soldado");
}

void Dungeon::handleEvents() {
    if (room == 1) {
        cout << "Mercado inicial: arma y armadura comunes disponibles.\n";
        int idx = uniform_int_distribution<>(0, itemPool.size() - 1)(get_rng());
        Item it = itemPool[idx];
        cout << "Sala 1: se obtiene " << it.description() << "\n";
        cout << "Elige heroe para equipar el item (1-" << heroes.size() << "):\n";
        for (int i = 0; i < heroes.size(); ++i)
            cout << i + 1 << ". " << heroes[i].name << "\n";
        int sel;
        cin >> sel;
        heroes[sel - 1].equip(it);
    }
    if (room == 3) {
        cout << "Cofre: 1) +2 LCK o 2) 3 pociones. Elige opcion: ";
        int op;
        cin >> op;
        if (op == 1) {
            Item acc("Amuleto_Suerte", 0, 0, 2, 0, 0);
            cout << "Elige heroe (1-" << heroes.size() << "): ";
            int h;
            cin >> h;
            heroes[h - 1].equip(acc);
        } else {
            cout << "3 pociones a todos.\n";
            for (auto& h : heroes) h.potions += 3;
        }
    }
    if (room == 6) {
        cout << "Sala 6: items aleatorios para cada heroe vivo:\n";
        for (int i = 0; i < heroes.size(); ++i)
            if (heroes[i].isAlive()) {
                int idx = uniform_int_distribution<>(0, itemPool.size() - 1)(get_rng());
                Item it = itemPool[idx];
                heroes[i].equip(it);
                cout << heroes[i].name << " recibe " << it.description() << "\n";
            }
    }
    if (room == 8) {
        cout << "Santo Grial: Se restaura salud total al completo.\n";
        for (auto& h : heroes)
            if (h.isAlive()) h.hp = h.max_hp;
    }
}

void Dungeon::battle(Enemy enemy) {
    while (enemy.isAlive() && count_if(heroes.begin(), heroes.end(), [](const Hero& h){ return h.isAlive(); }) > 1) {
        vector<Character*> participants;
        for (auto& h : heroes)
            if (h.isAlive()) participants.push_back(&h);
        participants.push_back(&enemy);
        sort(participants.begin(), participants.end(), [](Character* a, Character* b) {
            return a->spd > b->spd;
        });
        for (auto* p : participants) {
            if (!enemy.isAlive() || count_if(heroes.begin(), heroes.end(), [](const Hero& h){ return h.isAlive(); }) <= 1)
                break;
            if (Hero* h = dynamic_cast<Hero*>(p)) {
                if (!h->isAlive()) continue;
                cout << "\nTurno de " << h->name << " HP:" << h->hp << "\n";
                cout << "1) Atacar  2) Curar (" << h->potions << " pociones)\n";
                int act;
                cin >> act;
                if (act == HEAL && h->potions > 0) {
                    h->heal();
                    cout << h->name << " se cura. HP=" << h->hp << "\n";
                } else {
                    if (calculateHit(*h, enemy)) {
                        int dmg = calculateDamage(*h, enemy);
                        enemy.hp -= dmg;
                        cout << h->name << " golpea a " << enemy.name << " por " << dmg << "\n";
                        if (!enemy.isAlive()) cout << enemy.name << " derrotado.\n";
                    } else
                        cout << h->name << " falla el golpe.\n";
                }
            } else {
                vector<Hero*> alive;
                for (auto& hh : heroes)
                    if (hh.isAlive()) alive.push_back(&hh);
                if (!alive.empty()) {
                    Hero* target = alive[uniform_int_distribution<>(0, alive.size() - 1)(get_rng())];
                    cout << enemy.name << " ataca a " << target->name << "\n";
                    if (calculateHit(enemy, *target)) {
                        int dmg = calculateDamage(enemy, *target);
                        target->hp -= dmg;
                        cout << enemy.name << " inflige " << dmg << " a " << target->name << "\n";
                        if (!target->isAlive()) {
                            cout << target->name << " ha caido.\n";
                            hp_lost += target->max_hp;
                        }
                    } else
                        cout << enemy.name << " falla el ataque.\n";
                }
            }
        }
    }
    // Si el enemigo sigue vivo al final de la batalla, pero solo queda un héroe, la batalla termina.
}

string Dungeon::currentDateTime() {
    auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d_%H:%M:%S", localtime(&now));
    return buf;
}