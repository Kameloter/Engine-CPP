#pragma once

#include "mge\core\GameObject.hpp"
#include "tokamak.h"
#include  <glm.hpp>

class PhysicsWorld;
class StaticGameObject : public GameObject
{
public:
	StaticGameObject(std::string pName, glm::vec3 pPosition, PhysicsWorld* pWorld);
	~StaticGameObject();

	void SetBounds(glm::vec3 maxBound, glm::vec3 minBound);
	glm::vec3 GetMinBounds();
	glm::vec3 GetMaxBounds();
	void updateStaticBody();

	void moveStaticObject(glm::vec3 pPos);

	void AddBoxCollider(float pW, float pH, float pD);
private:
	neAnimatedBody* _animBody;
	glm::vec3 minBounds;
	glm::vec3 maxBounds;
};