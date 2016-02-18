#pragma once

#include "mge\core\GameObject.hpp"
#include "tokamak.h"
class PhysicsWorld;
class StaticGameObject : public GameObject
{
public:
	StaticGameObject(std::string pName, glm::vec3 pPosition, PhysicsWorld* pWorld);
	~StaticGameObject();


	void updateStaticBody();

	void AddBoxCollider(float pW, float pH, float pD);
private:
	neAnimatedBody* _animBody;
};