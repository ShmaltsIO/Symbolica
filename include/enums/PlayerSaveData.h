#ifndef PLAYER_SAVE_DATA_H
#define PLAYER_SAVE_DATA_H

#include <vector>
#include <string>

#include "Vector2D.h"
#include "LevelState.h"
#include "ItemData.h"

class PlayerSaveData {
public:
    int health = 20;
    int maxHealth = 20;
    int damage = 2;
    int protection = 1;
    int level = 1;
    int experience = 0;
    int cash = 0;
    Vector2D position{0, 0};
    int currentLevelId;

    std::vector<ItemData> inventory;
    //std::map<int, LevelState> levelsState; // состояние для каждого уровня (т.е. пройденного)
};

#endif // PLAYER_SAVE_DATA_H
