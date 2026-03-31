#ifndef COLLECTOR_COMPONENT_H
#define COLLECTOR_COMPONENT_H

#include "IComponent.h"
#include <map>

class Entity;

class CollectorComponent: public IComponent {
private:
    std::map<size_t, Entity*> collider_;
    
public:


};

#endif // COLLECTOR_COMPONENT_H