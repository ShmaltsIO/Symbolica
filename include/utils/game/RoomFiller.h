#ifndef ROOM_FILLER_H
#define ROOM_FILLER_H

#include <random>
#include <cmath>

#include "BSPNode.h"
#include "SpawnConfig.h"
#include "EntityFabric.h"
#include "EntityParams.h"
#include "EntityType.h"
#include "Map.h"

class RoomFiller {
private:
	std::mt19937 rng_;
	SpawnConfig* spawn_config_ = nullptr;
	EntityFabric* entity_fabric = nullptr;
	std::discrete_distribution<size_t> dist_;


	void buildDistribution();
	unsigned int calculateQuotaEnemies(int);
	unsigned int calculateQuotaItems(int);

	int calculateHealth(int);
	int calculateDamage(int);
	int calculateProtection(int);
	int calculateExperienceReward(int);
	int calculateWorth(int);

public:
	RoomFiller() = delete;
	RoomFiller(unsigned int seed, SpawnConfig* spawn_config, EntityFabric* entity_fabric): rng_(seed), spawn_config_(spawn_config), entity_fabric(entity_fabric) {
		buildDistribution();
	}

	~RoomFiller() = default;

	EntityFabric* getEntityFabric();
	SpawnConfig* getSpawnConfig();

	void fill(std::vector<BSPRoom>& rooms, const Map& map, int level_number);
};

#endif // ROOM_FILLER_H