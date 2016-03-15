#pragma once
#include "AbstractBehaviour.hpp"
#include "mge/core/collision/RigidbodyGameObject.h"
class DeathBehaviour :
	public AbstractBehaviour
{
public:
	DeathBehaviour();
	~DeathBehaviour();
	virtual void update(float step);
	virtual void OnCollision(Collision collision);

private:
	bool hit;
};

