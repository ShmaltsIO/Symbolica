#include "DungeonGenerator.h"

DungeonGenerator::DungeonGenerator(unsigned int seed) : rng_(seed) {}

Map DungeonGenerator::generate(int width, int height) {
    Map map(width, height, TileType::WALL);
    BSPNode* root = new BSPNode(0, 0, width, height);
    split(root, 0);
    createRooms(root, map);
    connectRooms(root, map);
    delete root;
    return map;
}

BSPNode* DungeonGenerator::split(BSPNode* node, int depth) {
    if (node->w < minLeafSize_ * 2 || node->h < minLeafSize_ * 2 || depth > 5) {
        node->leaf = true;
        return node;
    }

    bool splitH = false;
    if (node->w > node->h && node->w / node->h >= 1.25) splitH = false;
    else if (node->h > node->w && node->h / node->w >= 1.25) splitH = true;
    else splitH = std::uniform_int_distribution<>(0, 1)(rng_);

    int maxSplit = (splitH ? node->h : node->w) - minLeafSize_;
    if (maxSplit <= minLeafSize_) {
        node->leaf = true;
        return node;
    }

    int splitPos = std::uniform_int_distribution<>(minLeafSize_, maxSplit)(rng_);

    if (splitH) {
        node->left = new BSPNode(node->x, node->y, node->w, splitPos);
        node->right = new BSPNode(node->x, node->y + splitPos, node->w, node->h - splitPos);
    } else {
        node->left = new BSPNode(node->x, node->y, splitPos, node->h);
        node->right = new BSPNode(node->x + splitPos, node->y, node->w - splitPos, node->h);
    }

    split(node->left, depth + 1);
    split(node->right, depth + 1);
    return node;
}

void DungeonGenerator::createRooms(BSPNode* node, Map& map) {
    if (!node->leaf) {
        createRooms(node->left, map);
        createRooms(node->right, map);
        return;
    }

    int roomW = node->w - 2;
    int roomH = node->h - 2;
    int roomX = node->x + 1;
    int roomY = node->y + 1;

    if (roomW < 2 || roomH < 2) return;

    node->room = { roomX, roomY, roomW, roomH,
                   roomX + roomW / 2, roomY + roomH / 2 };

    rooms_.push_back(node->room);

    carveRoom(map, node->room);
}

void DungeonGenerator::carveRoom(Map& map, const BSPRoom& room) {
    for (int x = room.x; x < room.x + room.w; ++x)
        for (int y = room.y; y < room.y + room.h; ++y)
            if (map.isInside(x, y))
                map.setTile(x, y, TileType::GROUND);
}

void DungeonGenerator::connectRooms(BSPNode* node, Map& map) {
    if (!node->leaf) {
        connectRooms(node->left, map);
        connectRooms(node->right, map);

        // Join left and right sub-trees
        if (node->left->leaf && node->right->leaf) {
            const auto& r1 = node->left->room;
            const auto& r2 = node->right->room;
            // Join the centres by L-coridor
            carveHCorridor(map, r1.centerX, r2.centerX, r1.centerY);
            carveVCorridor(map, r1.centerY, r2.centerY, r2.centerX);
        } else {
            BSPNode* leaf1 = node->left;
            while (!leaf1->leaf) leaf1 = leaf1->left;
            BSPNode* leaf2 = node->right;
            while (!leaf2->leaf) leaf2 = leaf2->left;
            const auto& r1 = leaf1->room;
            const auto& r2 = leaf2->room;
            carveHCorridor(map, r1.centerX, r2.centerX, r1.centerY);
            carveVCorridor(map, r1.centerY, r2.centerY, r2.centerX);
        }
    }
}

void DungeonGenerator::carveHCorridor(Map& map, int x1, int x2, int y) {
    int from = std::min(x1, x2);
    int to   = std::max(x1, x2);
    for (int x = from; x <= to; ++x)
        if (map.isInside(x, y))
            map.setTile(x, y, TileType::GROUND);
}

void DungeonGenerator::carveVCorridor(Map& map, int y1, int y2, int x) {
    int from = std::min(y1, y2);
    int to   = std::max(y1, y2);
    for (int y = from; y <= to; ++y)
        if (map.isInside(x, y))
            map.setTile(x, y, TileType::GROUND);
}

bool DungeonGenerator::isInsideMap(const Map& map, int x, int y) const {
    return x >= 0 && x < static_cast<int>(map.getWidth()) &&
           y >= 0 && y < static_cast<int>(map.getHeight());
}

const std::vector<BSPRoom>& DungeonGenerator::getRooms() const { return rooms_; }
