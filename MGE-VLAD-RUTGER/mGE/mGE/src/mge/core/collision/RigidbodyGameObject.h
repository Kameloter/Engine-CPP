#pragma once

#include "mge\core\GameObject.hpp"
#include "tokamak.h"
class PhysicsWorld;
class RigidbodyGameObject : public GameObject
{
public:
	RigidbodyGameObject(std::string pName,glm::vec3 pPosition, PhysicsWorld* pWorld);
	~RigidbodyGameObject();
	void SetBounds(glm::vec3 maxBound, glm::vec3 minBound);
	glm::vec3 GetMinBounds();
	glm::vec3 GetMaxBounds();

	void updateRigidBody();
	void moveRb(glm::vec3 pPos);
	void AddBoxCollider(float pW, float pH, float pD);
	neRigidBody * GetRigidBody();

	bool _moveable = true;
private:
	neRigidBody* _rigidbody;
	PhysicsWorld*  _world;

	glm::vec3 minBounds;
	glm::vec3 maxBounds;

};

