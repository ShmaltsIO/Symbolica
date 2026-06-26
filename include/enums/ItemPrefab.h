#ifndef ITEM_PREFAB_H
#define ITEM_PREFAB_H

#include <string>
#include <unordered_map>

class ItemPrefab {
public:
    std::string id;
    std::string name;
    std::string description;
    unsigned int worth;
    unsigned int base_heal;
    unsigned int base_damage;
    unsigned int base_protection;

    //char symbol;
    //std::string color;
};

#endif // ITEM_PREFAB_H
