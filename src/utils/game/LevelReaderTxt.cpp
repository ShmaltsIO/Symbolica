#include "LevelReaderTxt.h"
#include <fstream>
#include <iostream>
LevelReaderTxt::LevelReaderTxt(): path_to_file_("") {}

void LevelReaderTxt::setPathToFile(std::string path) {
    path_to_file_ = path;
    //std::cout << path << std::endl;
}

std::string LevelReaderTxt::getPathToFile() {
    return path_to_file_;
}

std::string LevelReaderTxt::getPathToFile() const {
    return path_to_file_;
}

Grid LevelReaderTxt::read() {
    char symbol = ' ';
    Grid game_map(1, 1);
    int x = 1;
    int y = 1;
    // TODO-SOLVE: That's can be incorrectrly, because we can handle only digits 0-9, and NOT numbers 10-...
    std::string extend_of_file = ".txt";
    std::string filename = "level";

    int size_of_extend_of_file = extend_of_file.length();
    int size_of_filename = filename.length();

    int left_bound = path_to_file_.find(filename);
    int right_bound = path_to_file_.find(extend_of_file);
    
    std::string level = path_to_file_.substr(left_bound+size_of_filename, right_bound-left_bound-size_of_extend_of_file);
    std::cout << "STOI: " << level << std::endl;
    game_map.level_number_ = std::stoi(level);
    std::ifstream in (path_to_file_);

    if (in.is_open()) {
        while(in >> symbol) {
            game_map.map_.emplace(Vector2D(x, y), symbol);
            x++;
            if (symbol == 't') {
                x = 1;
                y++;
            }
        }
        in.close();
    } else {
        // ERROR
        // level = "";
    }
    game_map.width_ = y;
    game_map.height_ = y;

    return game_map;
}

bool LevelReaderTxt::checkFileExist() {
    std::ifstream in (path_to_file_);
    return in.is_open();    
}
