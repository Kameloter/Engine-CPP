#include "PressurePlateBehaviour.h"

#include <glm.hpp>
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>

#include "mge/core/collision/BoxTrigger.h"
#include "mge/core/collision/Collision.h"

PressurePlateBehaviour::PressurePlateBehaviour()
{	
	hit = false;
}

PressurePlateBehaviour::~PressurePlateBehaviour()
{
}

void PressurePlateBehaviour::update(float pStep) {
}

void PressurePlateBehaviour::SetStatue(GameObject * pStatue) {
	_statue = pStatue;
}

void PressurePlateBehaviour::OnCollision(Collision collision)
{
	//std::cout << collision.getHitBy() << std::endl;

	if (collision.getHitBy() == _statue->getName() && !hit)
	{
		_activated = true;
		hit = true;
	}
}

