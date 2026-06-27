#include "EntityFabric.h"

Entity* EntityFabric::createBaseEntity() {
	auto entity = em->CreateEntity();
    entity->Add<TransformComponent>(Vector2D(0, 0));
    entity->Add<TextureComponent>('~');
    entity->Add<ColliderComponent>();
    entity->Add<ColorComponent>("white");

    return entity;
}

Entity* EntityFabric::createAliveBaseEntity() {
    auto entity = createBaseEntity();

    entity->Add<MovementComponent>(Vector2D(0, 0), Vector2D(0, 0));
    entity->Add<HealthComponent>(1, 1);
    entity->Add<DamageComponent>(0, 0);
    entity->Add<RadiusComponent>();
    entity->Add<LocationComponent>();
    entity->Add<ProtectionComponent>();
    entity->Add<ExperienceComponent>(0, 1);
    entity->Add<WorthComponent>(0);
    entity->Add<NameComponent>();

    return entity;
}

Entity* EntityFabric::createPlayer() {
    auto player = createAliveBaseEntity();

    player->Add<PlayerTagComponent>();

    player->Get<HealthComponent>()->setHealth(20);
    player->Get<HealthComponent>()->setHealthLimit(20);
    player->Get<DamageComponent>()->setDamage(2);
    player->Get<TextureComponent>()->symbol_ = static_cast<char>(GameObjectsTexture::PLAYER);

    player->Add<WorthComponent>(0);
    player->Add<StepComponent>(0);
    player->Add<LevelComponent>(1);
    player->Add<ExperienceComponent>(0, 10);
    player->Add<InventoryComponent>();
    player->Add<EquipmentComponent>();

    return player;
}

Entity* EntityFabric::createObserver() {
    auto observer = em->CreateEntity();

    observer->Add<ObserverTagComponent>();
    observer->Add<TransformComponent>(Vector2D(0, 0));
    observer->Add<StepLimitComponent>(100);

    return observer;
}

Entity* EntityFabric::createEntityFrom(const SpawnConfig& config, const int level_number, const EntityParams& params) {
    Entity* en = nullptr;
    
    switch (params.entity_type)
    {
    case(EntityType::PLAYER):
        en = createPlayer();
        break;
    case(EntityType::COIN):
        en = createCoinFrom(config.items, params);
        break;
    case(EntityType::FOOD):
        en = createFoodFrom(config.items, params);
        break;
    case(EntityType::ENEMY):
        en = createEnemyFrom(params);
        break;
    case(EntityType::BOSS):
        //en = createBossFrom(config.bosses, level_number);
        break;
    case(EntityType::ARMOR):
        //en = createArmorFrom(config.armor_classes, level_number, room_config);
        break;
    case(EntityType::WEAPON):
        //en = createEnemyFrom(config.enemies, level_number, room_config);
        break;
    case(EntityType::CHEST):
        //en = createEnemyFrom(config.enemies, level_number, room_config);
        break;
    default:
        break;
    }
    
    return en;
}

Entity* EntityFabric::createEnemyFrom(const EntityParams& params) {
    auto enemy = createAliveBaseEntity();

    enemy->Add<EnemyTagComponent>();
    enemy->Add<PathToTargetComponent>();

    enemy->Get<HealthComponent>()->setHealthLimit(params.health);
    enemy->Get<HealthComponent>()->setHealth(params.health);

    enemy->Get<DamageComponent>()->setDamage(params.damage);
    enemy->Get<ProtectionComponent>()->setProtection(params.protection);

    enemy->Get<TextureComponent>()->symbol_ = static_cast<char>(GameObjectsTexture::ENEMY);
    enemy->Get<ColorComponent>()->setColor(EntityColor::entity_base_colors.at(EntityType::ENEMY));

    enemy->Get<NameComponent>()->setName(params.name);
    
    enemy->Get<NameComponent>()->setTitle(params.title);

    enemy->Get<ExperienceComponent>()->setExperience(0);
    enemy->Get<ExperienceComponent>()->setExperienceLimit(params.experienceReward);

    enemy->Get<WorthComponent>()->setWorth(params.worth);

    enemy->Get<TransformComponent>()->position_ = params.position;
    
    return enemy;
}

