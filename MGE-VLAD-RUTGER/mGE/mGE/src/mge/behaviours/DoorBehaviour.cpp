#include "DoorBehaviour.h"

#include <glm.hpp>
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>
#include "mge/behaviours/PressurePlateBehaviour.h"
#include "mge\core\collision\RigidbodyGameObject.h"

DoorBehaviour::DoorBehaviour()
{
    _activated = false;
}

DoorBehaviour::~DoorBehaviour()
{
    //dtor
}

void DoorBehaviour::update(float pStep){
	if (CheckPlates()) {
		if (glm::distance(_owner->getWorldPosition(), _openPos)>0.25f) {
			dynamic_cast<RigidbodyGameObject*>(_owner)->moveRb(glm::normalize(_openPos - _closedPos));
		}
	}
}

void DoorBehaviour::AddPressurePlate(GameObject * plate)
{
	plates.push_back(plate);
}

void DoorBehaviour::InitializePositions(glm::vec3 translateUp)
{
	_closedPos = _owner->getLocalPosition();
	_openPos = _owner->getLocalPosition() + glm::vec3(0, 3, 0);
}

bool DoorBehaviour::CheckPlates()
{
	int count = 0;
	for (int i = 0; i<plates.size(); i++) {
		if (dynamic_cast<PressurePlateBehaviour*>( plates[i]->getBehaviour())->_activated) {
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

void DoorBehaviour::SetOpenPos(glm::vec3 translateUp){
    _openPos = _owner->getLocalPosition() + translateUp;
}
