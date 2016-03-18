#include "SceneSwitchBehaviour.h"
#include "mge/core/collision/BoxTrigger.h"
#include "mge/core/collision/Collision.h"
#include "mge/core/collision/StaticGameObject.h"
#include "mge/core/LevelManager.h"



SceneSwitchBehaviour::SceneSwitchBehaviour()
{
	hit = false;
	 switchToHUB = false;
	 switchToLevel1 = false;
	 switchToLevel2 = false;
	 switchToLevel3 = false;
	 switchToLevel4 = false;
}


SceneSwitchBehaviour::~SceneSwitchBehaviour()
{
}

void SceneSwitchBehaviour::update(float pStep)
{
	if (hit)
	{
	
		if (switchToHUB)
		{
			LevelManager::getInstance().SwitchToLevel(GameLevels::HUB);
			switchToHUB = false;
		}
			
		if (switchToLevel1) 
		{
			LevelManager::getInstance().SwitchToLevel(GameLevels::Level1);
			switchToLevel1 = false;
		}

		if (switchToLevel2)
		{
			LevelManager::getInstance().SwitchToLevel(GameLevels::Level2);
			switchToLevel2 = false;
		}

		if (switchToLevel3)
		{
			LevelManager::getInstance().SwitchToLevel(GameLevels::Level3);
			switchToLevel3 = false;
		}

		if (switchToLevel4)
		{
			LevelManager::getInstance().SwitchToLevel(GameLevels::Level4);
			switchToLevel4 = false;
		}

	}
}

void SceneSwitchBehaviour::OnCollision(Collision collision)
{
	if (collision.getHitBy()->getName() == "Player" && !hit)
	{
		std::cout << "WHAHHAH" << std::endl;
		hit = true;

		string ownerName = _owner->getName();

		if (ownerName == "level_hub") {
			switchToHUB = true;
		} else if (ownerName == "level_01") {
			switchToLevel1 = true;
		} else if (ownerName == "level_02") {
			switchToLevel2 = true;
		} else if (ownerName == "level_03") {
			switchToLevel3 = true;
		} else if (ownerName == "level_04") {
			switchToLevel4 = true;
		}
	}
}
