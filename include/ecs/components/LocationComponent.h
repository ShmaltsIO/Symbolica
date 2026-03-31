#ifndef LOCATION_COMPONENT_H
#define LOCATION_COMPONENT_H

#include "IComponent.h"

/**
 * @brief That's component say, where our entity locate.
 */
class LocationComponent: public IComponent {
public:
    int current_location_;

    LocationComponent();
    LocationComponent(int);
};

#endif // LOCATION_COMPONENT_H