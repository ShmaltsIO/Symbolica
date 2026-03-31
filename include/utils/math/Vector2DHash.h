#ifndef VECTOR2D_HASH_H
#define VECTOR2D_HASH_H

#include "Vector2D.h"
#include <functional>

namespace std {
    template<> struct hash<Vector2D>
    {
        size_t operator() (const Vector2D& vector) const {
            size_t hash = 0;
            hash = std::hash<double>()(vector.getLength()) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
            return hash;
        }
    };
}


#endif // VECTOR2D_HASH_H