#include <cassert>
#include <iostream>
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/collision/Collision.h"

AbstractBehaviour::AbstractBehaviour():_owner(NULL) {}

AbstractBehaviour::~AbstractBehaviour()
{
	_owner = NULL;
}

void AbstractBehaviour::setOwner (GameObject* pOwner) {
    _owner = pOwner;
}

void AbstractBehaviour::OnCollision(Collision collision)
{
	
}

