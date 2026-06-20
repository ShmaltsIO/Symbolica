#include "TxtReader.h"

void TxtReader::setPathToFile(const std::string& path) {
    path_to_file_ = path;
}

std::string TxtReader::getPathToFile() const {
    return path_to_file_;
}

bool TxtReader::fileExists() const {
    std::ifstream f(path_to_file_);
    return f.is_open();
}

std::string TxtReader::read() {
    if (!fileExists()) {
        std::cout << "The void string returned!" << std::endl;
        return "";
    }

    std::string content = "";
    std::string line = "";

    std::ifstream in(path_to_file_);

    if (in.is_open())
    {
        while (std::getline(in, line))
        {
            line += "\n";
            content += line;
        }
        content.pop_back();
        
        // Erase the trash at begin (text form problem)
        content.erase(content.begin());
        content.erase(content.begin());
        content.erase(content.begin());
    }
    in.close();

    return content;
}