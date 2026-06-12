#ifndef MAP_H
#define MAP_H

#include <vector>
#include <cstddef>
#include <stdexcept>

#include "TileType.h"
#include "json.hpp"

class Map {
private:
    size_t width_ = 0;
    size_t height_ = 0;
    std::vector<std::vector<TileType>> tiles_; // [y][x]

public:
    Map() = default;
    Map(size_t width, size_t height, TileType defaultTile = TileType::WALL);
    Map(const Map&) = default;
    Map(Map&&) = default;
    Map& operator=(const Map&) = default;
    Map& operator=(Map&&) = default;

    TileType getTile(size_t x, size_t y) const;
    void setTile(size_t x, size_t y, TileType tile);
    TileType at(size_t x, size_t y) const;
    TileType operator()(size_t x, size_t y) const;

    size_t getWidth() const { return width_; }
    size_t getHeight() const { return height_; }

    const std::vector<std::vector<TileType>>& getData() const { return tiles_; }
    std::vector<std::vector<TileType>>& getData() { return tiles_; }

    bool isInside(size_t x, size_t y) const;
    bool isWalkable(size_t x, size_t y) const;

    // Сериализация
    nlohmann::json toJson() const;
    void fromJson(const nlohmann::json& j);
};

#endif // MAP_H