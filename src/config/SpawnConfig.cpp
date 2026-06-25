#include "SpawnConfig.h"

inline void from_json(const nlohmann::json& j, EnemyTypeConfig& cfg) {
    j.at("id").get_to(cfg.id);
    j.at("min_depth").get_to(cfg.min_depth);
}

inline void from_json(const nlohmann::json& j, EnemySpawnConfig& cfg) {
    j.at("base_count").get_to(cfg.base_count);
    j.at("base_health").get_to(cfg.base_count);
    j.at("base_damage").get_to(cfg.base_count);
    j.at("max_per_room").get_to(cfg.max_per_room);
    j.at("weights").at("distance_factor").get_to(cfg.weights.distance_factor);
    j.at("weights").at("random_factor").get_to(cfg.weights.random_factor);
    j.at("types").get_to(cfg.types);
}

inline void from_json(const nlohmann::json& j, ItemTypeConfig& cfg) {
    j.at("id").get_to(cfg.id);
    j.at("weight").get_to(cfg.weight);
    j.at("min_depth").get_to(cfg.min_depth);
}

inline void from_json(const nlohmann::json& j, ItemSpawnConfig& cfg) {
    j.at("base_count").get_to(cfg.base_count);
    j.at("per_depth").get_to(cfg.per_depth);
    j.at("types").get_to(cfg.types);
}

inline void from_json(const nlohmann::json& j, RoomTypeConfig& cfg) {
    j.at("id").get_to(cfg.id);
    j.at("weight").get_to(cfg.weight);
    j.at("enemy_species").get_to(cfg.enemy_species);
}

inline void from_json(const nlohmann::json& j, RoomSpawnConfig& cfg) {
    j.at("rooms").get_to(cfg.roomTypes);
}

inline void from_json(const nlohmann::json& j, ArmorClassConfig& cfg) {
    j.at("id").get_to(cfg.id);
    j.at("class").get_to(cfg.armor_class);
    j.at("titles").get_to(cfg.titles);
}

inline void from_json(const nlohmann::json& j, WeaponClassConfig& cfg) {
    j.at("id").get_to(cfg.id);
    j.at("class").get_to(cfg.weapon_class);
    j.at("titles").get_to(cfg.titles);
}

inline void from_json(const nlohmann::json& j, BossTypeConfig& cfg) {
    j.at("id").get_to(cfg.id);
    j.at("min_depth").get_to(cfg.min_depth);
}

inline void from_json(const nlohmann::json& j, BossSpawnConfig& cfg) {
    j.at("first_appear").get_to(cfg.first_appear);
    j.at("every").get_to(cfg.every);
    j.at("types").get_to(cfg.types);
}

inline void from_json(const nlohmann::json& j, ChestSpawnConfig& cfg) {
    j.at("base_count").get_to(cfg.base_count);
    j.at("every").get_to(cfg.every);
    j.at("loot").get_to(cfg.loot);
}

inline void from_json(const nlohmann::json& j, SpawnConfig& cfg) {
    auto spawn = j.at("spawn");
    from_json(spawn, cfg.enemies);
    from_json(spawn, cfg.items);
    from_json(spawn, cfg.rooms);
    cfg.armor_classes = spawn.at("armor_classes").get<std::vector<ArmorClassConfig>>();
    cfg.weapon_classes = spawn.at("weapon_classes").get<std::vector<WeaponClassConfig>>();
    from_json(spawn, cfg.bosses);
    from_json(spawn, cfg.chests);
}

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