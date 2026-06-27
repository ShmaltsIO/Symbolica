#ifndef A_STAR_H
#define A_STAR_H

#include "Vector2D.h"
#include "Map.h"
#include <vector>
#include <queue>
#include <map>
#include <cmath>

static int heuristic(const Vector2D& a, const Vector2D& b) {
    return abs(a.getX() - b.getX()) + abs(a.getY() - b.getY());
}

static std::vector<Vector2D> aStar(const Vector2D& start, const Vector2D& goal, const Map& map) {
    std::vector<Vector2D> path;
    if (!map.isInside(start.getX(), start.getY()) || !map.isInside(goal.getX(), goal.getY()))
        return path;

    // Узлы для A*
    struct Node {
        Vector2D pos;
        int g = 0;
        int h = 0;
        Node* parent = nullptr;
        int getF() const { return g + h; }
    };

    auto cmp = [](Node* a, Node* b) { return a->getF() > b->getF(); };
    std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> open(cmp);
    std::map<int, Node*> all_nodes;

    Node* startNode = new Node{ start, 0, heuristic(start, goal), nullptr };
    open.push(startNode);
    all_nodes[start.getX() * 1000 + start.getY()] = startNode; // простой хеш

    while (!open.empty()) {
        Node* current = open.top();
        open.pop();

        if (current->pos == goal) {
            // Восстанавливаем путь
            while (current) {
                path.push_back(current->pos);
                current = current->parent;
            }
            std::reverse(path.begin(), path.end());
            // Очищаем память
            for (auto& kv : all_nodes) delete kv.second;
            return path;
        }

        std::vector<Vector2D> dirs = { Vector2D(0,-1), Vector2D(1,0), Vector2D(0,1), Vector2D(-1,0) };
        for (auto& dir : dirs) {
            Vector2D next = current->pos + dir;
            if (!map.isInside(next.getX(), next.getY())) continue;
            if (!map.isWalkable(next.getX(), next.getY())) continue;

            int newG = current->g + 1;
            int key = next.getX() * 1000 + next.getY();
            if (all_nodes.find(key) == all_nodes.end() || newG < all_nodes[key]->g) {
                Node* neighbor = new Node{ next, newG, heuristic(next, goal), current };
                open.push(neighbor);
                all_nodes[key] = neighbor;
            }
        }
    }

    // Путь не найден
    for (auto& kv : all_nodes) delete kv.second;
    return path;
}

//#include "Node.h"
//#include "NodeComparator.h"
//#include "Grid.h"
//#include "GameObjectsEnum.h"
//#include <vector>
//#include <queue>
//#include <map>
//#include <algorithm>
//
//// TODO: can template this?
//static int heuristic(const Vector2D& vector_one, const Vector2D& vector_two) {
//    return getDistanceBetweenVectors2D(vector_one, vector_two);
//}
//
///**
// * @brief Algorithm A*
// * @param start is start Node;
// * @param end is end Node;
// * @param grid is game level map;
// * @param find_optimum is means, what's return's path would be a optimal.
// * @return std::vector<Vector2D> path, empty, if grid not allow fint path from start to end;
// */
//static std::vector<Vector2D> aStar(Node start, Node end, const Grid& grid, std::vector<GameObjectsEnum> obstacles, bool find_optimum) {
//    std::vector<Vector2D> path{};
//    std::priority_queue<Node*, std::vector<Node*>, NodeComparator> open_set;
//    std::map<int, Node*> all_nodes;
//
//    open_set.push(new Node(start.position_));
//    all_nodes[start.position_.getX()*grid.width_ + start.position_.getY()] = &start;
//
//    while(!open_set.empty()) {
//        // std::cout << "FROM WHILE" << std::endl;
//        Node* current = open_set.top();
//        open_set.pop();
//
//        if (current->position_ == end.position_ && find_optimum) {
//            // std::cout << "GOOOOOAL" << std::endl;
//            while (current != nullptr) {
//                // std::cout << "BLEP" << std::endl;
//                path.push_back(current->position_);
//                current = current->parent;
//            }
//            std::reverse(path.begin(), path.end());
//            return path;
//        }
//
//        std::vector<Vector2D> directions = {upVector, rightVector, downVector, leftVector};
//        for (auto dir : directions) {
//            // std::cout << "HELLO NEIGHBORS!" << std::endl;
//            Vector2D new_vector = current->position_ + dir;
//            bool obstacles_complete = true;
//            for (GameObjectsEnum obstacle : obstacles) {
//                if (grid.map_.at(new_vector) == obstacle) {
//                    obstacles_complete = false;
//                    //break;
//                }
//            }
//            // grid.map_.at(new_vector) != GameObjectsEnum::WALL && grid.map_.at(new_vector) != GameObjectsEnum::DOOR_TO && grid.map_.at(new_vector) != GameObjectsEnum::DOOR_FROM
//            if (new_vector >= zeroVector && new_vector.getX() < grid.width_ && new_vector.getY() < grid.height_ && obstacles_complete) {
//                Node* neighbor = new Node(new_vector);
//                neighbor->cost_ = current->cost_ + 1;
//                neighbor->heuristic_cost_ = heuristic(neighbor->position_, end.position_);
//
//                if (all_nodes.find(new_vector.getX()*grid.width_ + new_vector.getY()) == all_nodes.end() || neighbor->cost_ < all_nodes[new_vector.getX()*grid.width_ + new_vector.getY()]->cost_) {
//                    neighbor->parent = current;
//                    open_set.push(neighbor);
//                    all_nodes[new_vector.getX()*grid.width_ + new_vector.getY()] = neighbor;
//                }
//            }
//        }
//        if (!find_optimum) {
//            path.push_back(current->position_);
//            current = current->parent;
//        }
//    }
//    return path;
//}

#endif // A_STAR_H