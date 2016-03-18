#include "CollectableBehaviour.h"
#include "mge/core/GameObject.hpp"
#include "mge/core/collision/BoxTrigger.h"
#include "mge/core/collision/Collision.h"
#include "mge/core/collision/StaticGameObject.h"
#include "SFML\Audio.hpp"
#include "mge/config.hpp"
#include "mge/StatsHolder.h"
#include "mge/core/SoundManager.h"

CollectableBehaviour::CollectableBehaviour(bool key)
{
	hit = false;
	_key = key;
}


CollectableBehaviour::~CollectableBehaviour()
{
	std::cout << " Deleted collectable " << std::endl;
}
sf::SoundBuffer buffer;
sf::Sound sound;

void CollectableBehaviour::update(float pStep) 
{
	_owner->rotate(pStep, glm::vec3(0, 1, 0));
}

void CollectableBehaviour::OnCollision(Collision collision)
{
	//::cout << collision.getHitBy()  << std::endl;
	if (collision.getHitBy()->getName() == "Player" && !hit)
	{
		hit = true;

		std::cout << " Picked up " << std::endl;
		if (_key) {
			SoundManager::getInstance().PlaySound("key");
			SoundManager::getInstance().PlaySound("findkey");
			StatsHolder::addKey();
		}
		else {
			SoundManager::getInstance().PlaySound("coin");
			StatsHolder::increaseScore(1);
		}

		dynamic_cast<StaticGameObject*>(_owner)->deleteStaticObj();
		delete dynamic_cast<StaticGameObject*>(_owner);
	}
}
