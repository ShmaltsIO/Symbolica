#ifndef GAME_OBJECTS_TYPE_H
#define GAME_OBJECTS_TYPE_H

enum class GameObjectsTexture : char {
    PLAYER = '@',
    ENEMY = 'E',
    COIN = 'C',
    FOOD = '%',
    CHEST = 'X',
    KEY = '+',
    NPC = 'N',
    ARMOR = 'A',
    WEAPON = 'W',
    BOSS = 'B',
    WALL = '#',
    GROUND = '.'
};

#endif // GAME_OBJECTS_TYPE_H