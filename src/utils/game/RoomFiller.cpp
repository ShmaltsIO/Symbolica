#include "RoomFiller.h"

EntityFabric* RoomFiller::getEntityFabric() {
    return entity_fabric;
}

SpawnConfig* RoomFiller::getSpawnConfig() {
    return spawn_config_;
}

int RoomFiller::calculateHealth(int level_number) {
    if (level_number <= 0) {
        return spawn_config_->enemies.base_health;
    }

    return (spawn_config_->enemies.base_health + level_number*(level_number-1)/2);
}

int RoomFiller::calculateDamage(int level_number) {
    int n = spawn_config_->enemies.base_damage;

    if (n <= 0) n = 1;

    double f = (std::log(n * std::pow(level_number + 1, n)));

    int res = static_cast<int>(std::round(f));

    if (res < 1) res = 1;

    return res;
}

int RoomFiller::calculateProtection(int level_number) {
    float f = std::round((std::log(level_number+1)));
    return static_cast<int>(f);
}

int RoomFiller::calculateExperienceReward(int level_number) {
    int b = spawn_config_->enemies.base_health;
    int dm = calculateDamage(level_number);

    if (dm <= 1) dm = 2;

    std::uniform_real_distribution<double> dist(1.0, static_cast<double>(dm));

    float f = std::round(b*(std::log(b*std::pow(level_number+1, dist(rng_)))));

    return static_cast<int>(f);
}

int RoomFiller::calculateWorth(int level_number) {
    float f = std::round(std::sqrt(calculateDamage(level_number+1)));

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

    // 1. Проверка, что есть доступные враги
    if (available_enemies.empty()) {
        // Логируем или просто пропускаем врагов
        std::cerr << "Warning: no available enemies for depth " << level_number << std::endl;
        // Можно продолжить без врагов
    }

    // 2. Распределение для предметов
    std::vector<EntityType> items = { EntityType::COIN, EntityType::FOOD };
    std::vector<size_t> chances = { 50, 50 };
    auto items_dist = std::discrete_distribution<size_t>(chances.begin(), chances.end());

    // 3. Проходим по комнатам
    for (BSPRoom& room : rooms) {
        // Выбираем тип комнаты
        RoomTypeConfig chosen = spawn_config_->rooms.roomTypes[dist_(rng_)];
        room.type = chosen.id;
        room.difficult = 1; // TODO

        // 4. Собираем свободные клетки для ЭТОЙ комнаты
        std::vector<Vector2D> freeCells;
        for (int dx = room.x + 1; dx < room.x + room.w - 1; ++dx) {
            for (int dy = room.y + 1; dy < room.y + room.h - 1; ++dy) {
                if (map.isWalkable(dx, dy)) {
                    freeCells.push_back({ dx, dy });
                }
            }
        }
        if (freeCells.empty()) continue;

        // 5. Перемешиваем клетки
        std::shuffle(freeCells.begin(), freeCells.end(), rng_);

        // 6. Расставляем врагов
        unsigned int enemy_quota = calculateQuotaEnemies(level_number);
        if (enemy_quota > freeCells.size()) {
            enemy_quota = freeCells.size(); // или половину, как хочешь
        }

        if (!available_enemies.empty() && !chosen.enemy_species.empty()) {
            std::uniform_int_distribution<size_t> enemyTypeDist(0, available_enemies.size() - 1);
            std::uniform_int_distribution<size_t> speciesDist(0, chosen.enemy_species.size() - 1);

            for (unsigned int i = 0; i < enemy_quota; ++i) {
                const EnemyTypeConfig* enemy_type = available_enemies[enemyTypeDist(rng_)];
                std::string enemy_spec = chosen.enemy_species[speciesDist(rng_)];

                Vector2D pos = freeCells[i];

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

                entity_fabric->createEntityFrom(*spawn_config_, level_number, params);
            }
        }

        // 7. Расставляем предметы (используем оставшиеся клетки)
        unsigned int items_quota = calculateQuotaItems(level_number);
        size_t startIndex = enemy_quota; // после врагов
        if (items_quota > freeCells.size() - startIndex) {
            items_quota = freeCells.size() - startIndex;
        }

        for (unsigned int i = 0; i < items_quota; ++i) {
            EntityType item_type = items[items_dist(rng_)];
            Vector2D pos = freeCells[startIndex + i];

            EntityParams params;
            params.entity_type = item_type;
            params.position = pos;
            params.name = "TEST";

            int a = 0, b = 1;
            switch (item_type) {
            case EntityType::COIN: a = 1; b = 5; break;
            case EntityType::FOOD: a = 10; b = 15; break;
            default: break;
            }
            std::uniform_int_distribution<int> dist_i(a, b);
            params.worth = dist_i(rng_);

            entity_fabric->createEntityFrom(*spawn_config_, level_number, params);
        }
    }
}
