#ifndef GAME_STATE_H
#define GAME_STATE_H

class GameState {
private:
	unsigned int room_number = 1;

public:
	GameState() = default;
	GameState(unsigned int room_number) : room_number(room_number) {}

	~GameState() = default;

	unsigned int getRoomNumber();

	void setRoomNumber(unsigned int room_number);
};

#endif // !GAME_STATE_H
