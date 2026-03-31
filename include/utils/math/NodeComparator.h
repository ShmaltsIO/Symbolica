#ifndef NODE_COMPARATOR_H
#define NODE_COMPARATOR_H

#include "Node.h"

struct NodeComparator {
    bool operator() (Node* node_one, Node* node_two) {
        return (node_one->getTotalCost() > node_two->getTotalCost());
    }
};

#endif // NODE_COMPARATOR_H