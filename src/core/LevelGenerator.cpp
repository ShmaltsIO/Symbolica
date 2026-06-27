#include "LevelGenerator.h"

RoomFiller& LevelGenerator::getRoomFiller() {
	return room_filler_;
}

Map LevelGenerator::generateLevel(int width, int height, int level_number) {
	Map map = dungeon_gen_.generate(width, height);
	room_filler_.fill(dungeon_gen_.getRooms(), map, level_number);
	return map;
}
