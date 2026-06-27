#ifndef SPAWN_CONFIG_H
#define SPAWN_CONFIG_H

#include <vector>
#include <string>
#include <unordered_map>

#include "json.hpp"

struct EnemyTypeConfig {
    std::string id;
    int min_depth;
};

struct EnemySpawnConfig {
    int base_count;
    int base_health;
    int base_damage;
    int max_per_room;
    struct {
        float distance_factor;
        float random_factor;
    } weights;
    std::vector<EnemyTypeConfig> types;
};

struct ItemTypeConfig {
    std::string id;
    int weight;
    int min_depth;
};

struct ItemSpawnConfig {
    int base_count;
    int per_depth;
    std::vector<ItemTypeConfig> types;
};

struct ArmorClassConfig {
    std::string id;
    int armor_class;
    std::vector<std::string> titles;
};

struct WeaponClassConfig {
    std::string id;
    int weapon_class;
    std::vector<std::string> titles;
};

struct RoomTypeConfig {
    std::string id;
    float weight;
    std::vector<std::string> enemy_species;
};

struct RoomSpawnConfig {
    std::vector<RoomTypeConfig> roomTypes;
};

struct BossTypeConfig {
    std::string id;
    int min_depth;
};

struct BossSpawnConfig {
    int first_appear;
    int every;
    std::vector<BossTypeConfig> types;
};

struct ChestSpawnConfig {
    float base_count;
    int every;
    std::unordered_map<std::string, float> loot; // item_id -> вероятность
};

class SpawnConfig {
private:
    mutable std::unordered_map<int, std::vector<const EnemyTypeConfig*>> enemiesCache_;
    mutable std::unordered_map<int, std::vector<const ItemTypeConfig*>> itemsCache_;
    mutable std::unordered_map<int, std::vector<const BossTypeConfig*>> bossesCache_;
    mutable std::vector<const ArmorClassConfig*> armorClassesCache_;
    mutable std::vector<const WeaponClassConfig*> weaponClassesCache_;

public:
    SpawnConfig() = default;
    ~SpawnConfig() {
        enemiesCache_.clear(); itemsCache_.clear(); bossesCache_.clear();
        armorClassesCache_.clear(); weaponClassesCache_.clear();
    }

    EnemySpawnConfig enemies;
    ItemSpawnConfig items;
    RoomSpawnConfig rooms;
    std::vector<ArmorClassConfig> armor_classes;
    std::vector<WeaponClassConfig> weapon_classes;
    BossSpawnConfig bosses;
    ChestSpawnConfig chests;

    const std::vector<const EnemyTypeConfig*>& getEnemies(int depth) const;
    const std::vector<const ItemTypeConfig*>& getItems(int depth) const;
    const std::vector<const BossTypeConfig*>& getBosses(int depth) const;
    const std::vector<const WeaponClassConfig*>& getWeaponClasses() const;
    const std::vector<const ArmorClassConfig*>& getArmorClasses() const;
};

#endif // SPAWN_CONFIG_H