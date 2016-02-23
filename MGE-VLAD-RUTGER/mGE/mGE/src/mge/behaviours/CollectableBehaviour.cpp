#include "CollectableBehaviour.h"

#include "mge/core/collision/RigidbodyGameObject.h"

#include <glm.hpp>
#include "mge/core/GameObject.hpp"
#include <SFML/Graphics.hpp>



CollectableBehaviour::CollectableBehaviour()
{
}


CollectableBehaviour::~CollectableBehaviour()
{
}

void CollectableBehaviour::update(float pStep) {
	if (glm::distance(_owner->getLocalPosition(), _player->getLocalPosition()) < 1.0f) {
		delete _owner;
	}
}

void CollectableBehaviour::SetPlayer(GameObject * pPlayer)
{
	_player = pPlayer;
}
