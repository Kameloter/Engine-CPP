#pragma once

#include "mge\core\GameObject.hpp"
#include "tokamak.h"
class PhysicsWorld;
class RigidbodyGameObject : public GameObject
{
public:
	RigidbodyGameObject(std::string pName,glm::vec3 pPosition, PhysicsWorld* pWorld);
	~RigidbodyGameObject();


	void updateRigidBody();
	void moveRb(glm::vec3 pPos);
	void AddBoxCollider(float pW, float pH, float pD);
	void removeRigidBody();
	void deleteObject();
	neRigidBody * GetRigidBody();

protected:
	neRigidBody* _rigidbody;
private:

	PhysicsWorld*  _world;

};

