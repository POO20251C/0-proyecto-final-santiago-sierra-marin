#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <string>
#include <vector>

struct ScoreRecord { std::string alias, datetime; int max_room, hp_lost; };

class ScoreManager {
public:
    static const std::string FILE;
    static std::vector<ScoreRecord> load();
    static void save(const ScoreRecord& r);
    static void displayTop();
};

#endif // SCOREMANAGER_H