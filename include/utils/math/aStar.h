#ifndef A_STAR_H
#define A_STAR_H

#include "Node.h"
#include "NodeComparator.h"
#include "Grid.h"
#include "GameObjectsEnum.h"
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

// TODO: can template this?
static int heuristic(const Vector2D& vector_one, const Vector2D& vector_two) {
    return getDistanceBetweenVectors2D(vector_one, vector_two);
}

/**
 * @brief Algorithm A*
 * @param start is start Node;
 * @param end is end Node;
 * @param grid is game level map;
 * @param find_optimum is means, what's return's path would be a optimal.
 * @return std::vector<Vector2D> path, empty, if grid not allow fint path from start to end;
 */
static std::vector<Vector2D> aStar(Node start, Node end, const Grid& grid, std::vector<GameObjectsEnum> obstacles, bool find_optimum) {
    std::vector<Vector2D> path{};
    std::priority_queue<Node*, std::vector<Node*>, NodeComparator> open_set;
    std::map<int, Node*> all_nodes;

    open_set.push(new Node(start.position_));
    all_nodes[start.position_.getX()*grid.width_ + start.position_.getY()] = &start;

    while(!open_set.empty()) {
        // std::cout << "FROM WHILE" << std::endl;
        Node* current = open_set.top();
        open_set.pop();

        if (current->position_ == end.position_ && find_optimum) {
            // std::cout << "GOOOOOAL" << std::endl;
            while (current != nullptr) {
                // std::cout << "BLEP" << std::endl;
                path.push_back(current->position_);
                current = current->parent;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        std::vector<Vector2D> directions = {upVector, rightVector, downVector, leftVector};
        for (auto dir : directions) {
            // std::cout << "HELLO NEIGHBORS!" << std::endl;
            Vector2D new_vector = current->position_ + dir;
            bool obstacles_complete = true;
            for (GameObjectsEnum obstacle : obstacles) {
                if (grid.map_.at(new_vector) == obstacle) {
                    obstacles_complete = false;
                    //break;
                }
            }
            // grid.map_.at(new_vector) != GameObjectsEnum::WALL && grid.map_.at(new_vector) != GameObjectsEnum::DOOR_TO && grid.map_.at(new_vector) != GameObjectsEnum::DOOR_FROM
            if (new_vector >= zeroVector && new_vector.getX() < grid.width_ && new_vector.getY() < grid.height_ && obstacles_complete) {
                Node* neighbor = new Node(new_vector);
                neighbor->cost_ = current->cost_ + 1;
                neighbor->heuristic_cost_ = heuristic(neighbor->position_, end.position_);

                if (all_nodes.find(new_vector.getX()*grid.width_ + new_vector.getY()) == all_nodes.end() || neighbor->cost_ < all_nodes[new_vector.getX()*grid.width_ + new_vector.getY()]->cost_) {
                    neighbor->parent = current;
                    open_set.push(neighbor);
                    all_nodes[new_vector.getX()*grid.width_ + new_vector.getY()] = neighbor;
                }
            }
        }
        if (!find_optimum) {
            path.push_back(current->position_);
            current = current->parent;
        }
    }
    return path;
}

#endif // A_STAR_H