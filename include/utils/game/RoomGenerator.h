#ifndef ROOM_GENERATOR_H
#define ROOM_GENERATOR_H

#include "Node.h"
#include "NodeComparator.h"
#include "Grid.h"
#include "PRNG.h"
#include "LevelWriter.h"

#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <iostream>

#include "aStar.h"
static char getCharacter(int chance) {
    char symbol = '0';

    if (chance == -1) {
        symbol = '1';
    }
    if (0 <= chance && chance <= 40) {
        if (chance % 2 == 0) {
            symbol = '1';
        } else {
            symbol = '0';
        }
    }
    if (75 <= chance && chance <= 95) {
        if (chance % 2 == 0) {
            symbol = 'F';
        } else {
            symbol = 'C';
        }
    }
    if (90 <= chance && chance <= 100) {
        symbol = 'E';
    }
    return symbol;
}

static Grid generateLevelMOD(int width, int height, int level_number) {
    if (width <= 5 || height <= 5 || level_number <= 0) {
        width = 10;
        height = 10;
        level_number = 1;
    }

    Vector2D start_vector(2, 2);
    Vector2D end_vector = Vector2D(width, height) - start_vector;

    Node start(start_vector);
    Node end(end_vector);

    Grid level_map{width, height};

    std::vector<Vector2D> path{};
    std::vector<Vector2D> directions = {upVector, rightVector, downVector, leftVector};
    std::priority_queue<Node*, std::vector<Node*>, NodeComparator> open_set;
    std::map<int, Node*> all_nodes;

    unsigned int seed = width*height;

    open_set.push(new Node(start.position_));
    all_nodes[start.position_.getX()*width + start.position_.getY()] = &start;

    while(!open_set.empty()) {
        Node* current = open_set.top();
        open_set.pop();

        // If we achieve the path from start to end, h.cost = 0 and create path
        // Later this path will be built as ground tiles

        for (auto dir : directions) {
            Vector2D new_vector = current->position_ + dir;

            if (new_vector >= zeroVector && new_vector.getX() < width && new_vector.getY() < height) {
                Node* neighbor = new Node(new_vector);
                neighbor->cost_ = current->cost_ + 1;
                // Check borders positions, if is border, set h. cost = -1
                // else is just simple node
                if (new_vector.getX() == 0 || new_vector.getY() == 0 || new_vector.getX() == width-1 || new_vector.getY() == height-1) {
                    neighbor->heuristic_cost_ = -1;
                } else {
                    seed = getRandomNumber(seed, 100, 0);
                    neighbor->heuristic_cost_ = getRandomNumber(seed, 100, 0);
                }

                if (all_nodes.find(new_vector.getX()*width + new_vector.getY()) == all_nodes.end() || neighbor->cost_ < all_nodes[new_vector.getX()*width + new_vector.getY()]->cost_) {
                    //neighbor->heuristic_cost_ = 0; // create all as ground
                    neighbor->parent = current;
                    open_set.push(neighbor);
                    all_nodes[new_vector.getX()*width + new_vector.getY()] = neighbor;
                }
            }
        }
        seed++;
    }

    // Place our doors and player
    if (level_number > 1) {
        if (level_number % 2 == 0) {
            level_map.map_.emplace(end_vector, 'U');
            level_map.map_.emplace(end_vector + leftVector, 'P');
            level_map.map_.emplace(start_vector, 'D');
        } else {
            level_map.map_.emplace(start_vector, 'U');
            level_map.map_.emplace(start_vector + rightVector, 'P');
            level_map.map_.emplace(end_vector, 'D');
        }
    } else {
        level_map.map_.emplace(end_vector, 'D');
        level_map.map_.emplace(start_vector, 'P');
    }

    // Place other entites
    for (auto& node : all_nodes) {
        level_map.map_.emplace(node.second->position_, getCharacter(node.second->heuristic_cost_));    
    }
    
    // Post-refactor
    // Check the path from start to end and place on path 0, that's guarantees a chance to escape from level
    path = aStar(start, end, level_map, {}, true);
    path.pop_back();
    
    for (auto& vec : path) {
        if (vec != start_vector) {
            level_map.map_[vec] = '0';
        }            
    }
    
    // Save level in file
    LevelWriter lw;
    lw.write(level_map);

    return level_map;
}

#endif // ROOM_GENERATOR_H