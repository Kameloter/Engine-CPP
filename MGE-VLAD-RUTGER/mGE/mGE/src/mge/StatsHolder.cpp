#include "StatsHolder.h"


int StatsHolder::_score;
bool StatsHolder::PlayerDied = false;
int StatsHolder::_keyCount = 0;

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
