#include "SpawnPointBehaviour.h"
#include "mge/core/GameObject.hpp"
#include "mge/core/collision/BoxTrigger.h"
#include "mge/core/collision/Collision.h"
#include "mge/core/collision/StaticGameObject.h"
#include "SFML\Audio.hpp"
#include "mge/config.hpp"
#include "mge/StatsHolder.h"
#include "mge/SubtitleManager.h"
#include "mge/core/SoundManager.h"


SpawnPointBehaviour::SpawnPointBehaviour()
{
}


SpawnPointBehaviour::~SpawnPointBehaviour()
{
}

void SpawnPointBehaviour::update(float pStep)
{
}

void SpawnPointBehaviour::OnCollision(Collision collision)
{
	if (collision.getHitBy()->getName() == "Player" && !hit)
	{
		StatsHolder::setSpawnPos(_owner->getLocalPosition() + glm::vec3(0, 2, 0));
		SoundManager::getInstance().PlaySound(_owner->getName());
		SubtitleManager::playSubtitle("HUB_04");
		hit = true;
	}
}