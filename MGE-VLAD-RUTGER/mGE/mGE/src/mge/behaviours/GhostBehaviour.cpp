#include "GhostBehaviour.h"

#include <glm.hpp>
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>
#include "mge\core\collision/StaticGameObject.h"
#include "mge/core/collision/BoxTrigger.h"
#include "mge/core/collision/Collision.h"
#include "mge/StatsHolder.h"


GhostBehaviour::GhostBehaviour()
{

}


GhostBehaviour::~GhostBehaviour()
{
}

void GhostBehaviour::update(float pStep)
{

	if (forward) {


		if (glm::distance(_owner->getWorldPosition(), _openPos) > 0.5f) {
			dynamic_cast<StaticGameObject*>(_owner)->moveTriggerObject(glm::normalize(_openPos - _closedPos) * pStep * 5);
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
			dynamic_cast<StaticGameObject*>(_owner)->moveTriggerObject(-glm::normalize(_openPos - _closedPos) * pStep * 5);
		}
		else
		{
			forward = true;
		}
	}
}

void GhostBehaviour::InitializePositions()
{
	_closedPos = _owner->getLocalPosition();
	_openPos = _owner->getLocalPosition() + glm::vec3(0, 3, 0);
}

void GhostBehaviour::OnCollision(Collision collision)
{
	if (collision.getHitBy()->getName() == "Player" && !hit)
	{
		StatsHolder::PlayerDied = true;
		hit = true;
	}
}

void GhostBehaviour::setBeginEnd(glm::vec3 begin, glm::vec3 end) {
	_openPos = begin;
	_closedPos = end;
}
