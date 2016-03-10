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
	void SetOpenPos(glm::vec3 translateUp);
	void InitializePositions();
	virtual void OnCollision(Collision collision);

private:
	bool forward = false;
	bool hit;

	glm::vec3 _openPos;
	glm::vec3 _closedPos;
	glm::vec3 _translateUp;
};

