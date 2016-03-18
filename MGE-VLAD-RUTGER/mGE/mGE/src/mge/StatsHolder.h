#pragma once

#include <glm.hpp>

class StatsHolder
{
public:
	StatsHolder();
	~StatsHolder();

	static void increaseScore(int amount);
	static void addKey();

	static int getScore();
	static int getKeyCount();

	static void setSpawnPos(glm::vec3 pos);
	static glm::vec3 getSpawnPos();

	static bool InPauseMenu;
	static bool PlayerDied;

private:
	static int _score;
	static int _keyCount;

	static glm::vec3 _spawnPos;
};

