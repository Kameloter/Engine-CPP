#include "PressurePlateBehaviour.h"

#include <glm.hpp>
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>

PressurePlateBehaviour::PressurePlateBehaviour()
{
	
}


PressurePlateBehaviour::~PressurePlateBehaviour()
{
}

void PressurePlateBehaviour::update(float pStep) {
	if (glm::distance(_owner->getLocalPosition(), _statue->getLocalPosition()) < 1.9f) {
		_activated = true;
	}
	else
	{
		_activated = false;
	}
}

void PressurePlateBehaviour::SetStatue(GameObject * pStatue) {
	_statue = pStatue;
}

