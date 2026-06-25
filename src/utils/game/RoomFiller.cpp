#include "RoomFiller.h"

int RoomFiller::calculateHealth(int level_number) {
    return (spawn_config_->enemies.base_health + level_number*(level_number-1)/2);
}

int RoomFiller::calculateDamage(int level_number) {
    int n = spawn_config_->enemies.base_damage;

    return static_cast<int>(std::round((std::log(n*std::pow(level_number, n)))));
}

int RoomFiller::calculateProtection(int level_number) {
    float f = std::round((std::log(level_number)));
    return static_cast<int>(f);
}

int RoomFiller::calculateExperienceReward(int level_number) {
    int b = spawn_config_->enemies.base_health;
    int dm = calculateDamage(level_number);

    std::uniform_real_distribution<double> dist(1, dm);

    float f = std::round(b*(std::log(b*std::pow(level_number, dist(rng_)))));

    return static_cast<int>(f);
}

int RoomFiller::calculateWorth(int level_number) {
    float f = std::round(std::sqrt(calculateDamage(level_number)));

    return static_cast<int>(f);
}

void RoomFiller::buildDistribution() {
    if (!spawn_config_ || spawn_config_->rooms.roomTypes.empty()) {
        // TODO: Throwing error...
        return;
    }
    std::vector<float> weights = {};
    for (const auto& type : spawn_config_->rooms.roomTypes) {
        weights.push_back(type.weight);
    }
    dist_ = std::discrete_distribution<size_t>(weights.begin(), weights.end());
}

unsigned int RoomFiller::calculateQuotaEnemies(int level_number) {
    double base = spawn_config_->enemies.base_count;

    double f = base + 3.0 * std::sqrt(std::pow(level_number * 1.0, 3)) / 5.0;

    return (static_cast<unsigned int>(std::round(f)));
}

unsigned int RoomFiller::calculateQuotaItems(int level_number) {
    unsigned int base = spawn_config_->items.base_count;

    double f = base + 2.0 * std::sqrt(std::pow(level_number * 1.0, 3)) / 5.0;

    return (static_cast<unsigned int>(std::round(f)));
}

void RoomFiller::fill(std::vector<BSPRoom>& rooms, const Map& map, int level_number) {
    auto& available_enemies = spawn_config_->getEnemies(level_number);
    std::uniform_int_distribution<size_t> dist(0, available_enemies.size() - 1);

    std::vector<EntityType> items = {EntityType::COIN, EntityType::FOOD};
    std::vector<size_t> chances = {50, 50};
    auto items_dist = std::discrete_distribution<size_t>(chances.begin(), chances.end());

    std::vector<Vector2D> freeCells{};

    for (BSPRoom& room : rooms) {
        RoomTypeConfig chosen = spawn_config_->rooms.roomTypes[dist_(rng_)];
        std::uniform_int_distribution<size_t> d(0, chosen.enemy_species.size() - 1);

        if (freeCells.empty()) {
            for (int dx = room.x + 1; dx < room.x + room.w - 1; ++dx) {
                for (int dy = room.y + 1; dy < room.y + room.h - 1; ++dy) {
                    if (map.isWalkable(dx, dy)) {
                        freeCells.push_back({ dx, dy });
                    }
                }
            }
        }

        if (freeCells.empty()) continue;

        std::uniform_int_distribution<size_t> posDist(0, freeCells.size() - 1);
        
        Vector2D pos = freeCells[posDist(rng_)];

        // Удаляем занятую клетку из списка, чтобы не ставить туда повторно
        freeCells.erase(freeCells.begin() + posDist(rng_));

        room.type = chosen.id;
        room.difficult = 1; // TODO: difficult

        // 1. Fill room by enemies
        unsigned int enemy_quota = calculateQuotaEnemies(level_number);

        if (enemy_quota >= freeCells.size()) {
            if (freeCells.size() % 2 == 1) {
                enemy_quota = freeCells.size() - 1;
            }
            enemy_quota = freeCells.size()/2;
        }

        for (unsigned int i = 0; i < enemy_quota; i++) {
            const EnemyTypeConfig* enemy_type = available_enemies[dist(rng_)];
            std::string enemy_spec = chosen.enemy_species[d(rng_)];

            EntityParams params;
            params.entity_type = EntityType::ENEMY;
            params.damage = calculateDamage(level_number);
            params.health = calculateHealth(level_number);
            params.protection = calculateProtection(level_number);
            params.worth = calculateWorth(level_number);
            params.experienceReward = calculateExperienceReward(level_number);
            params.name = enemy_type->id;
            params.title = enemy_spec;
            params.position = pos;

            auto entity = entity_fabric->createEntityFrom(*spawn_config_, level_number, params);
        }

        // 2. Fill room by items
        unsigned int items_quota = calculateQuotaItems(level_number);

        if (items_quota >= freeCells.size()) {
            if (freeCells.size() % 2 == 1) {
                items_quota = freeCells.size() - 1;
            }
            items_quota = freeCells.size() / 2;
        }

        for (unsigned int i = 0; i < items_quota; i++) {
            EntityType item_type = items[items_dist(rng_)];

            EntityParams params;
            params.entity_type = item_type;

            int a = 0;
            int b = 1;

            switch (item_type)
            {
            case EntityType::COIN:
                a = 1;
                b = 5;
                break;
            case EntityType::FOOD:
                a = 10;
                b = 15;
                break;
            case EntityType::ARMOR:
                //
                break;
            case EntityType::WEAPON:
                //
                break;
            case EntityType::KEY:
                //
                break;
            default:
                //
                break;
            }

            std::uniform_int_distribution<int> dist_i(a, b);
            params.worth = dist_i(rng_);

            params.name = "TEST";
            params.position = pos;

            auto entity = entity_fabric->createEntityFrom(*spawn_config_, level_number, params);
        }

        freeCells.clear();
	}
}
