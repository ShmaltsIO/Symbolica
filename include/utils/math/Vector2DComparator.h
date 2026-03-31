#ifndef VECTOR2D_COMPARATOR_H
#define VECTOR2D_COMPARATOR_H

#include "Vector2D.h"

struct Vector2DComparator {
    bool operator() (const Vector2D& vector_one, const Vector2D& vector_two) {
        return false;
    }
};

#endif // VECTOR2D_COMPARATOR_H