#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include "IComponent.h"

/**
 * @brief Class, which do entity a mortal.
 * @param health_ is current health of entity.
 * @param health_limit_ is max health of entity.
 * 
 * Both is int fields.
 */
class HealthComponent: public IComponent {
private:
    int health_;
    int health_limit_;
public:
    HealthComponent();
    HealthComponent(int, int);

    void setHealth(int);
    int getHealth();
    int getHealth() const;

    void setHealthLimit(int);
    int getHealthLimit();
    int getHealthLimit() const;
};

#endif // HEALTH_COMPONENT_H