#pragma once

#include "mge/behaviours/AbstractBehaviour.hpp"

class CollectableBehaviour : public AbstractBehaviour
{
public:
	CollectableBehaviour();
	~CollectableBehaviour();
	virtual void update(float step);

};

