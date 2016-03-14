#pragma once

#include <glm.hpp>
#include "mge/behaviours/AbstractBehaviour.hpp"
#include <SFML/Graphics.hpp>

class PhysicsWorld;

class PressurePlateBehaviour : public AbstractBehaviour
{
public:
	PressurePlateBehaviour(PhysicsWorld * world);
	~PressurePlateBehaviour();
	virtual void update(float step);

	bool _activated = false;

	void SetStatue(GameObject * pStatue);

	virtual void OnCollision(Collision collision);
	
private:
	bool hit;
	GameObject * _statue;
	PhysicsWorld * _world;
};

