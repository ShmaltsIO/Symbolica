#ifndef EQUIPMENT_COMPONENT_H
#define EQUIPMENT_COMPONENT_H

#include "IComponent.h"
#include <map>
#include <string>

/**
 * @brief This component contain places for items on some entity.
 * @param equipment_ is map from string to size_t;
 * 
 * @warning Very important, if entity wears nothing, then value is 0;
 */
class EquipmentComponent: public IComponent {
private:
    std::map<std::string, size_t> equipment_{};

public:
    EquipmentComponent();
    EquipmentComponent(std::map<std::string, size_t>);

    void setChest(size_t);
    void setRightHand(size_t);

    std::map<std::string, size_t> getEquipment();
    size_t getChest();
    size_t getRightHand();

    size_t getChest() const;
    size_t getRightHand() const;
    std::map<std::string, size_t> getEquipment() const;

};

#endif // EQUIPMENT_COMPONENT_H