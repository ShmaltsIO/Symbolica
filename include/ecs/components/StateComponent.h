#ifndef STATE_COMPONENT_H
#define STATE_COMPONENT_H

#include "IComponent.h"
#include "GameStateTypesEnum.h"

class StateComponent: public IComponent {
private:
    GameStateTypesEnum state_;

public:
    StateComponent();
    StateComponent(GameStateTypesEnum);

    void setState(GameStateTypesEnum);
    GameStateTypesEnum getState();
    GameStateTypesEnum getState() const;

};

#endif // STATE_COMPONENT_H