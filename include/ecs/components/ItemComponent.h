#ifndef ITEM_COMPONENT_H
#define ITEM_COMPONENT_H

#include <string>

#include "IComponent.h"
#include "ItemStats.h"

class ItemComponent: public IComponent {
private:
    std::string prefabId_ = "";
    unsigned int count_ = 0;
    ItemStats stats_;

public:
    ItemComponent() = default;
    ItemComponent(const std::string& id, unsigned int count, const ItemStats& stats): prefabId_(id), count_(count), stats_(stats) {}

    std::string getPrefabId() const;
    unsigned int getCount() const;
    void setCount(unsigned int);
    void addCount(unsigned int);
    const ItemStats& getStats() const;
    void setStats(const ItemStats&);
};

#endif // ITEM_COMPONENT_H