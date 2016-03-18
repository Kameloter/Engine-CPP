#pragma once

#include "mge\core\GameObject.hpp"
#include "tokamak.h"
#include  <glm.hpp>

class PhysicsWorld;
class StaticGameObject : public GameObject
{
public:
	StaticGameObject(std::string pName, glm::vec3 pPosition, PhysicsWorld* pWorld, bool trigger = false);
	~StaticGameObject();

	void updateStaticBody();
	void moveStaticObject(glm::vec3 ptranslate);
	void moveTriggerObject(glm::vec3 ptranslate);
	void deleteStaticObj();
	neAnimatedBody * getAnimBody();


	void AddBoxCollider(float pW, float pH, float pD);
private:
	neAnimatedBody* _animBody;
	PhysicsWorld* _world;

};