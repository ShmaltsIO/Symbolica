#include "SavePlayerReader.h"

void SavePlayerReader::setPathToFile(const std::string& path) {
    path_to_file_ = path;
}

std::string SavePlayerReader::getPathToFile() const {
    return path_to_file_;
}

bool SavePlayerReader::fileExists() const {
    std::ifstream f(path_to_file_);
    return f.is_open();
}

PlayerSaveData SavePlayerReader::read() {
    std::ifstream file(path_to_file_);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open save file: " + path_to_file_);
    }
    nlohmann::json j;
    file >> j;
    return j.get<PlayerSaveData>();
}