#pragma once

#include <glm.hpp>
#include "mge/behaviours/AbstractBehaviour.hpp"
#include <SFML/Graphics.hpp>

class StatueBehaviour: public AbstractBehaviour
{
public:
	StatueBehaviour();
	~StatueBehaviour();
	virtual void update(float step);
	void SetPlayer(GameObject * pPlayer);
private:
	GameObject * _player;
	bool _isCarried;
	bool _canPress;
};

