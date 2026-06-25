#include "SavePlayerReader.h"

void SavePlayerReader::setPathToFile(const std::string& path) {
	path_to_file_ = path;
}

std::string SavePlayerReader::getPathToFile() const {
	return path_to_file_;
}

bool SavePlayerReader::fileExists() const {
	return true;
}

PlayerSaveData SavePlayerReader::read() {
	return PlayerSaveData();
}
