#ifndef TILE_COLOR_H
#define TILE_COLOR_H

#include <unordered_map>
#include <string>

#include "TileType.h"

class TileColor {
public:
    inline static std::unordered_map<TileType, std::string> tile_base_colors = {
    {TileType::WALL, "grey"},
    {TileType::GROUND, "dark green"},
    {TileType::DOOR_OPEN, "light brown"},
    {TileType::DOOR_CLOSED, "brown"}
    };
};

#endif // TILE_COLOR_H
