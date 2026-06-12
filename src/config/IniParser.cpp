#include "IniParser.h"
#include "ini.h"
#include <iostream>
#include <cctype>
#include <algorithm>

static int iniHandler(void* user, const char* section, const char* name, const char* value) {
    auto* parser = static_cast<IniParser*>(user);
    // Можно сохранить в любом виде, например, в map с ключом "section/name"
    // но проще вызвать метод parser->addValue(section, name, value)
    // Сделаем прямо здесь через временный объект? Упростим: запишем в переданный map.
    // Но нам нужен доступ к values_ парсера. Передадим указатель на map.
    static_cast<std::unordered_map<std::string, std::string>*>(user)->emplace(
        std::string(section) + "/" + name, value
    );
    return 1;
}

bool IniParser::load(const std::string& filename) {
    values_.clear();
    int error = ini_parse(filename.c_str(), iniHandler, &values_);
    if (error < 0) {
        std::cerr << "Cannot open/read " << filename << std::endl;
        return false;
    } else if (error > 0) {
        std::cerr << "Parse error on line " << error << " in " << filename << std::endl;
        return false;
    }
    return true;
}

std::string IniParser::makeKey(const std::string& section, const std::string& key) {
    return section + "/" + key;
}

std::optional<std::string> IniParser::get(const std::string& section, const std::string& key) const {
    auto it = values_.find(makeKey(section, key));
    if (it != values_.end()) return it->second;
    return std::nullopt;
}

std::string IniParser::getString(const std::string& section, const std::string& key, const std::string& defaultValue) const {
    auto val = get(section, key);
    return val.has_value() ? *val : defaultValue;
}

int IniParser::getInt(const std::string& section, const std::string& key, int defaultValue) const {
    auto val = get(section, key);
    if (!val.has_value()) return defaultValue;
    try {
        return std::stoi(*val);
    } catch (...) {
        return defaultValue;
    }
}

bool IniParser::getBool(const std::string& section, const std::string& key, bool defaultValue) const {
    auto val = get(section, key);
    if (!val.has_value()) return defaultValue;
    std::string v = *val;
    std::transform(v.begin(), v.end(), v.begin(), ::tolower);
    return (v == "true" || v == "1" || v == "yes" || v == "on");
}