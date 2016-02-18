#include "StaticGameObject.h"
#include "mge/core/collision/PhysicsWorld.h"


StaticGameObject::StaticGameObject(std::string pName, glm::vec3 pPosition, PhysicsWorld* pWorld)
	: GameObject(pName,pPosition),
	_animBody(pWorld->addStaticGameObject(this))
{

}


StaticGameObject::~StaticGameObject()
{

}

void StaticGameObject::SetBounds(glm::vec3 maxBound, glm::vec3 minBound)
{
	minBounds = minBound;
	maxBounds = maxBound;
}

glm::vec3 StaticGameObject::GetMinBounds()
{
	return minBounds;
}

glm::vec3 StaticGameObject::GetMaxBounds()
{
	return maxBounds;
}

void StaticGameObject::updateStaticBody()
{
	//neV3 goWorldPos;
	//goWorldPos.Set(getWorldPosition().x, getWorldPosition().y, getWorldPosition().z * -1);
	//_animBody->SetPos(goWorldPos);

	//neM3 rotationMat;

	//neV3 rX;
	//rX.Set(getWorldTransform()[0].x, getWorldTransform()[1].x, getWorldTransform()[2].x);

	//neV3 rY;
	//rY.Set(getWorldTransform()[0].y, getWorldTransform()[1].y, getWorldTransform()[2].y);

	//neV3 rZ;
	//rZ.Set(getWorldTransform()[0].z, getWorldTransform()[1].z, getWorldTransform()[2].z);
	//rZ *= -1;

	//rotationMat.SetColumns(rX, rY, rZ);

	//_animBody->SetRotation(rotationMat);
	//setWorldPosition(glm::vec3(_animBody->GetPos()[0], _animBody->GetPos()[1], _animBody->GetPos()[2]));
}

void StaticGameObject::AddBoxCollider(float pW, float pH, float pD)
{
	neGeometry* geometry = _animBody->AddGeometry();
	neV3 box;
	box.Set(pW, pH, pD);
	geometry->SetBoxSize(box);
	_animBody->UpdateBoundingInfo();
}
