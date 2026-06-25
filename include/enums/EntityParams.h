#ifndef ENTITY_PARAMS_H
#define ENTITY_PARAMS_H

#include <string>

#include "Vector2D.h"
#include "EntityType.h"

class EntityParams {
public:
    int health = 0;
    int damage = 0;
    int protection = 0;
    int experienceReward = 0;
    int worth = 0;
    Vector2D position;
    std::string name = "";
    std::string title = "";
    EntityType entity_type = EntityType::COIN;
    int level = 0;
};

#endif // ENTITY_PARAMS_H
