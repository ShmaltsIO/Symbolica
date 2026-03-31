#ifndef DAMAGE_COMPONENT_H
#define DAMAGE_COMPONENT_H

#include "IComponent.h"
/**
 * @brief Give entity a battle ability.
 * @param damage_ is entity damage (int).
 */
class DamageComponent: public IComponent {
private:
    int damage_;
    int bonus_damage_;

public:
    DamageComponent();
    DamageComponent(int);
    DamageComponent(int, int);

    void setDamage(int);
    void setBonusDamage(int);
    
    int getDamage();
    int getBonusDamage();
    int getTotalDamage();

    int getDamage() const;
    int getBonusDamage() const;
    int getTotalDamage() const;
};

#endif // DAMAGE_COMPONENT_H