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
			dynamic_cast<StaticGameObject*>(_owner)->moveTriggerObject(glm::normalize(_openPos - _closedPos) * pStep * 3);
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
			dynamic_cast<StaticGameObject*>(_owner)->moveTriggerObject(-glm::normalize(_openPos - _closedPos) * pStep * 2);
		}
		else
		{
			forward = true;
		}
	}
	
	glm::vec3 sine;
	sine = _owner->getWorldPosition();
	sine.y = sin(sine.x) * 5;
	dynamic_cast<StaticGameObject*>(_owner)->moveTriggerObject(glm::normalize(sine) );


}

void GhostBehaviour::InitializePositions()
{
	_closedPos = _owner->getLocalPosition();
	_openPos = _owner->getLocalPosition() + glm::vec3(0, 3, 0);
}

void GhostBehaviour::OnCollision(Collision collision)
{
	if (collision.getHitBy() == "Player" && !hit)
	{
		StatsHolder::PlayerDied = true;
		hit = true;
	}
}

void GhostBehaviour::setBeginEnd(glm::vec3 begin, glm::vec3 end) {
	_openPos = begin;
	_closedPos = end;
}
