#include "StatsHolder.h"


int StatsHolder::_score;
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