#include "InventoryComponent.h"

ItemComponent& InventoryComponent::getItem(unsigned int index) {
    return items_[index];
}
const ItemComponent& InventoryComponent::getItem(unsigned int index) const {
    return items_[index];
}

void InventoryComponent::addItem(const std::string& prefabId, unsigned int count, ItemStats stats) {
    for (auto& item : items_) {
        if (item.getPrefabId() == prefabId) {
            item.addCount(count);
            return;
        }
    }
    if (items_.size() < max_inventory_size) {
        items_.push_back(ItemComponent(prefabId, count, stats));
    }
}

void InventoryComponent::removeItem(unsigned int index, unsigned int count) {
    auto& item = items_[index];
    if (item.getCount() > count) {
        item.addCount(-count);
    }
    else {
        items_.erase(items_.begin() + index);
        if (selected_item_number >= items_.size()) selected_item_number = items_.size() - 1;
    }
}

void InventoryComponent::incSelectedItemNumber() {
    selected_item_number++;
}

void InventoryComponent::decSelectedItemNumber() {
    selected_item_number--;
}

std::vector<ItemComponent> InventoryComponent::getInventory() {
    return items_;
}

unsigned int InventoryComponent::getCurrentSize() {
    return items_.size();
}

unsigned int InventoryComponent::getMaxSize() {
    return max_inventory_size;
}

unsigned int InventoryComponent::getSelectedItemNumber() {
    return selected_item_number;
}

std::vector<ItemComponent> InventoryComponent::getInventory() const {
    return items_;
}

unsigned int InventoryComponent::getCurrentSize() const {
    return items_.size();
}

unsigned int InventoryComponent::getMaxSize() const {
    return max_inventory_size;
}

unsigned int InventoryComponent::getSelectedItemNumber() const {
    return selected_item_number;
}

void InventoryComponent::setSelectedItemNumber(unsigned int number) {
    if (number < max_inventory_size) {
        selected_item_number = number;
    }
}
