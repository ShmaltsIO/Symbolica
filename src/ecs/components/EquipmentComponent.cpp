#include "EquipmentComponent.h"

EquipmentComponent::EquipmentComponent() {
    equipment_ = { {"chest", 0}, {"right_hand", 0} };
}

EquipmentComponent::EquipmentComponent(std::map<std::string, size_t> equipment): equipment_(equipment) {}

void EquipmentComponent::setChest(size_t item) {
    equipment_["chest"] = item;
}

void EquipmentComponent::setRightHand(size_t item) {
    equipment_["right_hand"] = item;
}

std::map<std::string, size_t> EquipmentComponent::getEquipment() {
    return equipment_;
}

size_t EquipmentComponent::getChest() {
    return equipment_["chest"];
}

size_t EquipmentComponent::getRightHand() {
    return equipment_["right_hand"];
}

std::map<std::string, size_t> EquipmentComponent::getEquipment() const {
    return equipment_;
}

size_t EquipmentComponent::getChest() const {
    return equipment_.at("chest");
}

size_t EquipmentComponent::getRightHand() const {
    return equipment_.at("right_hand");
}
