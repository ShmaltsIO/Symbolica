#ifndef PLAYER_SAVE_DATA_H
#define PLAYER_SAVE_DATA_H

#include <vector>
#include <map>
#include <string>

#include "Vector2D.h"

class PlayerSaveData {
public:
    int health = 20;
    int maxHealth = 20;
    int damage = 2;
    int protection = 1;
    int level = 1;
    int experience = 0;
    int worth = 0;
    Vector2D position{0, 0};
    int currentLevelId;

    // std::vector<ItemData> inventory;
    // std::map<std::string, LevelState> levelsState; // состояние для каждого уровня (т.е. пройденного)
};

#endif // PLAYER_SAVE_DATA_H
