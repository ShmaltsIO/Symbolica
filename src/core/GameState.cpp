#include "GameState.h"

unsigned int GameState::getRoomNumber() { return this->room_number; }

void GameState::setRoomNumber(unsigned int room_number) {
	this->room_number = room_number;
}

LevelState GameState::getLevelState() { return this->level_state; }

void GameState::setLevelState(const LevelState& level_state) {
	this->level_state = level_state;
}

const LevelState& GameState::getLevelState() const {
	return level_state;
}

Map* GameState::getCurrentMap() const {
	return current_map_.get();
}

void GameState::setCurrentMap(std::unique_ptr<Map> map) {
	current_map_ = std::move(map);
}

Entity* GameState::getPlayer() {
	return player;
}

Entity* GameState::getPlayer() const {
	return player;
}

void GameState::setPlayer(Entity* player) {
	this->player = player;
}

Entity* GameState::getObserver() {
	return observer;
}

void GameState::setObserver(Entity* observer) {
	this->observer = observer;
}
