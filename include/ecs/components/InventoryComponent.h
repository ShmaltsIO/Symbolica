#ifndef INVENTORY_COMPONENT_H
#define INVENTORY_COMPONENT_H

#include <vector>

#include "ItemComponent.h"
#include "ItemStats.h"

class InventoryComponent: public IComponent {
private:
    std::vector<ItemComponent> items_;
    unsigned int max_inventory_size = 10;
    unsigned int selected_item_number = 0;

public:
    InventoryComponent() = default;
    InventoryComponent(std::vector<ItemComponent> items, unsigned int max_size, unsigned int current_index): items_(items), max_inventory_size(max_size), selected_item_number(current_index) {}

    void addItem(const std::string& prefabId, unsigned int count, ItemStats stats);
    void removeItem(unsigned int index, unsigned int count);
    void setSelectedItemNumber(unsigned int);
    void incSelectedItemNumber();
    void decSelectedItemNumber();
    
    ItemComponent& getItem(unsigned int index);
    const ItemComponent& getItem(unsigned int index) const;

    std::vector<ItemComponent> getInventory();
    unsigned int getCurrentSize();
    unsigned int getMaxSize();
    unsigned int getSelectedItemNumber();

    std::vector<ItemComponent> getInventory() const;
    unsigned int getCurrentSize() const;
    unsigned int getMaxSize() const;
    unsigned int getSelectedItemNumber() const;
};

#endif // INVENTORY_COMPONENT_H