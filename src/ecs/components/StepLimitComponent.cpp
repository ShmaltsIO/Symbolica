#include "StepLimitComponent.h"

StepLimitComponent::StepLimitComponent(): steps_limit_(40) {}

StepLimitComponent::StepLimitComponent(unsigned int step_limit): steps_limit_(step_limit) {}

void StepLimitComponent::setStepsLimit(unsigned int steps_limit) {
    steps_limit_ = steps_limit;
}

unsigned int StepLimitComponent::getStepLimit() {
    return steps_limit_;
}

unsigned int StepLimitComponent::getStepLimit() const {
    return steps_limit_;
}
