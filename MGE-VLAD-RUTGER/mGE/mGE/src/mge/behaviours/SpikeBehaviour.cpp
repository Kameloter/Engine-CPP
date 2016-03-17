#include "SpikeBehaviour.h"

#include <glm.hpp>
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>
#include "mge/behaviours/PressurePlateBehaviour.h"
#include "mge\core\collision/StaticGameObject.h"
#include "mge/core/collision/RigidbodyGameObject.h"
#include "mge/core/collision/BoxTrigger.h"
#include "mge/core/collision/Collision.h"
#include "mge/StatsHolder.h"


SpikeBehaviour::SpikeBehaviour(bool once)
{
	hit = false;
	_once = once;
}


SpikeBehaviour::~SpikeBehaviour()
{
}

void SpikeBehaviour::update(float pStep) {
	if (!_once) {
		if (forward) {
			if (glm::distance(_owner->getWorldPosition(), _openPos) > 0.5f) {
				dynamic_cast<StaticGameObject*>(_owner)->moveTriggerObject(glm::normalize(_openPos - _closedPos) * pStep * 2);
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
				dynamic_cast<StaticGameObject*>(_owner)->moveTriggerObject(-glm::normalize(_openPos - _closedPos) * 2 * pStep);
			}
			else
			{
				forward = true;
			}
		}
	}
	else
	{
		if (_activated) {
		//	std::cout << "im here" << std::endl;
			if (forward) {
			//	std::cout << "now im here" << std::endl;
				if (glm::distance(_owner->getWorldPosition(), _openPos) > 0.5f) {
				//	std::cout << "and now im here" << std::endl;
					dynamic_cast<StaticGameObject*>(_owner)->moveTriggerObject(glm::normalize(_openPos - _closedPos) * pStep * 5);
				}
				else
				{
					forward = false;
					finish = true;
				}
			}
			else
			{
				if (glm::distance(_owner->getWorldPosition(), _closedPos) > 0.5f)
				{
					dynamic_cast<StaticGameObject*>(_owner)->moveTriggerObject(-glm::normalize(_openPos - _closedPos) * 2 * pStep);
				}
				else
				{
					forward = true;
					if (finish) _activated = false;
				}
			}
		}
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

void SpikeBehaviour::OnCollision(Collision collision)
{
	//std::cout << collision.getHitBy() << std::endl;

	if (collision.getHitBy()->getName() == "Player" && !hit)
	{
		glm::vec3 spawnPos = StatsHolder::getSpawnPos();
		neV3 Pos;
		Pos.Set(spawnPos.x, spawnPos.y - 4.5f, spawnPos.z);

		neV3 vel;
		vel.Set(0, 0, 0);

		dynamic_cast<RigidbodyGameObject*>(collision.getHitBy())->GetRigidBody()->SetPos(Pos);
		dynamic_cast<RigidbodyGameObject*>(collision.getHitBy())->GetRigidBody()->SetVelocity(vel);
	}
}

