#pragma once
#include "mge/core/collision/RigidbodyGameObject.h"

class Player: public RigidbodyGameObject
{
public:
	Player(std::string pName, glm::vec3 pPosition, PhysicsWorld* pWorld,GameObject* cam);
	~Player();

private:
	GameObject * _cam;
};

