#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "LevelState.h"

class GameState {
private:
	unsigned int room_number = 1;
	LevelState level_state;

public:
	GameState() = default;
	GameState(unsigned int room_number) : room_number(room_number) {}

	~GameState() = default;

	unsigned int getRoomNumber();
	LevelState getLevelState();

	void setRoomNumber(unsigned int room_number);
	void setLevelState(const LevelState&);
};

#endif // !GAME_STATE_H
