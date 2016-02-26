#include "CollectableBehaviour.h"
#include "mge/core/GameObject.hpp"
#include "mge/core/collision/BoxTrigger.h"
#include "mge/core/collision/Collision.h"
#include "mge/core/collision/StaticGameObject.h"
#include "mge/StatsHolder.h"
CollectableBehaviour::CollectableBehaviour()
{
}


CollectableBehaviour::~CollectableBehaviour()
{
	std::cout << " Deleted collectable " << std::endl;
}

void CollectableBehaviour::update(float pStep) 
{
	//std::cout << dynamic_cast<StaticGameObject*>(_owner)->getTrigger()->getMaxBounds() << std::endl;
	 if (dynamic_cast<StaticGameObject*>(_owner)->getTrigger()->collisionInfo->OnTriggerEnter("Player"))
	{
		std::cout << " Picked up " << std::endl;
		StatsHolder::increaseScore(1);
		delete dynamic_cast<StaticGameObject*>(_owner);
	}
}


