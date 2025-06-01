#include "hero.h"
#include "enemy.h"
#include "dungeon.h"
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;
static mt19937 rng((unsigned)chrono::system_clock::now().time_since_epoch().count());

int main() {
    vector<Hero> pool = {
        Hero("Guerrero",200,30,20,15,10), Hero("Mago",150,40,10,20,15),
        Hero("Paladin",220,25,25,10,8), Hero("Ladron",180,28,15,25,20),
        Hero("Arquero",170,32,12,22,12), Hero("Clerigo",160,20,18,18,14)
    };

    cout << "Quieres elegir tus heroes? (s/n): ";
    char opcion; cin >> opcion;
    vector<Hero> heroes;
    if(opcion == 's' || opcion == 'S') {
        cout << "Elige 3 heroes por numero:\n";
        for(int i=0; i<pool.size(); ++i)
            cout << i+1 << ". " << pool[i].name << "\n";
        int sel;
        while(heroes.size() < 3) {
            cout << "Selecciona heroe " << heroes.size()+1 << ": ";
            cin >> sel;
            if(sel < 1 || sel > pool.size()) continue;
            if(find_if(heroes.begin(), heroes.end(), [&](const Hero& h){ return h.name == pool[sel-1].name; }) == heroes.end())
                heroes.push_back(pool[sel-1]);
            else cout << "Ya seleccionado.\n";
        }
    } else {
        shuffle(pool.begin(), pool.end(), rng);
        heroes.assign(pool.begin(), pool.begin()+3);
    }

    vector<Enemy> bosses;
    bosses.emplace_back("Mini_Jefe",250,35,20,12,10,"Mini Jefe");
    bosses.emplace_back("Gran_Jefe",500,50,30,8,12,"Gran Jefe");

    cout << "Ingresa tu alias: "; string alias; cin >> alias;
    Dungeon game(heroes, bosses); // Corrected Dungeon instantiation
    game.run(alias);             // Corrected function call
    return 0;
}