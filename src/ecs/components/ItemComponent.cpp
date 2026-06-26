#include "ItemComponent.h"

std::string ItemComponent::getPrefabId() const {
	return prefabId_;
}

unsigned int ItemComponent::getCount() const {
	return count_;
}

void ItemComponent::setCount(unsigned int count) {
	count_ = count;
}

void ItemComponent::addCount(unsigned int delta) {
	count_ += delta;
}
