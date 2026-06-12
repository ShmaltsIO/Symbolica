#ifndef LEVEL_READER_H
#define LEVEL_READER_H

#include <fstream>
#include <iostream>
#include <string>

#include "IReader.h"
#include "Map.h"
#include "json.hpp"

class LevelReader : public IReader<Map> {
private:
    std::string path_to_file_;
    
public:
    LevelReader();
    void setPathToFile(const std::string& path);
    std::string getPathToFile() const;
    bool fileExists() const;
    Map read() override;
};

#endif // LEVEL_READER_H