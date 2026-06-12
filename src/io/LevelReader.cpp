#include "LevelReader.h"

LevelReader::LevelReader() : path_to_file_("") {}

void LevelReader::setPathToFile(const std::string& path) {
    path_to_file_ = path;
}

std::string LevelReader::getPathToFile() const {
    return path_to_file_;
}

bool LevelReader::fileExists() const {
    std::ifstream f(path_to_file_);
    return f.is_open();
}

Map LevelReader::read() {
    if (!fileExists()) {
        std::cout << "The void map (1x1) returned!" << std::endl;
        return Map(1,1);
    }
    std::ifstream file(path_to_file_);
    nlohmann::json j;
    file >> j;
    Map map;
    map.fromJson(j);
    return map;
}