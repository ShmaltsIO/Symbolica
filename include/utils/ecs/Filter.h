#ifndef FILTER_H
#define FILTER_H

#include "IComponent.h"
#include "Entity.h"

class Filter {
public:
//template<typename... IComponent> static bool apply(const Entity&, const IComponent&...);
static bool isPlayer(const Entity*);
//static bool isObstacle(const Entity*);

};

#endif // FILTER_H