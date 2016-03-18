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


	bool switchToHUB;
	bool switchToLevel1;
	bool switchToLevel2;
	bool switchToLevel3;
	bool switchToLevel4;;
};

