#include "DeathBehaviour.h"
#include "mge/core/collision/BoxTrigger.h"
#include "mge/core/collision/Collision.h"
#include "mge/core/collision/StaticGameObject.h"
#include "mge/StatsHolder.h"
#include "mge/SubtitleManager.h"


DeathBehaviour::DeathBehaviour()
{
}


DeathBehaviour::~DeathBehaviour()
{
}

void DeathBehaviour::update(float pStep)
{
	//std::cout << dynamic_cast<StaticGameObject*>(_owner)->getTrigger()->getMaxBounds() << std::endl;
	if (dynamic_cast<StaticGameObject*>(_owner)->getTrigger()->collisionInfo->OnTriggerEnter("Player"))
	{
		std::cout << " PLAYER DIIIIED " << std::endl;
		StatsHolder::PlayerDied = true;
	}
}
