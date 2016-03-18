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
private:
	glm::vec3 oldPos = glm::vec3(0,0,0);
	float timer = 0.0f;
};

