#include "BrokenBridgeBehaviour.h"
#include "mge/core/GameObject.hpp"
#include "mge/core/collision/BoxTrigger.h"
#include "mge/core/collision/Collision.h"
#include "mge/core/collision/StaticGameObject.h"
#include "SFML\Audio.hpp"
#include "mge/config.hpp"
#include "mge/StatsHolder.h"



BrokenBridgeBehaviour::BrokenBridgeBehaviour(GameObject* bridge)
{
	_bridge = bridge;
}


BrokenBridgeBehaviour::~BrokenBridgeBehaviour()
{
}

void BrokenBridgeBehaviour::update(float pStep)
{
	if (hit) {
		timer += pStep;
		if (timer >= 1.0f && timer < 5.0f) {
			dynamic_cast<StaticGameObject*>(_bridge)->moveStaticObject(glm::vec3(0,-1,0) * pStep * 5);
		}
	}
}

void BrokenBridgeBehaviour::OnCollision(Collision collision)
{
	//::cout << collision.getHitBy()  << std::endl;
	if (collision.getHitBy()->getName() == "Player" && !hit)
	{
		hit = true;
		std::cout << "bridgething" << std::endl;
	}
}
