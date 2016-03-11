#pragma once

#include "mge/behaviours/AbstractBehaviour.hpp"

class BrokenBridgeBehaviour : public AbstractBehaviour
{
public:
	BrokenBridgeBehaviour(GameObject * bridge);
	~BrokenBridgeBehaviour();

	virtual void update(float step);
	virtual void OnCollision(Collision collision);

private:

	GameObject* _bridge;
	bool hit = false;
	float timer = 0.0f;
};

