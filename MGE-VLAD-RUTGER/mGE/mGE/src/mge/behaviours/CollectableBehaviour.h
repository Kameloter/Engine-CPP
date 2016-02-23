#pragma once

#include <glm.hpp>
#include "mge/behaviours/AbstractBehaviour.hpp"
#include <SFML/Graphics.hpp>
class CollectableBehaviour : public AbstractBehaviour
{
public:
	CollectableBehaviour();
	~CollectableBehaviour();
	virtual void update(float step);
	void SetPlayer(GameObject * pPlayer);

private:
	GameObject* _player;
};

