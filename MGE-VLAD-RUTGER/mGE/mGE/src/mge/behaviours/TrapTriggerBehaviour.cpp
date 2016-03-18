#include "TrapTriggerBehaviour.h"
#include "mge/core/GameObject.hpp"
#include "mge/core/collision/BoxTrigger.h"
#include "mge/core/collision/Collision.h"
#include "mge/core/collision/StaticGameObject.h"
#include "SFML\Audio.hpp"
#include "mge/config.hpp"
#include "mge/StatsHolder.h"

#include "mge/behaviours/SpikeBehaviour.h"
#include "mge/core/SoundManager.h"


TrapTriggerBehaviour::TrapTriggerBehaviour()
{
}


TrapTriggerBehaviour::~TrapTriggerBehaviour()
{
}

void TrapTriggerBehaviour::update(float pStep)
{
	if (hit && !triggered) {
		timer += pStep;
		if (timer >= 2.0f) {
			dynamic_cast<SpikeBehaviour*>(_trap->getBehaviour())->_activated = true;
			triggered = true;
		}
	}
}

void TrapTriggerBehaviour::OnCollision(Collision collision)
{
	if (collision.getHitBy()->getName() == "Player" && !hit)
	{
		hit = true;
		SoundManager::getInstance().PlaySound("mechclick");
	}
}

void TrapTriggerBehaviour::SetTrap(GameObject * pTrap)
{
	_trap = pTrap;
}
