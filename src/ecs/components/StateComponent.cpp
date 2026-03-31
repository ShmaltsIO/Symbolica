#include "StateComponent.h"

StateComponent::StateComponent(): state_(GameStateTypesEnum::STAY) {}

StateComponent::StateComponent(GameStateTypesEnum state): state_(state) {}

void StateComponent::setState(GameStateTypesEnum state) {
    state_ = state;
}

GameStateTypesEnum StateComponent::getState() {
    return state_;
}

GameStateTypesEnum StateComponent::getState() const {
    return state_;
}
