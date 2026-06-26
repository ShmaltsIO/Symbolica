#ifndef SAVE_PLAYER_WRITER_H
#define SAVE_PLAYER_WRITER_H

#include <string>
#include <fstream>
#include <stdexcept>

#include "JsonSerialization.h"
#include "IWriter.h"
#include "PlayerSaveData.h"

class SavePlayerWriter : public IWriter<const PlayerSaveData&> {
private:
    std::string path_to_file_;

public:
    SavePlayerWriter() = default;
    void setPathToFile(const std::string& path);
    std::string getPathToFile() const;
    void write(const PlayerSaveData& data) override;
};

#endif // SAVE_PLAYER_WRITER_H