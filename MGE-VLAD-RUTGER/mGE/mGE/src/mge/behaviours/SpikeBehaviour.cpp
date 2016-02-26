#include "SpikeBehaviour.h"

#include <glm.hpp>
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>
#include "mge/behaviours/PressurePlateBehaviour.h"
#include "mge\core\collision/StaticGameObject.h"
#include "mge/core/collision/BoxTrigger.h"
#include "mge/core/collision/Collision.h"
#include "mge/StatsHolder.h"

SpikeBehaviour::SpikeBehaviour()
{
}


SpikeBehaviour::~SpikeBehaviour()
{
}

void SpikeBehaviour::update(float pStep) {

	if (forward) {
		if (glm::distance(_owner->getWorldPosition(), _openPos) > 0.5f) {
			dynamic_cast<StaticGameObject*>(_owner)->moveTriggerObject(glm::normalize(_openPos - _closedPos) / 25);
		}
		else
		{
			forward = false;
		}
	}
	else
	{
		if (glm::distance(_owner->getWorldPosition(), _closedPos) > 0.5f)
		{
			dynamic_cast<StaticGameObject*>(_owner)->moveTriggerObject(-glm::normalize(_openPos - _closedPos) / 25);
		}
		else
		{
			forward = true;
		}
	}


	if (dynamic_cast<StaticGameObject*>(_owner)->getTrigger()->collisionInfo->OnTriggerEnter("Player"))
	{
		std::cout << " player died " << std::endl;
	}
}

void SpikeBehaviour::InitializePositions()
{
	_closedPos = _owner->getLocalPosition();
	_openPos = _owner->getLocalPosition() + glm::vec3(0, 3, 0);
}

void SpikeBehaviour::SetOpenPos(glm::vec3 translateUp) {
	_openPos = _owner->getLocalPosition() + translateUp;
}

