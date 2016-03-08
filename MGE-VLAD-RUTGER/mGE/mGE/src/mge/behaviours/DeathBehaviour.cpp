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
	//::cout << collision.getHitBy()  << std::endl;
	if (collision.getHitBy() == "Player" && !hit)
	{
		hit = true;
		std::cout << " Hitting playerr :) " << std::endl;
		StatsHolder::PlayerDied = true;
	}
}
