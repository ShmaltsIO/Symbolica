#ifndef LEVEL_GENERATOR_H
#define LEVEL_GENERATOR_H

#include "DungeonGenerator.h"
#include "RoomFiller.h"
#include "Map.h"

class LevelGenerator {
private:
	DungeonGenerator dungeon_gen_;
	RoomFiller room_filler_;

public:
	LevelGenerator() = delete;
	LevelGenerator(SpawnConfig* spawnConfig, EntityFabric* entityFabric, unsigned int seed = 42)
		: dungeon_gen_(seed), room_filler_(seed, spawnConfig, entityFabric) {}

	~LevelGenerator() = default;

	RoomFiller& getRoomFiller();

	Map generateLevel(int width, int height, int level_number);
};

#endif // LEVEL_GENERATOR_H
