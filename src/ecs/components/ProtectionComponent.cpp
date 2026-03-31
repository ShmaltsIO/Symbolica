#include "ProtectionComponent.h"

ProtectionComponent::ProtectionComponent(): protection_(0) {}

ProtectionComponent::ProtectionComponent(unsigned int protection): protection_(protection) {}

void ProtectionComponent::setProtection(unsigned int protection) {
    protection_ = protection;
}

unsigned int ProtectionComponent::getProtection() {
    return protection_;
}

unsigned int ProtectionComponent::getProtection() const {
    return protection_;
}
