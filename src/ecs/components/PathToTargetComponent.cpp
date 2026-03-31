#include "PathToTargetComponent.h"

PathToTargetComponent::PathToTargetComponent(): path_to_target_{} {}

void PathToTargetComponent::setPathToTarget(std::vector<Vector2D> path_to_target) {
    path_to_target_ = path_to_target;
}

std::vector<Vector2D> PathToTargetComponent::getPathToTarget() {
    return path_to_target_;
}

std::vector<Vector2D> PathToTargetComponent::getPathToTarget() const {
    return path_to_target_;
}
