#include "DeathBehaviour.h"
#include "mge/core/collision/BoxTrigger.h"
#include "mge/core/collision/Collision.h"
#include "mge/core/collision/StaticGameObject.h"
#include "mge/StatsHolder.h"


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
		std::cout << "player died" << std::endl;
		std::cout << collision.getHitBy()->getName() << std::endl;

		glm::vec3 spawnPos = StatsHolder::getSpawnPos();
		neV3 Pos;
		Pos.Set( spawnPos.x,spawnPos.y -4.5f,spawnPos.z);

		neV3 vel;
		vel.Set(0, 0, 0);

		dynamic_cast<RigidbodyGameObject*>(collision.getHitBy())->GetRigidBody()->SetPos(Pos);
		dynamic_cast<RigidbodyGameObject*>(collision.getHitBy())->GetRigidBody()->SetVelocity(vel);

		//hit = true;
		//StatsHolder::PlayerDied = true;
	}
}
