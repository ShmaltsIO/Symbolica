#ifndef ENTITY_FABRIC_H
#define ENTITY_FABRIC_H

#include "EntityManager.h"
#include "Entity.h"
#include "SpawnConfig.h"
#include "BSPNode.h"
#include "GameObjectsTexture.h"
#include "EntityType.h"
#include "EntityColor.h"
#include "EntityParams.h"
#include "Map.h"
#include "TileParams.h"
#include "TileColor.h"

#include "ColliderComponent.h"
#include "PlayerControlComponent.h"
#include "MovementComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "WorthComponent.h"
#include "HealthComponent.h"
#include "StepComponent.h"
#include "LevelComponent.h"
#include "ExperienceComponent.h"
#include "StepLimitComponent.h"
#include "OpenableComponent.h"
#include "DamageComponent.h"
#include "PathToTargetComponent.h"
#include "ColorComponent.h"
#include "LocationComponent.h"
#include "RadiusComponent.h"
#include "InventoryComponent.h"
#include "OnPlaceComponent.h"
#include "ProtectionComponent.h"
#include "StateComponent.h"
#include "EquipmentComponent.h"
#include "NameComponent.h"
#include "SightRadiusComponent.h"

#include "ObstacleTagComponent.h"
#include "PlayerTagComponent.h"
#include "MoneyTagComponent.h"
#include "FoodTagComponent.h"
#include "ObstacleTagComponent.h"
#include "DoorTagComponent.h"
#include "EnemyTagComponent.h"
#include "ItemTagComponent.h"
#include "ArmorTagComponent.h"
#include "WeaponTagComponent.h"
#include "GroundTagComponent.h"
#include "ObserverTagComponent.h"

class EntityFabric {
private:
	EntityManager* em = nullptr;

	Entity* createBaseEntity();
	Entity* createAliveBaseEntity();

public:
	EntityFabric() = delete;
	EntityFabric(EntityManager* em) : em(em) {}

	~EntityFabric() { em = nullptr; }

	Entity* createPlayer();
	Entity* createObserver();

	Entity* createEntityFrom(const SpawnConfig& config, const int level_number, const EntityParams& params);
	
	Entity* createEnemyFrom(const EntityParams& params);
	Entity* createBossFrom(const BossSpawnConfig& config, const int level_number);
	Entity* createCoinFrom(const ItemSpawnConfig& config, const EntityParams& params);
	Entity* createFoodFrom(const ItemSpawnConfig& config, const EntityParams& params);
	Entity* createArmorFrom(const ArmorClassConfig& config, const int level_number);
	Entity* createWeaponFrom(const WeaponClassConfig& config, const int level_number);
	Entity* createChestFrom(const ChestSpawnConfig& config, const int level_number);

	Entity* createWall(const TileParams& params);
	Entity* createGround(const TileParams& params);
	Entity* createDoor(const TileParams& params);
	void createMapTiles(const Map& map, int currentLevelId);
};

#endif // ENTITY_FABRIC_H