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
	
}

void SubtitleBehaviour::OnCollision(Collision collision)
{
	//::cout << collision.getHitBy()  << std::endl;
	if (collision.getHitBy()->getName() == "Player" && !hit)
	{
		hit = true;
		std::cout << " Hitting playerr :) " << std::endl;
		std::cout << " Playing subtitle on object  " << _owner->getName() << std::endl;
		SubtitleManager::playSubtitle(_owner->getName(), 6.0f);
		delete dynamic_cast<StaticGameObject*>(_owner);
	}
}
