#ifndef BSP_NODE_H
#define BSP_NODE_H

struct BSPRoom {
    int x, y, w, h;
    int centerX, centerY;

    std::string type;
    unsigned int difficult;
};

struct BSPNode {
    int x, y, w, h;
    BSPNode* left = nullptr;
    BSPNode* right = nullptr;
    BSPRoom room;
    bool leaf = false;

    BSPNode(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}
    ~BSPNode() { delete left; delete right; }
};

#endif // BSP_NODE_H