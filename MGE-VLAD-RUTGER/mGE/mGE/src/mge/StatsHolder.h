#pragma once
class StatsHolder
{
public:
	StatsHolder();
	~StatsHolder();

	static void increaseScore(int amount);
	static void addKey();

	static int getScore();
	static int getKeyCount();


	static bool PlayerDied;

private:
	static int _score;
	static int _keyCount;
	
};

