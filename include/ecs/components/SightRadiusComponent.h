#ifndef SIGHT_RADIUS_COMPONENT_H
#define SIGHT_RADIUS_COMPONENT_H

#include "IComponent.h"

class SightRadiusComponent : public IComponent {
private:
    int radius_ = 5;
public:
    SightRadiusComponent() = default;
    explicit SightRadiusComponent(int r) : radius_(r) {}

    void setRadius(int r) { radius_ = r; }
    int getRadius() const { return radius_; }
};

#endif