Entity* EntityFabric::createBossFrom(const BossSpawnConfig& config, const int level_number) {
    return nullptr;
}

Entity* EntityFabric::createCoinFrom(const ItemSpawnConfig& config, const EntityParams& params) {
    auto coin = createBaseEntity();

    coin->Add<MoneyTagComponent>();
    coin->Add<WorthComponent>(0);

    coin->Get<WorthComponent>()->setWorth(params.worth);
    coin->Get<TextureComponent>()->symbol_ = static_cast<char>(GameObjectsTexture::COIN);
    coin->Get<ColorComponent>()->setColor(EntityColor::entity_base_colors.at(EntityType::COIN));

    coin->Get<TransformComponent>()->position_ = params.position;

    return coin;
}

Entity* EntityFabric::createFoodFrom(const ItemSpawnConfig& config, const EntityParams& params) {
    auto food = createBaseEntity();

    food->Add<ItemTagComponent>();
    food->Add<WorthComponent>(0);

    food->Get<WorthComponent>()->setWorth(params.worth);
    food->Get<TextureComponent>()->symbol_ = static_cast<char>(GameObjectsTexture::FOOD);
    food->Get<ColorComponent>()->setColor(EntityColor::entity_base_colors.at(EntityType::FOOD));

    food->Add<OnPlaceComponent>();

    food->Get<TransformComponent>()->position_ = params.position;

    return food;
}

Entity* EntityFabric::createArmorFrom(const ArmorClassConfig& config, const int level_number) {
    return nullptr;
}

Entity* EntityFabric::createWeaponFrom(const WeaponClassConfig& config, const int level_number) {
    return nullptr;
}

Entity* EntityFabric::createChestFrom(const ChestSpawnConfig& config, const int level_number) {
    return nullptr;
}

Entity* EntityFabric::createWall(const TileParams& params) {
    auto wall = createBaseEntity();

    wall->Add<ObstacleTagComponent>();

    wall->Get<TransformComponent>()->position_ = params.position;
    wall->Get<TextureComponent>()->symbol_ = static_cast<char>(GameObjectsTexture::WALL);
    wall->Get<ColorComponent>()->setColor(TileColor::tile_base_colors.at(TileType::WALL));

    return wall;
}

Entity* EntityFabric::createGround(const TileParams& params) {
    auto ground = createBaseEntity();

    ground->Add<GroundTagComponent>();

    ground->Get<TransformComponent>()->position_ = params.position;
    ground->Get<TextureComponent>()->symbol_ = static_cast<char>(GameObjectsTexture::GROUND);
    ground->Get<ColorComponent>()->setColor(TileColor::tile_base_colors.at(TileType::GROUND));

    return ground;
}

Entity* EntityFabric::createDoor(const TileParams& params) {
    return nullptr;
}

void EntityFabric::createMapTiles(const Map& map, int currentLevelId) {
    for (size_t y = 0; y < map.getHeight(); y++) {
        for (size_t x = 0; x < map.getWidth(); x++) {
            TileType tile = map.getTile(x, y);

            TileParams params;
            params.position = Vector2D(x, y);

            switch (tile)
            {
            case TileType::GROUND:
                createGround(params);
                break;
            case TileType::WALL:
                createWall(params);
                break;
            //case TileType::DOOR_NEXT:
            //    break;
            //case TileType::DOOR_PREV:
            //    break;
            //case TileType::DOOR_CLOSED:
            //    break;
            //case TileType::DOOR_OPEN:
            //    break;
            default:
                break;
            }
        }
    }
}
