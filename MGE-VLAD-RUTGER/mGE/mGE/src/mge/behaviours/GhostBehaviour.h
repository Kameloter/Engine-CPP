#pragma once

#include <glm.hpp>
#include "mge/behaviours/AbstractBehaviour.hpp"
#include <SFML/Graphics.hpp>

class GhostBehaviour : public AbstractBehaviour
{
public:
	GhostBehaviour();
	~GhostBehaviour();

	virtual void update(float step);
	virtual void OnCollision(Collision collision);
	void InitializePositions();
	void setBeginEnd(glm::vec3 begin, glm::vec3 end);

private:
	glm::vec3 _openPos;
	glm::vec3 _closedPos;
	bool forward = true;
	bool hit = false;
};

