#ifndef LEVEL_STATE_H
#define LEVEL_STATE_H

#include <vector>

#include "Vector2D.h"

class LevelState {
public:
    std::vector<Vector2D> killedEnemies;      // позиции, где были убиты враги
    std::vector<Vector2D> collectedItems;     // позиции, где были подобраны предметы
    std::vector<Vector2D> openedDoors;        // позиции открытых дверей
};

#endif // LEVEL_STATE_H
