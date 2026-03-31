#include "LevelComponent.h"

LevelComponent::LevelComponent(): level_(1) {}

LevelComponent::LevelComponent(unsigned int level): level_(level) {}

void LevelComponent::setLevel(unsigned int level) {
    level_ = level;
}

unsigned int LevelComponent::getLevel() {
    return level_;
}

unsigned int LevelComponent::getLevel() const {
    return level_;
}
