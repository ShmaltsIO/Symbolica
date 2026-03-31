#ifndef LEVEL_WRITER_H
#define LEVEL_WRITER_H

#include "IWriter.h"
#include <string>
#include "Grid.h"

/**
 * @brief Class for writing game levels to special files. Implement saves in game.
 */
class LevelWriter: public IWriter<Grid&> {
private:
    std::string path_to_file_;
public:
    LevelWriter();

    void setPathToFile(std::string);
    std::string getPathToFile();
    std::string getPathToFile() const;
    // bool checkFileExist();
    // Why can't put the const Grid& ??? Templates create problems
    void write(Grid&) override;
};

#endif // LEVEL_WRITER_H