#ifndef ENTITY_TYPE_H
#define ENTITY_TYPE_H

enum class EntityType : char {
	PLAYER = 'p',
	COIN = 'i',
	FOOD = 'f',
	ENEMY = 'e',
	BOSS = 'b',
	ARMOR = 'a',
	WEAPON = 'w',
	CHEST = 'c',
	KEY = 'k'
};

#endif // ENTITY_TYPE_H