#ifndef NODE_H
#define NODE_H

#include "Vector2D.h"

struct Node {
    Vector2D position_;
    int cost_;
    int heuristic_cost_;
    Node* parent;

    int getTotalCost() const {
        return cost_ + heuristic_cost_;
    }

    Node(Vector2D& position): position_(position), cost_(0), heuristic_cost_(0), parent(nullptr) {}
};

#endif // NODE_H