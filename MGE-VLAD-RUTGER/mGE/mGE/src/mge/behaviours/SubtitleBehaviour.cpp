#include "SubtitleBehaviour.h"
#include "mge/core/collision/BoxTrigger.h"
#include "mge/core/collision/Collision.h"
#include "mge/core/collision/StaticGameObject.h"
#include "mge/SubtitleManager.h"

SubtitleBehaviour::SubtitleBehaviour()
{
	hit = false;
}


SubtitleBehaviour::~SubtitleBehaviour()
{
}

void SubtitleBehaviour::update(float pStep)
{
	
 	//std::cout << dynamic_cast<StaticGameObject*>(_owner)->getTrigger()->getMaxBounds() << std::endl;
	if (dynamic_cast<StaticGameObject*>(_owner)->getTrigger()->collisionInfo->OnTriggerEnter("Player"))
	{
		
	}
}

void SubtitleBehaviour::OnCollision(Collision collision)
{
	//::cout << collision.getHitBy()  << std::endl;
	if (collision.getHitBy() == "Player" && !hit)
	{
		hit = true;
		std::cout << " Hitting playerr :) " << std::endl;
		std::cout << " Playing subtitle on object  " << _owner->getName() << std::endl;
		SubtitleManager::playSubtitle(_owner->getName(), 6.0f);
		delete dynamic_cast<StaticGameObject*>(_owner);
	}
}
