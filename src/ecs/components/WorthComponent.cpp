#include "WorthComponent.h"

WorthComponent::WorthComponent(): worth_(0) {}

WorthComponent::WorthComponent(unsigned int worth): worth_(worth) {}


void WorthComponent::setWorth(unsigned int worth) {
    worth_ = worth;
}

unsigned int WorthComponent::getWorth() {
    return worth_;
}

unsigned int WorthComponent::getWorth() const {
    return worth_;
}
