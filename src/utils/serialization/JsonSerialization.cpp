#include "JsonSerialization.h"

// ---- SpawnConfig ----
void from_json(const nlohmann::json& j, EnemyTypeConfig& cfg) {
    j.at("id").get_to(cfg.id);
    j.at("min_depth").get_to(cfg.min_depth);
}

void from_json(const nlohmann::json& j, EnemySpawnConfig& cfg) {
    j.at("base_count").get_to(cfg.base_count);
    j.at("base_health").get_to(cfg.base_health);
    j.at("base_damage").get_to(cfg.base_damage);
    j.at("max_per_room").get_to(cfg.max_per_room);
    j.at("weights").at("distance_factor").get_to(cfg.weights.distance_factor);
    j.at("weights").at("random_factor").get_to(cfg.weights.random_factor);
    j.at("types").get_to(cfg.types);
}

void from_json(const nlohmann::json& j, ItemTypeConfig& cfg) {
    j.at("id").get_to(cfg.id);
    j.at("weight").get_to(cfg.weight);
    j.at("min_depth").get_to(cfg.min_depth);
}

void from_json(const nlohmann::json& j, ItemSpawnConfig& cfg) {
    j.at("base_count").get_to(cfg.base_count);
    j.at("per_depth").get_to(cfg.per_depth);
    j.at("types").get_to(cfg.types);
}

void from_json(const nlohmann::json& j, RoomTypeConfig& cfg) {
    j.at("id").get_to(cfg.id);
    j.at("weight").get_to(cfg.weight);
    j.at("enemy_species").get_to(cfg.enemy_species);
}

void from_json(const nlohmann::json& j, RoomSpawnConfig& cfg) {
    j.at("rooms").get_to(cfg.roomTypes);
}

void from_json(const nlohmann::json& j, ArmorClassConfig& cfg) {
    j.at("id").get_to(cfg.id);
    j.at("class").get_to(cfg.armor_class);
    j.at("titles").get_to(cfg.titles);
}

void from_json(const nlohmann::json& j, WeaponClassConfig& cfg) {
    j.at("id").get_to(cfg.id);
    j.at("class").get_to(cfg.weapon_class);
    j.at("titles").get_to(cfg.titles);
}

void from_json(const nlohmann::json& j, BossTypeConfig& cfg) {
    j.at("id").get_to(cfg.id);
    j.at("min_depth").get_to(cfg.min_depth);
}

void from_json(const nlohmann::json& j, BossSpawnConfig& cfg) {
    j.at("first_appear").get_to(cfg.first_appear);
    j.at("every").get_to(cfg.every);
    j.at("types").get_to(cfg.types);
}

void from_json(const nlohmann::json& j, ChestSpawnConfig& cfg) {
    j.at("base_count").get_to(cfg.base_count);
    j.at("every").get_to(cfg.every);
    j.at("loot").get_to(cfg.loot);
}

void from_json(const nlohmann::json& j, SpawnConfig& cfg) {
    auto spawn = j.at("spawn");
    from_json(spawn.at("enemies"), cfg.enemies);
    from_json(spawn, cfg.rooms);
    from_json(spawn.at("items"), cfg.items);
    cfg.armor_classes = spawn.at("armor_classes").get<std::vector<ArmorClassConfig>>();
    cfg.weapon_classes = spawn.at("weapon_classes").get<std::vector<WeaponClassConfig>>();
    from_json(spawn.at("bosses"), cfg.bosses);
    from_json(spawn.at("chests"), cfg.chests);
}
