#ifndef LEVEL_WRITER_TXT_H
#define LEVEL_WRITER_TXT_H

#include "IWriter.h"
#include <string>
#include "Grid.h"

/**
 * @brief Class for writing game levels to special files. Implement saves in game.
 */
class LevelWriterTxt: public IWriter<Grid&> {
private:
    std::string path_to_file_;
public:
    LevelWriterTxt();

    void setPathToFile(std::string);
    std::string getPathToFile();
    std::string getPathToFile() const;
    // bool checkFileExist();
    // Why can't put the const Grid& ??? Templates create problems
    void write(Grid&) override;
};

#endif // LEVEL_WRITER_TXT_H