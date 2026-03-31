#include "ColorComponent.h"

ColorComponent::ColorComponent(): color_("white") {}

ColorComponent::ColorComponent(std::string color): color_(color) {}

void ColorComponent::setColor(std::string color) {
    color_ = color;
}

std::string ColorComponent::getColor() {
    return color_;
}

std::string ColorComponent::getColor() const {
    return color_;
}
