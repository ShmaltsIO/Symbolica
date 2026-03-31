#include "DamageComponent.h"

DamageComponent::DamageComponent(): damage_(1), bonus_damage_(0) {}

DamageComponent::DamageComponent(int damage): damage_(damage), bonus_damage_(0) {}

DamageComponent::DamageComponent(int damage, int bonus_damage): damage_(damage), bonus_damage_(bonus_damage) {}

void DamageComponent::setDamage(int damage) {
    damage_ = damage;
}

void DamageComponent::setBonusDamage(int bonus_damage) {
    bonus_damage_ = bonus_damage;
}

int DamageComponent::getDamage() {
    return damage_;
}

int DamageComponent::getBonusDamage() {
    return bonus_damage_;
}

int DamageComponent::getTotalDamage() {
    return damage_ + bonus_damage_;
}

int DamageComponent::getDamage() const {
    return damage_;
}

int DamageComponent::getBonusDamage() const {
    return bonus_damage_;
}

int DamageComponent::getTotalDamage() const {
    return damage_ + bonus_damage_;
}
