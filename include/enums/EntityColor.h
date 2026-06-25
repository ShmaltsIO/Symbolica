#ifndef ENTITY_COLOR_H
#define ENTITY_COLOR_H

#include <unordered_map>
#include <string>

#include "EntityType.h"

class EntityColor {
public:
    inline static std::unordered_map<EntityType, std::string> entity_base_colors = {
    {EntityType::PLAYER, "white"},
    {EntityType::ENEMY, "red"},
    {EntityType::COIN, "dark yellow"},
    {EntityType::FOOD, "amber"},
    {EntityType::BOSS, "dark red"}
    };
};

#endif // ENTITY_COLOR_H
