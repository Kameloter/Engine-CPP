#pragma once

#include <glm.hpp>
#include "mge/behaviours/AbstractBehaviour.hpp"
#include <SFML/Graphics.hpp>

class SpikeBehaviour : public AbstractBehaviour
{
public:
	SpikeBehaviour();
	~SpikeBehaviour();
	virtual void update(float step);

	void InitializePositions();

private:
	bool forward = false;

	glm::vec3 _openPos;
	glm::vec3 _closedPos;
	glm::vec3 _translateUp;
};

