#pragma once
#include "AbstractBehaviour.hpp"
class DeathBehaviour :
	public AbstractBehaviour
{
public:
	DeathBehaviour();
	~DeathBehaviour();
	virtual void update(float step);
};

