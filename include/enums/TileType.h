#ifndef TILE_TYPE_H
#define TILE_TYPE_H

enum class TileType : char {
    GROUND = '0',
    WALL = '1',
    DOOR_NEXT = 'D',
    DOOR_PREV = 'U',
    DOOR_CLOSED = 'C',
    DOOR_OPEN = 'O'
};

#endif // TILE_TYPE_H