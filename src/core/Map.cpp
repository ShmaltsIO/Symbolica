#include "Map.h"

Map::Map(size_t width, size_t height, TileType defaultTile)
    : width_(width), height_(height)
    , tiles_(height, std::vector<TileType>(width, defaultTile)) {}

TileType Map::getTile(size_t x, size_t y) const {
    return tiles_[y][x];
}

void Map::setTile(size_t x, size_t y, TileType tile) {
    tiles_[y][x] = tile;
}

TileType Map::at(size_t x, size_t y) const {
    if (x >= width_ || y >= height_)
        throw std::out_of_range("Map::at: out of range");
    return tiles_[y][x];
}

TileType Map::operator()(size_t x, size_t y) const {
    return tiles_[y][x];
}

bool Map::isInside(size_t x, size_t y) const {
    return x < width_ && y < height_;
}

bool Map::isWalkable(size_t x, size_t y) const {
    if (!isInside(x, y)) return false;
    TileType t = tiles_[y][x];
    return t == TileType::GROUND || t == TileType::DOOR_NEXT || t == TileType::DOOR_PREV;
}

nlohmann::json Map::toJson() const {
    nlohmann::json j;
    j["width"] = width_;
    j["height"] = height_;
    j["tiles"] = nlohmann::json::array();
    for (size_t y = 0; y < height_; ++y) {
        nlohmann::json row = nlohmann::json::array();
        for (size_t x = 0; x < width_; ++x) {
            row.push_back(static_cast<char>(tiles_[y][x]));
        }
        j["tiles"].push_back(row);
    }
    return j;
}

void Map::fromJson(const nlohmann::json& j) {
    width_ = j["width"];
    height_ = j["height"];
    tiles_.resize(height_, std::vector<TileType>(width_));
    auto tilesJson = j["tiles"];
    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            char ch = tilesJson[y][x].get<std::string>()[0];
            tiles_[y][x] = static_cast<TileType>(ch);
        }
    }
}