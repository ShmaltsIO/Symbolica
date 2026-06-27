#ifndef DUNGEON_GENERATOR_H
#define DUNGEON_GENERATOR_H

#include <vector>
#include <random>
#include <memory>
#include <algorithm>
#include <iostream>
#include <string>

#include "Map.h"
#include "TileType.h"
#include "BSPNode.h"

class DungeonGenerator {
private:
    std::mt19937 rng_;
    int minRoomSize_ = 4;
    int maxRoomSize_ = 10;
    int minLeafSize_ = 6;
    std::vector<BSPRoom> rooms_;

    BSPNode* split(BSPNode* node, int depth);
    void createRooms(BSPNode* node, Map& map);
    void connectRooms(BSPNode* node, Map& map);
    void carveRoom(Map& map, const BSPRoom& room);
    void carveHCorridor(Map& map, int x1, int x2, int y);
    void carveVCorridor(Map& map, int y1, int y2, int x);
    bool isInsideMap(const Map& map, int x, int y) const;

public:
    DungeonGenerator(unsigned int seed = std::random_device{}());
    DungeonGenerator(unsigned int seed, int min_room_size, int max_room_size, int min_leaf_size): rng_(seed), minRoomSize_(min_leaf_size), maxRoomSize_(max_room_size), minLeafSize_(min_leaf_size) {}
    
    ~DungeonGenerator() { rooms_.clear(); minLeafSize_ = 0; minRoomSize_ = 0; maxRoomSize_ = 0; }
    
    Map generate(int width, int height);
    const std::vector<BSPRoom>& getRooms() const;
    std::vector<BSPRoom>& getRooms();
};

#endif