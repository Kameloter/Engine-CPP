#include "SubtitleBehaviour.h"
#include "mge/core/collision/BoxTrigger.h"
#include "mge/core/collision/Collision.h"
#include "mge/core/collision/StaticGameObject.h"
#include "mge/SubtitleManager.h"

SubtitleBehaviour::SubtitleBehaviour()
{

}


SubtitleBehaviour::~SubtitleBehaviour()
{
}

void SubtitleBehaviour::update(float pStep)
{
	std::cout << " Up date " << std::endl;
 	//std::cout << dynamic_cast<StaticGameObject*>(_owner)->getTrigger()->getMaxBounds() << std::endl;
	if (dynamic_cast<StaticGameObject*>(_owner)->getTrigger()->collisionInfo->OnTriggerEnter("Player"))
	{
		std::cout << " Playing subtitle on object  " << _owner->getName() <<  std::endl;
		SubtitleManager::playSubtitle(_owner->getName(),5.0f);
		delete dynamic_cast<StaticGameObject*>(_owner);
	}
}
