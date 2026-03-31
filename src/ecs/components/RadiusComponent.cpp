#include "RadiusComponent.h"

RadiusComponent::RadiusComponent(): neighborhood_{} {}

void RadiusComponent::setNeighborhood(std::vector<size_t> neighborhood) {
    neighborhood_.clear();
    neighborhood_ = neighborhood;
}

std::vector<size_t> RadiusComponent::getNeighborhood() {
    return neighborhood_;
}

std::vector<size_t> RadiusComponent::getNeighborhood() const {
    return neighborhood_;
}
