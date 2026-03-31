#ifndef INVENTORY_COMPONENT_H
#define INVENTORY_COMPONENT_H

#include "ItemComponent.h"
#include <vector>

class InventoryComponent: public IComponent {
private:
    std::vector<ItemComponent> items_;
    unsigned int current_inventory_size = 0;
    unsigned int max_inventory_size = 10;
    unsigned int selected_item_number = 0;

public:
    InventoryComponent();
    InventoryComponent(std::vector<ItemComponent>, unsigned int, unsigned int);

    void addItem(ItemComponent);
    void deleteItem(unsigned int);
    void setSelectedItemNumber(unsigned int);
    void incSelectedItemNumber();
    void decSelectedItemNumber();
    
    ItemComponent getItem();
    ItemComponent getItem() const;

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