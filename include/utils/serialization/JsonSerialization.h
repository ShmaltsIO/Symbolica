#ifndef JSON_SERIALIZATION_H
#define JSON_SERIALIZATION_H

#include "json.hpp"
#include "Vector2D.h"
#include "ItemStats.h"
#include "ItemData.h"
#include "PlayerSaveData.h"
#include "SpawnConfig.h"

// ---- SpawnConfig ----
void from_json(const nlohmann::json& j, EnemyTypeConfig& cfg);
void from_json(const nlohmann::json& j, EnemySpawnConfig& cfg);
void from_json(const nlohmann::json& j, ItemTypeConfig& cfg);
void from_json(const nlohmann::json& j, ItemSpawnConfig& cfg);
void from_json(const nlohmann::json& j, RoomTypeConfig& cfg);
void from_json(const nlohmann::json& j, RoomSpawnConfig& cfg);
void from_json(const nlohmann::json& j, ArmorClassConfig& cfg);
void from_json(const nlohmann::json& j, WeaponClassConfig& cfg);
void from_json(const nlohmann::json& j, BossTypeConfig& cfg);
void from_json(const nlohmann::json& j, BossSpawnConfig& cfg);
void from_json(const nlohmann::json& j, ChestSpawnConfig& cfg);
void from_json(const nlohmann::json& j, SpawnConfig& cfg);

// ---- Vector2D ----
namespace nlohmann {
    template<>
    struct adl_serializer<Vector2D> {
        static void to_json(json& j, const Vector2D& v) {
            j = { v.getX(), v.getY() };
        }
        static void from_json(const json& j, Vector2D& v) {
            v = Vector2D(j[0].get<int>(), j[1].get<int>());
        }
    };

    // ---- ItemStats ----
    template<>
    struct adl_serializer<ItemStats> {
        static void to_json(json& j, const ItemStats& s) {
            j = {
                {"health", s.health},
                {"damage", s.damage},
                {"protection", s.protection},
                {"worth", s.worth}
            };
        }
        static void from_json(const json& j, ItemStats& s) {
            s.health = j.value("health", 0);
            s.damage = j.value("damage", 0);
            s.protection = j.value("protection", 0);
            s.worth = j.value("worth", 0);
        }
    };

    // ---- ItemData ----
    template<>
    struct adl_serializer<ItemData> {
        static void to_json(json& j, const ItemData& item) {
            j = {
                {"prefabId", item.prefabId},
                {"count", item.count},
                {"stats", item.stats}
            };
        }
        static void from_json(const json& j, ItemData& item) {
            item.prefabId = j.at("prefabId").get<std::string>();
            item.count = j.value("count", 1);
            if (j.contains("stats")) {
                item.stats = j.at("stats").get<ItemStats>();
            }
        }
    };

    // ---- PlayerSaveData ----
    template<>
    struct adl_serializer<PlayerSaveData> {
        static void to_json(json& j, const PlayerSaveData& data) {
            j = {
                {"health", data.health},
                {"maxHealth", data.maxHealth},
                {"damage", data.damage},
                {"protection", data.protection},
                {"level", data.level},
                {"experience", data.experience},
                {"cash", data.cash},
                {"position", data.position},
                {"currentLevelId", data.currentLevelId},
                {"inventory", data.inventory}
            };
        }
        static void from_json(const json& j, PlayerSaveData& data) {
            data.health = j.at("health").get<int>();
            data.maxHealth = j.at("maxHealth").get<int>();
            data.damage = j.at("damage").get<int>();
            data.protection = j.at("protection").get<int>();
            data.level = j.at("level").get<int>();
            data.experience = j.at("experience").get<int>();
            data.cash = j.at("cash").get<int>();
            data.position = j.at("position").get<Vector2D>();
            data.currentLevelId = j.at("currentLevelId").get<int>();
            data.inventory = j.at("inventory").get<std::vector<ItemData>>();
        }
    };
} // namespace nlohmann

#endif // JSON_SERIALIZATION_H