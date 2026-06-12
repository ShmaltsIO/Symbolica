// TilemapConfig.cpp
#include "TilemapConfig.h"
#include <fstream>
#include <sstream>
#include <cctype>
#include "BearLibTerminal.h"

bool TilemapConfig::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    data_.clear();
    std::string line;
    std::string currentSection;

    while (std::getline(file, line)) {
        // Удаляем пробелы в начале и конце
        size_t start = line.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) continue; // пустая строка
        size_t end = line.find_last_not_of(" \t\r\n");
        line = line.substr(start, end - start + 1);

        // Пропускаем комментарии (; или #)
        if (line.empty() || line[0] == ';' || line[0] == '#') continue;

        // Секция: [name]
        if (line.front() == '[' && line.back() == ']') {
            currentSection = line.substr(1, line.size() - 2);
            continue;
        }

        // Парсим запись вида код = путь
        size_t eqPos = line.find('=');
        if (eqPos == std::string::npos) continue;

        std::string codeStr = line.substr(0, eqPos);
        std::string path = line.substr(eqPos + 1);
        // Удаляем пробелы вокруг
        codeStr.erase(0, codeStr.find_first_not_of(" \t"));
        codeStr.erase(codeStr.find_last_not_of(" \t") + 1);
        path.erase(0, path.find_first_not_of(" \t"));
        path.erase(path.find_last_not_of(" \t") + 1);

        uint32_t code;
        if (codeStr.find("0x") == 0 || codeStr.find("0X") == 0) {
            code = std::stoul(codeStr, nullptr, 16);
        } else {
            code = std::stoul(codeStr);
        }

        if (!currentSection.empty()) {
            data_[currentSection][code] = path;
        }
    }
    return true;
}

std::string TilemapConfig::getPath(const std::string& section, uint32_t ch) const {
    auto itSec = data_.find(section);
    if (itSec != data_.end()) {
        auto itCh = itSec->second.find(ch);
        if (itCh != itSec->second.end()) {
            return itCh->second;
        }
    }
    return "";
}

void TilemapConfig::applyToTerminal(const std::string& section) {
    auto itSec = data_.find(section);
    if (itSec == data_.end()) return;

    for (const auto& pair : itSec->second) {
        uint32_t code = pair.first;
        const std::string& path = pair.second;
        // Формируем команду для BearLibTerminal: "0x0058: assets/high/tileChest.png"
        // Путь должен быть относительно рабочей директории, поэтому если в .ini у тебя "high/tileChest.png",
        // а assets скопирована в папку сборки, то полный относительный путь будет "assets/high/tileChest.png"
        std::string cmd = "0x" + std::to_string(code) + ": assets/" + path;
        terminal_set(cmd.c_str());
    }
}