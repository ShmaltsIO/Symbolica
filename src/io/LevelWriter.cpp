#include "LevelWriter.h"

LevelWriter::LevelWriter() : path_to_file_("") {}

void LevelWriter::setPathToFile(const std::string& path) {
    path_to_file_ = path;
}

std::string LevelWriter::getPathToFile() const {
    return path_to_file_;
}

void LevelWriter::write(const Map& map) {
    std::ofstream file(path_to_file_);
    if (!file.is_open()) return;
    nlohmann::json j = map.toJson();
    file << j.dump(2);
}