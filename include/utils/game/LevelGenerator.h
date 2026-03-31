#ifndef LEVEL_GENERATOR_H
#define LEVEL_GENERATOR_H

#include "Node.h"
#include "NodeComparator.h"
#include "Grid.h"
#include "PRNG.h"
#include "LevelWriter.h"

#include <vector>
#include <map>
#include <queue>
#include <iostream>

#include <fstream>

// TODO: maybe it can be a more better?
// Chest - 1%, wall/ground - 70%, Food/Coin - 20%, Enemy - 9%
static char getCharacter(unsigned int chance) {
    char symbol = '0';

    // if (0 == chance) {
    //     symbol = 'X';
    // }
    if (0 <= chance && chance <= 30) {
        if (chance % 2 == 0) {
            symbol = '1';
        } else {
            symbol = '0';
        }
    }
    if (85 <= chance && chance <= 95) {
        if (chance % 2 == 0) {
            symbol = 'F';
        } else {
            symbol = 'C';
        }
    }
    if (99 <= chance && chance <= 100) {
        symbol = 'E';
    }
    return symbol;
}

static std::vector<Vector2D> generateLevel(Node start, Node end, const Grid& grid) {
    int i = 0;
    std::vector<Vector2D> path{};
    std::priority_queue<Node*, std::vector<Node*>, NodeComparator> open_set;
    std::map<int, Node*> all_nodes;
    unsigned int seed = abs(start.position_.getX() + start.position_.getY()) + grid.level_number_;
    std::vector<Vector2D> sentorio{};
    open_set.push(new Node(start.position_));
    all_nodes[start.position_.getX()*grid.width_ + start.position_.getY()] = &start;

    while(!open_set.empty()) {
        // std::cout << "FROM WHILE" << std::endl;
        Node* current = open_set.top();
        open_set.pop();
        // Node curmane = current;
        // std::cout << "CURRENT: " << current->position_ << std::endl;
        // std::cout << "CURMANE: " << curmane.position_ << std::endl;

        std::vector<Vector2D> directions = {upVector, rightVector, downVector, leftVector};
        for (auto dir : directions) {
            // std::cout << "HELLO NEIGHBORS!" << std::endl;
            Vector2D new_vector = current->position_ + dir;

            if (new_vector >= zeroVector && new_vector.getX() < grid.width_ && new_vector.getY() < grid.height_) {
                Node* neighbor = new Node(new_vector);
                neighbor->cost_ = current->cost_ + 1;
                seed = getRandomNumber(seed, 100, 0);
                neighbor->heuristic_cost_ = getRandomNumber(seed, 100, 0);

                if (all_nodes.find(new_vector.getX()*grid.width_ + new_vector.getY()) == all_nodes.end() || neighbor->cost_ < all_nodes[new_vector.getX()*grid.width_ + new_vector.getY()]->cost_) {
                    //neighbor->heuristic_cost_ = 0; // create all as ground
                    neighbor->parent = current;
                    open_set.push(neighbor);
                    all_nodes[new_vector.getX()*grid.width_ + new_vector.getY()] = neighbor;
                }
            } else {
                i++;
                //std::cout << "ELSE: " << new_vector << " AND: " << i << std::endl;
                sentorio.push_back(new_vector);
            }
        }
        
        path.push_back(current->position_);
        current = current->parent;
        //std::cout << "CURRENT: " << current->position_ << std::endl;
        //std::cout << "CURMANE: " << curmane.position_ << std::endl;
        seed++;
    }
    // std::cout << "Shin: " << sentorio.size() << std::endl;
    // int counter = 0;
    // std::ofstream outer("PUMPA.txt");
    // for (auto& v : sentorio) {
    //     if (v.getX() >= 0 && v.getY() >= 0){
    //     outer << v << "\n";
    //     counter++;}
    //     if (v == zeroVector) {
    //         std::cout << "ZERO" << std::endl;
    //         break;
    //     }
    // }
    // outer.close();
    //std::cout<< "COUNTER: " << counter << std::endl;
    Grid grid_ = grid;
    int count = 0;
    //std::cout << "ALL NODES SIZE: " << all_nodes.size() << std::endl;
    //std::cout << "LEVeLELELEL: " << grid_.level_number_ << std::endl;
    grid_.map_.clear();

    // Spawn player and doors.
    // TODO: sequence of door is very important 
    if (grid_.level_number_ > 1) {
        if (grid_.level_number_ % 2 == 0) {
            grid_.map_.emplace(end.position_, 'U');
            grid_.map_.emplace(end.position_ + leftVector, 'P');
            grid_.map_.emplace(start.position_+onesVector, 'D');
        } else {
            grid_.map_.emplace(start.position_, 'U');
            grid_.map_.emplace(start.position_ + rightVector, 'P');
            grid_.map_.emplace(end.position_ + onesVector, 'D');
        }
    } else {
        grid_.map_.emplace(end.position_, 'D');
        grid_.map_.emplace(start.position_, 'P');
    }
    //grid_.map_.emplace(Vector2D(start.position_), 'D');
    // grid_.map_.emplace(start.position_ + downVector, 'P');
    // if (grid_.level_number_ > 1) {
    //     grid_.map_.emplace(Vector2D(start.position_), 'U');
    //     //grid_.map_.emplace(Vector2D(grid_.width_-3, grid_.height_-3), 'D'); // !
    // }
    // grid_.map_.emplace(Vector2D(end.position_), 'D');
    //seed++;
    //grid_.map_.emplace(Vector2D(getRandomNumber(seed, grid_.width_+grid_.height_, 2), getRandomNumber(seed, grid_.height_+grid_.width_, 2)), 'D');
    std::ofstream out("Pumpkin.txt");
    for (auto& node : all_nodes) {
        //std::cout << "OBOI: " << all_nodes.size() << std::endl;
        out << node.second->position_ << "\n";
        //std::cout << "Total: " << node.second->heuristic_cost_ << std::endl;
        if (node.second->position_.getX() == 1 || node.second->position_.getX() == grid_.width_-1
            || node.second->position_.getY() == 1 || node.second->position_.getY() == grid_.height_-1) {
                grid_.map_.emplace(node.second->position_, '1');
        } else {
            grid_.map_.emplace(node.second->position_, getCharacter(node.second->heuristic_cost_));
        }

        // For stats
        // if (10 <= costt.second->cost_ && costt.second->cost_ <= 50) {
        //     count++;
        // }
    }
    out.close();
    LevelWriter lw;
    //std::cout << "LEVEL NUMBER: " << grid_.level_number_ << std::endl;
    lw.write(grid_);
    return path;
}

#endif // LEVEL_GENERATOR_H