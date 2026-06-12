#ifndef LEVEL_WRITER_H
#define LEVEL_WRITER_H

#include <string>
#include <fstream>

#include "IWriter.h"
#include "Map.h"

class LevelWriter : public IWriter<const Map&> {
private:
    std::string path_to_file_;
    
public:
    LevelWriter();
    void setPathToFile(const std::string& path);
    std::string getPathToFile() const;
    void write(const Map& map) override;
};

#endif // LEVEL_WRITER_H