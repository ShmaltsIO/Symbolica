#include "GameStatistics.h"

unsigned int GameStatistics::getEnemiesBeaten() { return this->enemies_beaten; }

unsigned int GameStatistics::getMoneyCollected() { return this->money_collected; }

unsigned int GameStatistics::getStepsCompleted() { return this->steps_completed; }

unsigned int GameStatistics::getScore() { return this->score; }

void GameStatistics::setEnemiesBeaten(unsigned int enemies_beaten) {
	this->enemies_beaten = enemies_beaten;
}

void GameStatistics::setMoneyCollected(unsigned int money_collected) {
	this->money_collected = money_collected;
}

void GameStatistics::setStepsCompleted(unsigned int steps_completed) {
	this->steps_completed = steps_completed;
}

void GameStatistics::setScore(unsigned int score) {
	this->score = score;
}
