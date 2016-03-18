#pragma once
#include "AbstractBehaviour.hpp"

class SceneSwitchBehaviour : public AbstractBehaviour
{
public:
	SceneSwitchBehaviour();
	~SceneSwitchBehaviour();

	virtual void update(float step);
	virtual void OnCollision(Collision collision);

private:
	bool hit;
};

