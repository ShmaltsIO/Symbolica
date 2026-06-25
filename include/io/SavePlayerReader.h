#ifndef SAVE_PLAYER_READER_H
#define SAVE_PLAYER_READER_H

#include <fstream>
#include <iostream>
#include <string>

#include "IReader.h"
#include "PlayerSaveData.h"
#include "json.hpp"

class SavePlayerReader : public IReader<PlayerSaveData> {
private:
    std::string path_to_file_;

public:
    SavePlayerReader() = default;
    ~SavePlayerReader() = default;

    void setPathToFile(const std::string& path);
    std::string getPathToFile() const;
    bool fileExists() const;
    PlayerSaveData read() override;
};

#endif // SAVE_PLAYER_READER_H