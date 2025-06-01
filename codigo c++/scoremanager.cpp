#include "scoremanager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

const std::string ScoreManager::FILE="scores.txt";
std::vector<ScoreRecord> ScoreManager::load() {
    std::vector<ScoreRecord> v; std::ifstream in(FILE); std::string line;
    while(getline(in,line)){
        std::stringstream ss(line); ScoreRecord r; ss>>r.alias>>r.datetime>>r.max_room>>r.hp_lost; v.push_back(r);
    }
    return v;
}
void ScoreManager::save(const ScoreRecord& r){ auto v=load(); v.push_back(r);
    std::sort(v.begin(), v.end(),[](auto&a,auto&b){ if(a.max_room!=b.max_room) return a.max_room>b.max_room; return a.hp_lost<b.hp_lost; });
    if(v.size()>5) v.resize(5);
    std::ofstream out(FILE);
    for(auto&x:v) out<<x.alias<<' '<<x.datetime<<' '<<x.max_room<<' '<<x.hp_lost<<"\n";
}
void ScoreManager::displayTop(){ auto v=load(); std::cout<<"Top 5 Scores:\n"; int i=1;
    for(auto&rec:v) std::cout<<i++<<". "<<rec.alias<<" - Sala:"<<rec.max_room<<" - HP perdido:"<<rec.hp_lost<<" - Fecha:"<<rec.datetime<<"\n";
}