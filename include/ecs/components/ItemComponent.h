#ifndef ITEM_COMPONENT_H
#define ITEM_COMPONENT_H

#include <string>

#include "IComponent.h"

class ItemComponent: public IComponent {
private:
    std::string prefabId_ = "";
    unsigned int count_ = 0;

public:
    ItemComponent() = default;
    ItemComponent(const std::string& id, unsigned int count = 1): prefabId_(id), count_(count) {}

    std::string getPrefabId() const;
    unsigned int getCount() const;
    void setCount(unsigned int);
    void addCount(unsigned int);
};

#endif // ITEM_COMPONENT_H