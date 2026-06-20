#ifndef GAME_STATISTICS_H
#define GAME_STATISTICS_H

class GameStatistics
{
private:
	unsigned int enemies_beaten = 0;
	unsigned int steps_completed = 0;
	unsigned int money_collected = 0;
	unsigned int score = 0;

public:
	GameStatistics() = default;
	GameStatistics(unsigned int enemies_beaten, unsigned int steps_completed, unsigned int money_collected) : 
		enemies_beaten(enemies_beaten), 
		steps_completed(steps_completed),
		money_collected(money_collected) {}

	~GameStatistics() = default;

	unsigned int getEnemiesBeaten();
	unsigned int getStepsCompleted();
	unsigned int getMoneyCollected();
	unsigned int getScore();

	void setEnemiesBeaten(unsigned int enemies_beaten);
	void setStepsCompleted(unsigned int steps_completed);
	void setMoneyCollected(unsigned int money_collected);
	void setScore(unsigned int score);
};

#endif // GAME_STATISTICS_H