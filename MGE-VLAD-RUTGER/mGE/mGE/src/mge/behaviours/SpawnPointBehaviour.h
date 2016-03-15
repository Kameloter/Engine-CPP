#pragma once

#include "mge/behaviours/AbstractBehaviour.hpp"


class SpawnPointBehaviour : public AbstractBehaviour
{
public:
	SpawnPointBehaviour();
	~SpawnPointBehaviour();

	virtual void update(float step);
	virtual void OnCollision(Collision collision);

private:
	bool hit = false;
};