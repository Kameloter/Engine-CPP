#include "RigidbodyGameObject.h"
#include "mge/core/collision/PhysicsWorld.h"
#include "SFML\Graphics.hpp"
#include "BoxTrigger.h"

RigidbodyGameObject::RigidbodyGameObject(std::string pName, glm::vec3 pPosition, PhysicsWorld* pWorld) :
	GameObject(pName,pPosition),
	_rigidbody (pWorld->addRigidBodyObject(this))
{
	_world = pWorld;
	neV3 position;
	position.Set(pPosition.x, pPosition.y, pPosition.z);
	_rigidbody->SetPos(position);

	
}


RigidbodyGameObject::~RigidbodyGameObject()
{
	_world->freeMemory(_rigidbody);
	
//	std::cout << _name << "<-- Rigid body cleaned" << std::endl;

	//delete _trigger;
	//std::cout << "trigger of  " << _name << "cleaned " << std::endl;
}

void RigidbodyGameObject::moveRb(glm::vec3 pPos)
{
	neV3 currVel;
	currVel.Set(_rigidbody->GetVelocity());

	neV3 posToSet;
	posToSet.Set(pPos.x, currVel[1], pPos.z);

	_rigidbody->SetVelocity( posToSet);
}

void RigidbodyGameObject::updateRigidBody()
{
		neV3 rbPos = _rigidbody->GetPos();
		glm::vec3 toGLMpos = glm::vec3(rbPos[0], rbPos[1], rbPos[2]);

		//neM3 rbRotationMatrix = _rigidbody->GetRotationM3();
		//
		////set gameobject transform
		//setTransform(glm::mat4x4(
		//	rbRotationMatrix[0][0], rbRotationMatrix[0][1], rbRotationMatrix[0][2], 0,
		//	rbRotationMatrix[1][0], rbRotationMatrix[1][1], rbRotationMatrix[1][2], 0,
		//	rbRotationMatrix[2][0], rbRotationMatrix[2][1], rbRotationMatrix[2][2], 0,
		//				toGLMpos.x,			    toGLMpos.y,				toGLMpos.z, 1
		//	));

	/*	neV3 rbVel;
		rbVel.Set(_rigidbody->GetVelocity());
		glm::vec3 glmRbVel(rbVel[0], rbVel[1], rbVel[2]);*/
		
		setLocalPosition(toGLMpos);
		
}

void RigidbodyGameObject::AddBoxCollider(float pW, float pH, float pD)
{
	neGeometry* geometry = _rigidbody->AddGeometry();
	neV3 box;
	box.Set(pW, pH, pD);
	geometry->SetBoxSize(box);
	_rigidbody->UpdateBoundingInfo();

	_trigger = new BoxTrigger(_minBounds, _maxBounds);
	_world->addMovingTrigger(this);
}

void RigidbodyGameObject::removeRigidBody()
{
	_world->freeMemory(_rigidbody);
}

void RigidbodyGameObject::deleteObject()
{
	_world->cleanMovingObject(this);
	delete _trigger;
}

neRigidBody* RigidbodyGameObject::GetRigidBody()
{
	return _rigidbody;
}

//void RigidbodyGameObject::SetBounds(glm::vec3 maxBound, glm::vec3 minBound)
//{
//	minBounds = minBound;
//	maxBounds = maxBound;
//}

//glm::vec3 RigidbodyGameObject::GetMinBounds()
//{
//	return minBounds;
//}

//glm::vec3 RigidbodyGameObject::GetMaxBounds()
//{
//	return maxBounds;
//}
