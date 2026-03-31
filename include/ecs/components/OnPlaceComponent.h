#ifndef ON_PLACE_COMPONENT_H
#define ON_PLACE_COMPONENT_H

#include "IComponent.h"

/**
 * @brief Special component for entities.
 * 
 * That's component means, what some entity can be place on other, and if this 
 * door or item, player can't go to door or pick the item.
 * 
 * @param i_am_on_palce_ is bool private field.
 */
class OnPlaceComponent: public IComponent {
private:
    bool i_am_on_place_ = false;

public:
    OnPlaceComponent();
    OnPlaceComponent(bool);

    void enable();
    void disable();

    bool getStatus();
    bool getStatus() const;

};

#endif // ON_PLACE_COMPONENT_H