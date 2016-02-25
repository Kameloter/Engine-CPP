#include "TriggerManager.h"
#include "mge/core/collision/Collision.h"
#include "mge/core/GameObject.hpp"
#include "mge/core/collision/BoxTrigger.h"
TriggerManager::TriggerManager()
{
    //ctor
}

TriggerManager::~TriggerManager()
{
    //dtor
}

void TriggerManager::addObject(GameObject * object)
{
	_triggers.push_back(object);
}
void TriggerManager::addMovingObject(GameObject * object)
{
	_movingTriggers.push_back(object);
}

void TriggerManager::cleanUp()
{
	_triggers.clear();
	_movingTriggers.clear();
	std::cout << " Triggers and moving triggers cleared " << std::endl;
}
void TriggerManager::runPhysics(float pDelta)
{
//	std::cout << " Helo trig" <<  std::endl;
    for(unsigned int i = 0; i < _movingTriggers.size(); i++)
    {
		//std::cout << " Helo rb  " << _movingTriggers[i]->getLocalPosition() << std::endl;
	//	std::cout << " Helo rb  " << _movingTriggers[i]->getTrigger()->getMaxBounds() <<  std::endl;
        for(unsigned int j = 0; j < _triggers.size(); j++)
        {

		//	std::cout << " Helo sb" << std::endl;

			Collision collisionInfo = _movingTriggers[i]->getTrigger()->resolveCollision(_triggers[i]->getTrigger());
			
           // std :: cout << "After colliding bool " << collisionInfo.getIsColliding() << std::endl;
          //  std :: cout << "After colliding distance " << collisionInfo.getCollisionDistance() << std::endl;
            if(collisionInfo.getIsColliding())
            {

                  std::cout << "THERE IS COLLISION " << std::endl;
				  _movingTriggers[i]->getTrigger()->collisionInfo->setInfo(true, _triggers[j]->getName());
				  _triggers[j]->getTrigger()->collisionInfo->setInfo(true, _movingTriggers[i]->getName());
			}
			else 
			{
				_movingTriggers[i]->getTrigger()->collisionInfo->setInfo(false,"");
				_triggers[j]->getTrigger()->collisionInfo->setInfo(false, "");
			}
        }
    }
}
