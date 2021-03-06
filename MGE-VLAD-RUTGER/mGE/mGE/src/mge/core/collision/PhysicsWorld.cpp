#include "PhysicsWorld.h"
#include <algorithm>
#include "mge/core/collision/RigidbodyGameObject.h"
#include "mge/core/collision/StaticGameObject.h"
#include "mge/core/collision/TriggerManager.h"

PhysicsWorld::PhysicsWorld(int pStaticGameObjectsCount, int pRigidbodyGameObjectsCount)
{
	//store needed data for the physics simulator and on creation give the data to it.
	neSimulatorSizeInfo simulatorSize;

	//store it in physics engine type of data.
	s32 rbCount = pRigidbodyGameObjectsCount;
	s32 stCount = pStaticGameObjectsCount;
	
	simulatorSize.rigidBodiesCount = rbCount;
	simulatorSize.animatedBodiesCount = stCount;

	s32 totalCount = rbCount + stCount;
	simulatorSize.geometriesCount = totalCount;

	simulatorSize.overlappedPairsCount = totalCount * (totalCount - 1) / 2;


	//Not used
	simulatorSize.rigidParticleCount = 0;
	simulatorSize.constraintsCount = 0;
	simulatorSize.terrainNodesStartCount = 0;

	//Generate gravity
	neV3 gravity;
	gravity.Set(.0f, -15.0f, .0f);

	//start the physics simulation
	_physicsSimulator = neSimulator::CreateSimulator(simulatorSize, NULL, &gravity);
	_triggerManager = new TriggerManager();

	_physicsSimulator->SetMaterial(0, 2.0f, 0.01f);// index , friction, bounciness
}

//void CollisionCallback(neCollisionInfo & collisionInfo)
//{
//	if (collisionInfo.typeA == NE_RIGID_BODY)
//	{
//		neRigidBody * rbA = (neRigidBody *)collisionInfo.bodyA;
//
//		s32 data = rbA->GetUserData();
//
//		if (data == 0)
//		{
//			return;
//		}
//
//		CRenderPrimitive* render = reinterpret_cast<CRenderPrimitive*>(data);
//		render->SetDiffuseColor(D3DXCOLOR(1.0, 0, 0, 1.0f));
//	}
//	if (collisionInfo.typeB == NE_RIGID_BODY)
//	{
//		neRigidBody * rbB = (neRigidBody *)collisionInfo.bodyB;
//
//		s32 data = rbB->GetUserData();
//
//		if (data == 0)
//		{
//			return;
//		}
//
//		CRenderPrimitive* render = reinterpret_cast<CRenderPrimitive*>(data);
//		render->SetDiffuseColor(D3DXCOLOR(0, 0.5f, 0.5, 1.0f));
//	}
//}

PhysicsWorld::~PhysicsWorld()
{
	delete _triggerManager;
}


void PhysicsWorld::update(float pStep, const glm::mat4& pParentTransform)
{
	World::update(pStep, pParentTransform);
}

void PhysicsWorld::fixedUpdate()
{
	_physicsSimulator->Advance(0.005f);
	if (_triggerManager != NULL) {
		_triggerManager->runPhysics(0.005f);
	}

	for (int i = 0; i < _staticGameObjects.size(); i++)
	{
		_staticGameObjects[i]->updateStaticBody();
	}

	for (int i  = 0; i < _rigidbodyGameObjects.size(); i++)
	{
		_rigidbodyGameObjects[i]->updateRigidBody();
	}
}

void  PhysicsWorld::addStaticTrigger(GameObject * pGameObject)
{
	_triggerManager->addStaticTrigger(pGameObject);
	_staticGameObjects.push_back(dynamic_cast<StaticGameObject*>(pGameObject));
}
void  PhysicsWorld::addMovingTrigger(GameObject * pGameObject)
{
	_triggerManager->addMovingTrigger(pGameObject);

}


neRigidBody* PhysicsWorld::addRigidBodyObject(RigidbodyGameObject * pRbGameObject)
{
	_rigidbodyGameObjects.push_back(pRbGameObject);
	
	return _physicsSimulator->CreateRigidBody();
}

neAnimatedBody* PhysicsWorld::addStaticGameObject(StaticGameObject * pStaticGameobject)
{
	_staticGameObjects.push_back(pStaticGameobject);
	return _physicsSimulator->CreateAnimatedBody();
}

std::vector<RigidbodyGameObject*> PhysicsWorld::getRigidObjects()
{
	return _rigidbodyGameObjects;
}

std::vector<StaticGameObject*> PhysicsWorld::getStaticObjects()
{
	return _staticGameObjects;
}

void PhysicsWorld::CleanUpPhysicsWorld()
{

	World::CleanUpworld();

	_triggerManager->cleanUp();
	_rigidbodyGameObjects.clear();

	_staticGameObjects.clear();
	//DestroyTriggerManager();

	std::cout << " CLEANED OBJECTS " << _staticGameObjects.size() << " <- S  " << _rigidbodyGameObjects.size() << " <- RB " << std::endl;
} 

void PhysicsWorld::cleanStaticObject(GameObject * object)
{
	
	//std::cout << " physics world clean object  ---- "  << object->getName() << std::endl;
	std::cout << " Static obj count "<<_staticGameObjects.size() << std::endl;
	_staticGameObjects.erase(std::remove(_staticGameObjects.begin(), _staticGameObjects.end(), object), _staticGameObjects.end());
	
	std::cout << " count " << _staticGameObjects.size() << std::endl;
	//std::cout << " static objects cleaned  " << object->getName() << std::endl;
	_triggerManager->cleanStaticObject(object);
	//std::cout << " trigger manager  cleaned  " << object->getName() << std::endl;

	World::CleanObjectFromWorld(object);
	
	//GameObject::clearGameObject(dynamic_cast<GameObject*>(object));
	//_triggerManager->cleanObject(object);
	//std::cout << " Cleaning individual physic obbect from list " << std::endl;
	//_staticGameObjects.erase(std::remove(_staticGameObjects.begin(), _staticGameObjects.end(), object),_staticGameObjects.end());
	
}

void PhysicsWorld::cleanMovingObject(GameObject * object)
{
	std::cout << " Moving rb obj count " << _rigidbodyGameObjects.size() << std::endl;
	_rigidbodyGameObjects.erase(std::remove(_rigidbodyGameObjects.begin(), _rigidbodyGameObjects.end(), object), _rigidbodyGameObjects.end());
	std::cout << " Moving rb obj count " << _rigidbodyGameObjects.size() << std::endl;
	//std::cout << " static objects cleaned  " << object->getName() << std::endl;
	_triggerManager->cleanMovingObject(object);
	//std::cout << " trigger manager  cleaned  " << object->getName() << std::endl;

	World::CleanObjectFromWorld(object);
}

void PhysicsWorld::CreateTriggerManager()
{
	_triggerManager = new TriggerManager();
}

void PhysicsWorld::DestroyTriggerManager()
{
	delete _triggerManager;
	_triggerManager = NULL;
}

void PhysicsWorld::freeMemory(neRigidBody* pNeRb)
{
	_physicsSimulator->FreeRigidBody(pNeRb);
//	std::cout << "rb memory freed" << std::endl;
}
void PhysicsWorld::freeMemory(neAnimatedBody* pAnimbody)
{
	_physicsSimulator->FreeAnimatedBody(pAnimbody);
//	std::cout << "sb memory freed" << std::endl;
}