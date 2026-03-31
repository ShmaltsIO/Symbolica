#include "LevelWriter.h"
#include <fstream>
#include <iostream>
LevelWriter::LevelWriter(): path_to_file_("") {}

void LevelWriter::setPathToFile(std::string path) {
    path_to_file_ = path;
}

std::string LevelWriter::getPathToFile() {
    return path_to_file_;
}

std::string LevelWriter::getPathToFile() const {
    return path_to_file_;
}

void LevelWriter::write(Grid& level_map) {
    int x = 1;
    int y = 1;
    char symbol = ' ';
    auto map = level_map.map_;
    // TODO: why absolute pathes??? -IDK
    //std::cout << "BOMBOM: " << level_map.level_number_ << std::endl;
    std::string file_name = "/home/lesnoy-elf/Документы/cProjects/shmalts.edgar-game/src/symbolica/levels/room" + std::to_string(level_map.level_number_) + ".txt";
    std::ofstream out (file_name);
    if (out.is_open()) {
        out.clear();
        while(y != level_map.height_) {
            symbol = map.find(Vector2D(x, y))->second;

            out << symbol;
            x++;

            if (x == level_map.width_) {
                x = 1;
                y++;
                out << 't' << '\n';
            }
        }
        out.close();
    } else {
        // ERROR
        // std::cerr << "File can't be opened" << std::endl;
    }
    
}
