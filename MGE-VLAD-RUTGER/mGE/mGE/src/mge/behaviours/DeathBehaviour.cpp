#include "DeathBehaviour.h"
#include "mge/core/collision/BoxTrigger.h"
#include "mge/core/collision/Collision.h"
#include "mge/core/collision/StaticGameObject.h"
#include "mge/core/collision/RigidbodyGameObject.h"
#include "mge/StatsHolder.h"
#include "mge/core/SoundManager.h"


DeathBehaviour::DeathBehaviour()
{
	hit = false;
}


DeathBehaviour::~DeathBehaviour()
{
}

void DeathBehaviour::update(float pStep)
{
}

void DeathBehaviour::OnCollision(Collision collision)
{
	if (collision.getHitBy()->getName() == "Player" && !hit)
	{

		glm::vec3 spawnPos = StatsHolder::getSpawnPos();
		neV3 Pos;
		Pos.Set( spawnPos.x,spawnPos.y -4.5f,spawnPos.z);

		neV3 vel;
		vel.Set(0, 0, 0);

		dynamic_cast<RigidbodyGameObject*>(collision.getHitBy())->GetRigidBody()->SetPos(Pos);
		dynamic_cast<RigidbodyGameObject*>(collision.getHitBy())->GetRigidBody()->SetVelocity(vel);
		SoundManager::getInstance().PlaySound("death");
	}
}
