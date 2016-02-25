#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <mge/core/World.hpp>
#include "tokamak.h"
class StaticGameObject;
class RigidbodyGameObject;
class TriggerManager;
class PhysicsWorld : public World
{
    public:
        PhysicsWorld(int pStaticGameObjectsCount, int pRigidbodyGameObjectsCount);
        virtual ~PhysicsWorld();

		neRigidBody* addRigidBodyObject(RigidbodyGameObject * pRbGameObject);
		neAnimatedBody* addStaticGameObject(StaticGameObject * pStaticGameobject);

		void addStaticTrigger(StaticGameObject * pGameObject);
		void addRbTrigger(RigidbodyGameObject * pGameObject);

		void update(float pStep, const glm::mat4& pParentTransform);

		void freeMemory(neRigidBody* pNeRb);
		void freeMemory(neAnimatedBody* pAnimbody);

		TriggerManager* _triggerManager;

		virtual void CleanUpPhysicsWorld();
    protected:
    private:
		std::vector<RigidbodyGameObject*> _rigidbodyGameObjects;
		std::vector<StaticGameObject*> _staticGameObjects;
		
		neSimulator* _physicsSimulator;
		
};

#endif // PHYSICSMANAGER_H
