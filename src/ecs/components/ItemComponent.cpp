#include "ItemComponent.h"

ItemComponent::ItemComponent(): item_id_(0), name_("Void"), description_("Empty") {}

ItemComponent::ItemComponent(size_t item_id, std::string name, std::string description):
 item_id_(item_id), name_(name), description_(description) {}

std::string ItemComponent::getName() {
    return name_;
}

std::string ItemComponent::getDescription() {
    return description_;
}

size_t ItemComponent::getItemId() {
    return item_id_;
}

std::string ItemComponent::getName() const {
    return name_;
}

std::string ItemComponent::getDescription() const {
    return description_;
}

size_t ItemComponent::getItemId() const {
    return item_id_;
}
