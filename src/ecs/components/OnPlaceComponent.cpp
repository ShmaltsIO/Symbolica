#include "OnPlaceComponent.h"

OnPlaceComponent::OnPlaceComponent(): i_am_on_place_(false) {}

OnPlaceComponent::OnPlaceComponent(bool status): i_am_on_place_(status) {}

void OnPlaceComponent::enable() {
    i_am_on_place_ = true;
}

void OnPlaceComponent::disable() {
    i_am_on_place_ = false;
}

bool OnPlaceComponent::getStatus() {
    return i_am_on_place_;
}

bool OnPlaceComponent::getStatus() const {
    return i_am_on_place_;
}
