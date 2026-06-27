#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <memory>

#include "LevelState.h"
#include "Map.h"

class GameState {
private:
	unsigned int room_number = 1;
	LevelState level_state;
	std::unique_ptr<Map> current_map_;

public:
	GameState() = default;
	GameState(unsigned int room_number) : room_number(room_number) {}

	~GameState() = default;

	unsigned int getRoomNumber();
	void setRoomNumber(unsigned int room_number);

	LevelState getLevelState();
	const LevelState& getLevelState() const;
	void setLevelState(const LevelState&);

	Map* getCurrentMap() const;
	void setCurrentMap(std::unique_ptr<Map> map);
};

#endif // GAME_STATE_H
