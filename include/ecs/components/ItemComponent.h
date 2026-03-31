#ifndef ITEM_COMPONENT_H
#define ITEM_COMPONENT_H

#include "IComponent.h"
#include <string>

class ItemComponent: public IComponent {
private:
    size_t item_id_ = 0;
    std::string name_ = " ";
    std::string description_ = " ";

public:
    ItemComponent();
    ItemComponent(size_t, std::string, std::string);

    size_t getItemId();
    std::string getName();
    std::string getDescription();

    size_t getItemId() const;
    std::string getName() const;
    std::string getDescription() const;
};

#endif // ITEM_COMPONENT_H