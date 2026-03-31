#ifndef LEVEL_READER_H
#define LEVEL_READER_H

#include "IReader.h"
#include "Grid.h"
#include <string>

/**
 * @brief Class for reading game levels from special files.
 */
class LevelReader: public IReader<Grid> {
private:
    std::string path_to_file_;
public:
    LevelReader();

    void setPathToFile(std::string);
    std::string getPathToFile();
    std::string getPathToFile() const;
    bool checkFileExist();

    Grid read() override;
};

#endif // LEVEL_READER_H