#ifndef ITEM_DATA_H
#define ITEM_DATA_H

#include <string>

#include "ItemStats.h"

class ItemData {
public:
	std::string prefabId;
	unsigned int count;
	ItemStats stats;
};

#endif // ITEM_DATA_H
