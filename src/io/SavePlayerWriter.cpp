#include "SavePlayerWriter.h"

void SavePlayerWriter::setPathToFile(const std::string& path) {
    path_to_file_ = path;
}

std::string SavePlayerWriter::getPathToFile() const {
    return path_to_file_;
}

void SavePlayerWriter::write(const PlayerSaveData& data) {
    nlohmann::json j = data;
    std::ofstream file(path_to_file_);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + path_to_file_);
    }
    file << j.dump(4);
}