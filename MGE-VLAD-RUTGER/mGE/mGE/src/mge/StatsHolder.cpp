#include "StatsHolder.h"


int StatsHolder::_score;
bool StatsHolder::PlayerDied = false;
bool StatsHolder::InPauseMenu = false;
bool StatsHolder::showLoadingScreen = false;
int StatsHolder::_keyCount = 0;
glm::vec3 StatsHolder::_spawnPos = glm::vec3(0,0,0);

StatsHolder::StatsHolder()
{
}


StatsHolder::~StatsHolder()
{
}

void StatsHolder::increaseScore(int amount)
{
	_score += amount;
}

void StatsHolder::addKey()
{
	_keyCount++;
}
int StatsHolder::getScore()
{
	return _score;
}

int StatsHolder::getKeyCount()
{
	return _keyCount;
}

void StatsHolder::setSpawnPos(glm::vec3 pos)
{
	std::cout << pos << std::endl;
	_spawnPos = pos;
}

glm::vec3 StatsHolder::getSpawnPos()
{
	return _spawnPos;
}
