#pragma once

#include "mge/behaviours/AbstractBehaviour.hpp"

class TrapTriggerBehaviour : public AbstractBehaviour
{
public:
	TrapTriggerBehaviour();
	~TrapTriggerBehaviour();

	virtual void update(float step);
	virtual void OnCollision(Collision collision);

	void SetTrap(GameObject * pTrap);

private:
	GameObject* _trap;
	bool hit = false;
	float timer= 0.0f;
	bool triggered = false;
};

