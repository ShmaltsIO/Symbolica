// TilemapConfig.h
#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <stdint.h>

class TilemapConfig {
public:
    // Загрузить из файла (полный путь до assets/tilemap.ini)
    bool load(const std::string& filename);

    // Получить путь для символа в указанной секции
    std::string getPath(const std::string& section, uint32_t ch) const;

    // Загрузить все сопоставления из секции и применить в BearLibTerminal
    void applyToTerminal(const std::string& section);

private:
    // Структура: секция -> (код символа -> путь)
    std::unordered_map<std::string, std::unordered_map<uint32_t, std::string>> data_;

    // Вспомогательный парсинг строки вида "0x0058 = high/tileChest.png"
    bool parseLine(const std::string& line, uint32_t& code, std::string& path);
};