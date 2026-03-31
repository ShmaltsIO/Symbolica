#include "InventoryComponent.h"

InventoryComponent::InventoryComponent(): items_(), current_inventory_size(0), max_inventory_size(10), selected_item_number(0) {}

InventoryComponent::InventoryComponent(std::vector<ItemComponent> items, unsigned int current_size, unsigned int max_size):
 items_(items), current_inventory_size(current_size), max_inventory_size(max_size), selected_item_number(0) {}

void InventoryComponent::addItem(ItemComponent item) {
    items_.emplace_back(item);
    current_inventory_size++;
    selected_item_number++;
}

void InventoryComponent::deleteItem(unsigned int number) {
    items_.erase(items_.cbegin() + number);
    current_inventory_size--;
    selected_item_number--;
}

void InventoryComponent::incSelectedItemNumber() {
    selected_item_number++;
}

void InventoryComponent::decSelectedItemNumber() {
    selected_item_number--;
}

ItemComponent InventoryComponent::getItem() {
    if (selected_item_number == 0 || current_inventory_size == 0) {
        return ItemComponent();
    } else {
        return items_[selected_item_number-1];
    }
}

ItemComponent InventoryComponent::getItem() const {
    return items_[selected_item_number-1];
}

std::vector<ItemComponent> InventoryComponent::getInventory() {
    return items_;
}

unsigned int InventoryComponent::getCurrentSize() {
    return current_inventory_size;
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
    return current_inventory_size;
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
