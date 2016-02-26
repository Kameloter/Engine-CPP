#pragma once
#include <glm.hpp>
#include "mge/behaviours/AbstractBehaviour.hpp"
#include <SFML/Graphics.hpp>
class PushBlockBehaviour : public AbstractBehaviour
{
public:
	PushBlockBehaviour();
	~PushBlockBehaviour();
	virtual void update(float step);
	void SetOpenPos(glm::vec3 translateUp);
	void AddPressurePlate(GameObject * plate);
	void InitializePositions();

private:
	std::vector<GameObject*> plates;
	bool CheckPlates();

	bool forward = false;

	glm::vec3 _openPos;
	glm::vec3 _closedPos;
	glm::vec3 _translateUp;
};

