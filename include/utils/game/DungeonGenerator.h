#ifndef DUNGEON_GENERATOR_H
#define DUNGEON_GENERATOR_H

#include <vector>
#include <random>
#include <memory>
#include <algorithm>
#include <iostream>

#include "Map.h"
#include "TileType.h"

struct BSPRoom {
    int x, y, w, h;
    int centerX, centerY;
};

struct BSPNode {
    int x, y, w, h;
    BSPNode* left = nullptr;
    BSPNode* right = nullptr;
    BSPRoom room;
    bool leaf = false;

    BSPNode(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}
    ~BSPNode() { delete left; delete right; }
};

class DungeonGenerator {
public:
    DungeonGenerator(unsigned int seed = std::random_device{}());
    Map generate(int width, int height);

private:
    std::mt19937 rng_;
    int minRoomSize_ = 4;
    int maxRoomSize_ = 10;
    int minLeafSize_ = 6;

    BSPNode* split(BSPNode* node, int depth);
    void createRooms(BSPNode* node, Map& map);
    void connectRooms(BSPNode* node, Map& map);
    void carveRoom(Map& map, const BSPRoom& room);
    void carveHCorridor(Map& map, int x1, int x2, int y);
    void carveVCorridor(Map& map, int y1, int y2, int x);
    bool isInsideMap(const Map& map, int x, int y) const;
};

#endif