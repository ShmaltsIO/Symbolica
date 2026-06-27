#include "SpawnConfig.h"

const std::vector<const EnemyTypeConfig*>& SpawnConfig::getEnemies(int depth) const {
    auto it = enemiesCache_.find(depth);
    if (it != enemiesCache_.end()) {
        return it->second;
    }
    std::vector<const EnemyTypeConfig*> filtered;
    for (const auto& t : enemies.types) {
        if (t.min_depth <= depth) {
            filtered.push_back(&t);
        }
    }
    enemiesCache_[depth] = std::move(filtered);
    return enemiesCache_[depth];
}

const std::vector<const ItemTypeConfig*>& SpawnConfig::getItems(int depth) const {
    auto it = itemsCache_.find(depth);
    if (it != itemsCache_.end()) {
        return it->second;
    }
    std::vector<const ItemTypeConfig*> filtered;
    for (const auto& t : items.types) {
        if (t.min_depth <= depth) {
            filtered.push_back(&t);
        }
    }
    itemsCache_[depth] = std::move(filtered);
    return itemsCache_[depth];
}

const std::vector<const BossTypeConfig*>& SpawnConfig::getBosses(int depth) const {
    auto it = bossesCache_.find(depth);
    if (it != bossesCache_.end()) {
        return it->second;
    }
    std::vector<const BossTypeConfig*> filtered;
    for (const auto& t : bosses.types) {
        if (t.min_depth <= depth) {
            filtered.push_back(&t);
        }
    }
    bossesCache_[depth] = std::move(filtered);
    return bossesCache_[depth];
}

const std::vector<const ArmorClassConfig*>& SpawnConfig::getArmorClasses() const {
    if (!armorClassesCache_.empty() || armor_classes.empty()) {
        return armorClassesCache_;
    }
    for (const auto& a : armor_classes) {
        armorClassesCache_.push_back(&a);
    }
    return armorClassesCache_;
}

const std::vector<const WeaponClassConfig*>& SpawnConfig::getWeaponClasses() const {
    if (!weaponClassesCache_.empty() || weapon_classes.empty()) {
        return weaponClassesCache_;
    }
    for (const auto& w : weapon_classes) {
        weaponClassesCache_.push_back(&w);
    }
    return weaponClassesCache_;
}