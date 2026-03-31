#include "HealthComponent.h"

HealthComponent::HealthComponent(): health_(20), health_limit_(20) {}

HealthComponent::HealthComponent(int health, int health_limit): health_(health), health_limit_(health_limit) {}

int HealthComponent::getHealth() {
    return health_;
}

int HealthComponent::getHealth() const {
    return health_;
}

void HealthComponent::setHealth(int health) {
    health_ = health;
}

int HealthComponent::getHealthLimit() {
    return health_limit_;
}

int HealthComponent::getHealthLimit() const {
    return health_limit_;
}

void HealthComponent::setHealthLimit(int health_limit) {
    health_limit_ = health_limit;
}

