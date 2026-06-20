#ifndef TXT_READER_H
#define TXT_READER_H

#include <fstream>
#include <iostream>
#include <string>

#include "IReader.h"

class TxtReader : public IReader<std::string> {
private:
    std::string path_to_file_;

public:
    TxtReader() = default;
    TxtReader(const std::string& path) : path_to_file_(path) {}
    
    ~TxtReader() = default;

    void setPathToFile(const std::string& path);
    std::string getPathToFile() const;
    bool fileExists() const;
    std::string read() override;
};

#endif // TXT_READER_H