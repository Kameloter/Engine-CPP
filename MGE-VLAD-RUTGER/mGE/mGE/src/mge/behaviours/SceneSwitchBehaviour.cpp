#include "SceneSwitchBehaviour.h"
#include "mge/core/collision/BoxTrigger.h"
#include "mge/core/collision/Collision.h"
#include "mge/core/collision/StaticGameObject.h"
#include "mge/core/LevelManager.h"



SceneSwitchBehaviour::SceneSwitchBehaviour()
{
	hit = false;
}


SceneSwitchBehaviour::~SceneSwitchBehaviour()
{
}

void SceneSwitchBehaviour::update(float pStep)
{

}

void SceneSwitchBehaviour::OnCollision(Collision collision)
{
	if (collision.getHitBy()->getName() == "Player" && !hit)
	{
		std::cout << "WHAHHAH" << std::endl;
		hit = true;

		string ownerName = _owner->getName();

		if (ownerName == "level_hub") {
			LevelManager::getInstance().SwitchToLevel(GameLevels::HUB);
		} else if (ownerName == "level_01") {
			LevelManager::getInstance().SwitchToLevel(GameLevels::Level1);
		} else if (ownerName == "level_02") {
			LevelManager::getInstance().SwitchToLevel(GameLevels::Level2);
		} else if (ownerName == "level_03") {
			LevelManager::getInstance().SwitchToLevel(GameLevels::Level3);
		} else if (ownerName == "level_04") {
			LevelManager::getInstance().SwitchToLevel(GameLevels::Level4);
		}
	}
}
