#include "StaticGameObject.h"
#include "mge/core/collision/PhysicsWorld.h"
#include "mge/core/collision/BoxTrigger.h"

#define STATICMATERIAL 0

StaticGameObject::StaticGameObject(std::string pName, glm::vec3 pPosition, PhysicsWorld* pWorld, bool trigger)
	: GameObject(pName, pPosition),
	_world(pWorld)
{
	if (!trigger)
	{
		_animBody = _world->addStaticGameObject(this);
		neV3 pos;
		pos.Set(pPosition.x, pPosition.y, pPosition.z);
		_animBody->SetPos(pos);
		_trigger = nullptr;
	}
	else
	{
		_animBody = nullptr;
	}
}
neAnimatedBody * StaticGameObject::getAnimBody()
{
	if(_animBody != nullptr)
		return _animBody;	
}

StaticGameObject::~StaticGameObject()
{
	if (_animBody != nullptr)
	{
		_world->freeMemory(_animBody);
	//	std::cout << _name << "<-- Static body cleaned" << std::endl;
	}

	if (_trigger != nullptr)
	{
		_world->cleanStaticObject(this);
		delete _trigger;
	//	std::cout << "trigger of  " << _name << "cleaned " << std::endl;

	}
}
//
//void StaticGameObject::SetBounds(glm::vec3 maxBound, glm::vec3 minBound)
//{
//	minBounds = minBound;
//	maxBounds = maxBound;
//}
//
//glm::vec3 StaticGameObject::GetMinBounds()
//{
//	return minBounds;
//}
//
//glm::vec3 StaticGameObject::GetMaxBounds()
//{
//	return maxBounds;
//}


void StaticGameObject::moveStaticObject(glm::vec3 pTranslate)
{
	neV3 posToSet;
	posToSet.Set(pTranslate.x, pTranslate.y, pTranslate.z);
	_animBody->SetPos(_animBody->GetPos() + posToSet);
}

void StaticGameObject::moveTriggerObject(glm::vec3 pTranslate)
{
	setLocalPosition(getLocalPosition()+ pTranslate);
}

void StaticGameObject::updateStaticBody()
{

	if (!_trigger)
	{
		neV3 pos = _animBody->GetPos();

		glm::vec3 glmPOS(pos[0], pos[1], pos[2]);

		setLocalPosition(glmPOS);


	/*	neV3 goWorldPos;
		goWorldPos.Set(getWorldPosition().x, getWorldPosition().y, getWorldPosition().z * -1);
		_animBody->SetPos(goWorldPos);


		neM3 rotationMat;
		neQ quat;

		neV3 rX;
		rX.Set(getWorldTransform()[0].x, getWorldTransform()[0].y, getWorldTransform()[0].z);
		
		neV3 rY;
		rY.Set(getWorldTransform()[1].x, getWorldTransform()[1].y, getWorldTransform()[1].z);

		neV3 rZ;
		rZ.Set(getWorldTransform()[2].x, getWorldTransform()[2].y, getWorldTransform()[2].z);
	

		rotationMat.SetColumns(rX, rY, rZ);

		quat.SetupFromMatrix3(rotationMat);

		_animBody->SetRotation(quat);*/

	}

	//setWorldPosition(glm::vec3(_animBody->GetPos()[0], _animBody->GetPos()[1], _animBody->GetPos()[2]));
	//std::cout <<glm::vec3(_animBody->GetPos()[0], _animBody->GetPos()[1], _animBody->GetPos()[2]) << std::endl;
}

void StaticGameObject::AddBoxCollider(float pW, float pH, float pD)
{
	if (_animBody != nullptr)
	{
		neGeometry* geometry = _animBody->AddGeometry();
		neV3 box;
		//std::cout << "boxPOS" << glm::vec3(_animBody->GetPos()[0], _animBody->GetPos()[1], _animBody->GetPos()[2]) << std::endl;
		box.Set(pW, pH, pD);
		geometry->SetBoxSize(box);
		_animBody->UpdateBoundingInfo();
	}
	else {
		
		_trigger = new BoxTrigger(_minBounds, _maxBounds);
		_world->addStaticTrigger(this);
	}

	
}

