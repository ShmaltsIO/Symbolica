#ifndef GRID_H
#define GRID_H

#include "Vector2D.h"
#include "Vector2DHash.h"
#include <unordered_map>

/**
 * @brief The grid structure represent game map.
 * @param width_ is width of grid;
 * @param height_ is height of grid;
 * @param map_ is map with pairs {Vector2D : int}, i.e. position contains entity ID;
 * @param level_number_ is number of game level;
 */
struct Grid
{
    int width_ = 1;
    int height_ = 1;
    std::unordered_map<Vector2D, int> map_;
    unsigned int level_number_ = 1;

    Grid(int width, int height) {
        width_ = width;
        height_ = height;
        map_ = {};
    }

    Grid(Grid& grid) {
        width_ = grid.width_;
        height_ = grid.height_;
        map_ = grid.map_;
    }

    Grid(const Grid& grid) {
        width_ = grid.width_;
        height_ = grid.height_;
        map_ = grid.map_;
        level_number_ = grid.level_number_;
    }

    ~Grid() = default;

    Grid& operator=(const Grid& grid) {
        if (this != &grid) {
            width_ = grid.width_;
            height_ = grid.height_;
            map_ = grid.map_;
            level_number_ = grid.level_number_;
        }
        return *this;
    }
};

#endif // GRID_H