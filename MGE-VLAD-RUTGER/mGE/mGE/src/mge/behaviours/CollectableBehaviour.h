#pragma once

#include "mge/behaviours/AbstractBehaviour.hpp"

class CollectableBehaviour : public AbstractBehaviour
{
public:
	CollectableBehaviour(bool key);
	~CollectableBehaviour();
	virtual void update(float step);
	virtual void OnCollision(Collision collision);

private:
	bool _key;
	bool hit;
};

