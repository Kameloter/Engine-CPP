#pragma once
class StatsHolder
{
public:
	StatsHolder();
	~StatsHolder();

	static void increaseScore(int amount);
	static int getScore();


private:
	static int _score;
};

