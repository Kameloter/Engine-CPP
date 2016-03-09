#include "PushBlockBehaviour.h"
#include <glm.hpp>
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>
#include "mge/behaviours/PressurePlateBehaviour.h"
#include "mge\core\collision/StaticGameObject.h"



PushBlockBehaviour::PushBlockBehaviour()
{
}


PushBlockBehaviour::~PushBlockBehaviour()
{
}

void PushBlockBehaviour::update(float pStep) {
	if (forward) {
		if (glm::distance(_owner->getWorldPosition(), _openPos) > 0.5f) {
			dynamic_cast<StaticGameObject*>(_owner)->moveStaticObject(( glm::normalize(_openPos - _closedPos))* pStep * 15);
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
			dynamic_cast<StaticGameObject*>(_owner)->moveStaticObject(-glm::normalize(_openPos - _closedPos) * pStep * 2 );
		}
		else
		{
			forward = true;
		}
	}

}

void PushBlockBehaviour::InitializePositions()
{
	_closedPos = _owner->getLocalPosition();
	_openPos = _owner->getLocalPosition() + glm::vec3(0, 3, 0);
}

bool PushBlockBehaviour::CheckPlates()
{
	int count = 0;
	for (int i = 0; i<plates.size(); i++) {
		if (dynamic_cast<PressurePlateBehaviour*>(plates[i]->getBehaviour())->_activated) {
			count++;
		}
	}

	if (count == plates.size()) {
		return true;
	}
	else
	{
		return false;
	}
}


 //LUA
void PushBlockBehaviour::SetOpenPos(glm::vec3 translateUp) {
	_openPos = _owner->getLocalPosition() + translateUp;
}

void PushBlockBehaviour::AddPressurePlate(GameObject * plate)
{
	plates.push_back(plate);
}
