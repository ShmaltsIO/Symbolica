#include "OpenableComponent.h"

OpenableComponent::OpenableComponent(): is_open_(false) {}

void OpenableComponent::setOpen() {
    is_open_ = !is_open_;
}

bool OpenableComponent::getStatus() {
    return is_open_;
}

bool OpenableComponent::getStatus() const {
    return is_open_;
}
