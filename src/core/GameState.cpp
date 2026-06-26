#include "GameState.h"

unsigned int GameState::getRoomNumber() { return this->room_number; }

void GameState::setRoomNumber(unsigned int room_number) {
	this->room_number = room_number;
}

LevelState GameState::getLevelState() { return this->level_state; }

void GameState::setLevelState(const LevelState& level_state) {
	this->level_state = level_state;
}