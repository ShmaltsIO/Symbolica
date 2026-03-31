#include "StepComponent.h"

StepComponent::StepComponent(): steps_(0) {}

StepComponent::StepComponent(unsigned int steps):
 steps_(steps) {}

void StepComponent::setSteps(unsigned int steps) {
    steps_ = steps;
}

unsigned int StepComponent::getSteps() {
    return steps_;
}

unsigned int StepComponent::getSteps() const {
    return steps_;
}
