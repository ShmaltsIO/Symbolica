#ifndef SETTINGS_PARSER_H
#define SETTINGS_PARSER_H
#include <string>
#include <unordered_map>
#include <optional>

class IniParser {
public:
    bool load(const std::string& filename);
    
    // Получить значение из секции
    std::optional<std::string> get(const std::string& section, const std::string& key) const;
    
    // Удобные обёртки
    std::string getString(const std::string& section, const std::string& key, const std::string& defaultValue = "") const;
    int getInt(const std::string& section, const std::string& key, int defaultValue = 0) const;
    bool getBool(const std::string& section, const std::string& key, bool defaultValue = false) const;

private:
    std::unordered_map<std::string, std::string> values_;  // ключ = "section/key"
    static std::string makeKey(const std::string& section, const std::string& key);
};

#endif // SETTINGS_PARSER_H