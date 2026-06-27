#ifndef TILE_PARAMS_H
#define TILE_PARAMS_H

#include "Vector2D.h"
#include "TileType.h"

class TileParams {
public:
    Vector2D position;
    TileType tile_type = TileType::GROUND;
    bool is_next_level = false;
};

#endif // TILE_PARAMS_H