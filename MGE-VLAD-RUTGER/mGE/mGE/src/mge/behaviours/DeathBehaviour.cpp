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
	if (collision.getHitBy() == "Player" && !hit)
	{
		std::cout << "player died" << std::endl;
		/*glm::vec3 spawnPos = StatsHolder::getSpawnPos();
		neV3 Pos;
		Pos.Set( spawnPos.x,spawnPos.y,spawnPos.z);*/
		//_player->GetRigidBody()->SetPos(Pos);

		hit = true;
		//StatsHolder::PlayerDied = true;
	}
}
