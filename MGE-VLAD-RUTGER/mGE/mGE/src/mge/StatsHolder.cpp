#include "StatsHolder.h"


int StatsHolder::_score;
bool StatsHolder::PlayerDied = false;
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
int StatsHolder::getScore()
{
	return _score;
}